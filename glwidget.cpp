#include "glwidget.h"
#include <QDebug>
#include <Eigen/Eigen>

using namespace Eigen;

GLWidget::GLWidget(QWidget *parent)
{
    // Set OpenGL Version information
    // Note: This format must be set before show() is called.
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2,1);

    this->setFormat(format);

}

GLWidget::~GLWidget()
{
    makeCurrent();
    teardownGL();
}


void
GLWidget::initializeGL(){
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    printContextInformation();

    // Set global information
    glClearColor(0.0f,0.0f,0.0f,0.0f);

    printContextInformation();
}

void
GLWidget::resizeGL(int width, int height){
    /*set up projection matrix to define the view port*/

    this->width = width;
    this->height = height;

    //creates a rendering area across the window
    glViewport(0,0,width,height);

    // uses an orthogonal projection matrix so that
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //you guys should look up this function
    glOrtho(0,width,0.0,height,-10,10);

    //clear the modelview matrix
    //the ModelView Matrix can be used in this project, to change the view on the projection
    //but you can also leave it alone and deal with changing the projection to a different view
    //for project 2, do not use the modelview matrix to transform the actual geometry, as you won't
    //be able to save the results
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
GLWidget::paintGL(){    
    //clears the screen
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
    //clears the opengl Modelview transformation matrix
    glLoadIdentity();

    int sideLength = (width<height) ? width : height;

    vector<Polyhedron> clippedPolyhedrons;
    if(this->clipping)
    {
        for(Polyhedron polyhedron : this->polyhedrons)
        {
            unsigned int pointsWithinCube = 0;
            for(Point point : polyhedron.GetPoints())
            {
                if((0 <= point.x) && (1 >= point.x) && (0 <= point.y) && (1 >= point.y) && (0 <= point.z) && (1 >= point.z))
                {
                    pointsWithinCube++;
                }
            }
            if(pointsWithinCube == polyhedron.GetPoints().size())
            {
                clippedPolyhedrons.push_back(polyhedron);
            }
        }
    }
    else
        clippedPolyhedrons = this->polyhedrons;
    for(Polyhedron polyhedron : clippedPolyhedrons)
    {
        vector<Point> points = polyhedron.GetPoints();
        for(Triangle triangle : polyhedron.GetTriangles())
        {
            Vector3f vertex1 = {points[triangle.v1].x,
                                points[triangle.v1].y,
                                points[triangle.v1].z};
            Vector3f vertex2 = {points[triangle.v2].x,
                                points[triangle.v2].y,
                                points[triangle.v2].z};
            Vector3f vertex3 = {points[triangle.v3].x,
                                points[triangle.v3].y,
                                points[triangle.v3].z};
            Vector3f normal = ((vertex2 - vertex1).cross(vertex3 - vertex1)).normalized();
            glPointSize(this->light.X(2) * sideLength/10);
            glBegin(GL_POINTS);
            auto lColor = this->light.Li;
            glColor4f(lColor(0),lColor(1),lColor(2), 0.1);
            glVertex3f(this->light.X(0)*sideLength, this->light.X(1)*sideLength, 1);
            glEnd();
            glPointSize(1.0);
            Vector3f color1 = phongLight(polyhedron, vertex1, normal);
            Vector3f color2 = phongLight(polyhedron, vertex2, normal);
            Vector3f color3 = phongLight(polyhedron, vertex3, normal);
            DrawBresenham({points[triangle.v1].x*sideLength, points[triangle.v1].y*sideLength}, {points[triangle.v2].x*sideLength, points[triangle.v2].y*sideLength}, color1, color2);
            DrawBresenham({points[triangle.v2].x*sideLength, points[triangle.v2].y*sideLength}, {points[triangle.v3].x*sideLength, points[triangle.v3].y*sideLength}, color2, color3);
            DrawBresenham({points[triangle.v3].x*sideLength, points[triangle.v3].y*sideLength}, {points[triangle.v1].x*sideLength, points[triangle.v1].y*sideLength}, color3, color1);
        }
    }

    //tells opengl to interperate every two calls to glVertex as a line
    glBegin(GL_LINES);
    if(drawRotAxis)
    {
        glColor3f(1.0,0.0,0.0);
        glVertex3f(pointA(0)*sideLength, pointA(1)*sideLength, pointA(2)*sideLength);
        glVertex3f(pointB(0)*sideLength, pointB(1)*sideLength, pointB(2)*sideLength);
        drawRotAxis = false;
    }
    glEnd();
}

Vector3f GLWidget::phongLight(Polyhedron polyhedron, Vector3f vertex, Vector3f normal)
{
    Vector3f light = this->light.X;
    Vector3f lightVector = (light - vertex).normalized();
    Vector3f f = vertex + Vector3f(0.5, 0.5, 1);
    Vector3f Kd = this->materials[polyhedron.GetMaterial()].Kd;
    Vector3f intens = this->light.Li/((f-vertex).norm() + this->light.K);
    Vector3f diffuseColor = intens.cwiseProduct(Kd*(lightVector.dot(normal)));
    return diffuseColor;
}

bool GLWidget::OpenData(std::string filename, std::string matfilename, std::string lightfilename)
{
    polyhedrons.clear();
    std::ifstream infile(filename);
    if(!infile) return false;
    std::string line;
    int countPolyhedrons;
    std::getline(infile, line);

    std::istringstream(line) >> countPolyhedrons;

    for(int polyIndex = 0; polyIndex < countPolyhedrons; polyIndex++)
    {
        do //remove empty lines
        {
            std::getline(infile, line);
        }
        while(line.empty());
        int material, countPoints;
        std::istringstream(line) >> material;
        std::getline(infile, line);
        std::istringstream(line) >> countPoints;
        std::vector<Point> points;

        for(int pointIndex = 0; pointIndex < countPoints; pointIndex++)
        {
            std::getline(infile, line);
            float x, y, z;
            if(!(std::istringstream(line) >> x >> y >> z))
            {
                break;
                cout << "Failed to read point " << line << ": must be formatted like \"0.32 0.0 0.45\"" << endl;
                cin >> line;
                exit(-1);
            }
            Point newPoint = {x, y, z};
            points.push_back(newPoint);
        }

        do //remove empty lines
        {
            std::getline(infile, line);
        }
        while(line.empty());
        int countTriangles;
        std::istringstream(line) >> countTriangles;
        std::vector<Triangle> triangles;

        for(int triangleIndex = 0; triangleIndex < countTriangles; triangleIndex++)
        {
            std::getline(infile, line);
            int v1, v2, v3;
            if(!(std::istringstream(line) >> v1 >> v2 >> v3))
            {
                break;
                cout << "Failed to read edge " << line << ": must be formatted like \"1 2 3\"" << endl;
                cin >> line;
                exit(-1);
            }

            Triangle newTriangle = {v1 - 1, v2 - 1, v3 - 1};
            triangles.push_back(newTriangle);
        }

        this->polyhedrons.push_back(Polyhedron(points, triangles, material));
    }
    infile.close();

    materials.clear();
    std::ifstream matfile(matfilename);
    if(!matfile) return false;
    int countMaterials;
    std::getline(matfile, line);
    std::istringstream(line) >> countMaterials;

    for(int countIndex = 0; countIndex < countMaterials; countIndex++)
    {
        do //remove empty lines
        {
            std::getline(matfile, line);
        }
        while(line.empty());

        float KaR, KaG, KaB;
        std::istringstream(line) >> KaR >> KaG >> KaB;
        Vector3f Ka = {KaR, KaG, KaB};

        std::getline(matfile, line);
        float KdR, KdG, KdB;
        std::istringstream(line) >> KdR >> KdG >> KdB;
        Vector3f Kd = {KdR, KdG, KdB};

        std::getline(matfile, line);
        float KsR, KsG, KsB;
        std::istringstream(line) >> KsR >> KsG >> KsB;
        Vector3f Ks = {KsR, KsG, KsB};

        std::getline(matfile, line);
        float phongExponent;
        std::istringstream(line) >> phongExponent;

        materials.push_back({.Ka = Ka, .Kd = Kd, .Ks = Ks, .phongExponent = phongExponent});
    }
    matfile.close();

    std::ifstream lightfile(lightfilename);
    if(!lightfile) return false;

    std::getline(lightfile, line);
    float Xx, Xy, Xz;
    std::istringstream(line) >> Xx >> Xy >> Xz;
    Vector3f X = {Xx, Xy, Xz};

    std::getline(lightfile, line);
    float LaR, LaG, LaB;
    std::istringstream(line) >> LaR >> LaG >> LaB;
    Vector3f La = {LaR, LaG, LaB};

    std::getline(lightfile, line);
    float LiR, LiG, LiB;
    std::istringstream(line) >> LiR >> LiG >> LiB;
    Vector3f Li = {LiR, LiG, LiB};

    std::getline(lightfile, line);
    float F;
    std::istringstream(line) >> F;

    std::getline(lightfile, line);
    float K;
    std::istringstream(line) >> K;

    light = {.X = X, .La = La, .Li = Li, .F = F, .K = K};

    lightfile.close();

    this->setMaterials(this->materials);

    this->setLight(this->light);

    return true;
}

bool GLWidget::SaveData(std::string filename)
{
    ofstream fout(filename);
    if(!fout) return false;

    fout << this->polyhedrons.size() << endl;

    for(Polyhedron polyhedron : this->polyhedrons)
    {
        fout << endl;
        fout << polyhedron.GetMaterial() << endl;
        fout << polyhedron.GetPoints().size() << endl;
        for(Point point : polyhedron.GetPoints())
        {
            fout << point.x << " " << point.y << " " << point.z << endl;
        }

        fout << polyhedron.GetTriangles().size() << endl;
        for(Triangle triangle : polyhedron.GetTriangles())
        {

            fout << triangle.v1 + 1 << " " << triangle.v2 + 1 << " " << triangle.v3 + 1 << endl;
        }
    }

    fout.close();
    return true;
}

void GLWidget::Megapixel(float x, float y, Vector3f color)
{
    char cells[3][3] = {0};
    float noOn = 9 * std::max(std::max(color(0), color(1)), color(2));
    //if (noOn > 9) noOn = 9;
    int noR = round(color(0) * noOn / (color(0) + color(1) + color(2)));
    for(int i = 0; i < noR; i++)
    {
        int cell = rand() % (9);
        if(cells[cell / 3][cell % 3])
        {
            i--;
        }
        else
           cells[cell / 3][cell % 3] = 'r';
    }
    int noG = round(color(1) * noOn / (color(0) + color(1) + color(2)));
    for(int i = 0; i < noG; i++)
    {
        int cell = rand() % (9);
        if(cells[cell / 3][cell % 3])
        {
            i--;
        }
        else
           cells[cell / 3][cell % 3] = 'g';
    }
    int noB = round(color(2) * noOn / (color(0) + color(1) + color(2)));
    for(int i = 0; i < noB; i++)
    {
        int cell = rand() % (9);
        if(cells[cell / 3][cell % 3])
        {
            i--;
        }
        else
           cells[cell / 3][cell % 3] = 'b';
    }
    glBegin(GL_POINTS);
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            glColor3f(1.0 * (cells[i][j] == 'r'), 1.0 * (cells[i][j] == 'g'), 1.0 * (cells[i][j] == 'b'));
            glVertex2f(x + i - 1, y + j - 1);
        }
    }
    glEnd();
}

void GLWidget::DrawPixel(float x, float y, Vector3f color)
{
    glBegin(GL_POINTS);
    glColor3f(color(0), color(1), color(2));
    glVertex2f(x, y);
    glEnd();
}

Vector3f GLWidget::linInt(Vector3f colorA, Vector3f colorB, float t)
{
    float r = colorA(0) + (colorB(0) - colorA(0)) * t;
    float g = colorA(1) + (colorB(1) - colorA(1)) * t;
    float b = colorA(2) + (colorB(2) - colorA(2)) * t;
    Vector3f rgb = {r, g, b};
    return rgb;
}


// Adapted from the book
void GLWidget::DrawBresenham(Vector2f pointA, Vector2f pointB, Vector3f colorA, Vector3f colorB)
{
    float slope = (pointB(1) - pointA(1))/(pointB(0) - pointA(0));
    // Special cases

    if(pointB(1) - pointA(1) == 0)
    {
        float xDist = max(pointB(0), pointA(0)) - min(pointB(0), pointA(0));
        for(int j = 1; j < xDist; j++)
        {
            if (pointB(0) >= pointA(0))
            {
                DrawPixel(pointA(0) + j, pointA(1), linInt(colorA, colorB, j/xDist));
            }
            else if (pointB(0) < pointA(0))
            {
                DrawPixel(pointB(0) + j, pointA(1), linInt(colorB, colorA, j/xDist));
            }
        }
    }
    else if(pointB(0) - pointA(0) == 0)
    {
        float yDist = max(pointB(1), pointA(1)) - min(pointB(1), pointA(1));
        for(int j = 1; j < yDist; j++)
        {
            if (pointB(1) >= pointA(1))
            {
                DrawPixel(pointA(0), pointA(1) + j, linInt(colorA, colorB, j/yDist));
            }
            if (pointB(1) < pointA(1))
            {
                DrawPixel(pointA(0), pointB(1) + j, linInt(colorB, colorA, j/yDist));
            }

        }
    }
    else if(1 == abs(slope))
    {
        float xDist = max(pointB(0), pointA(0)) - min(pointB(0), pointA(0));
        for(int j = 1; j < xDist; j++)
        {
            if (pointB(0) >= pointA(0))
            {
                DrawPixel(pointA(0) + j, (slope == 1) ? min(pointB(1), pointA(1)) + j : max(pointB(1), pointA(1)) - j, linInt(colorA, colorB, j/xDist));
            }
            else if (pointB(0) < pointA(0))
            {
                DrawPixel(pointB(0) + j, (slope == 1) ? min(pointB(1), pointA(1)) + j : max(pointB(1), pointA(1)) - j, linInt(colorB, colorA, j/xDist));
            }
        }
    }
    else
    {
        bool slopeLessThanOne = fabs(slope) < 1;
        bool slopePositive = slope > 0;

        int x1 = (slopeLessThanOne ? pointA(0) : pointA(1)) * ((!slopeLessThanOne && !slopePositive) ? -1 : 1);
        int y1 = (slopeLessThanOne ? pointA(1) : pointA(0)) * ((slopeLessThanOne && !slopePositive) ? -1 : 1);
        int x2 = (slopeLessThanOne ? pointB(0) : pointB(1)) * ((!slopeLessThanOne && !slopePositive) ? -1 : 1);
        int y2 = (slopeLessThanOne ? pointB(1) : pointB(0)) * ((slopeLessThanOne && !slopePositive) ? -1 : 1);
        int dx = fabs(x2 - x1);
        int dy = fabs(y2 - y1);
        int p = 2 * dy - dx;
        int twoDy = 2 * dy;
        int twoDyMinusDx = 2 * (dy - dx);
        int x, y;

        int totalDist = fabs(x1 - x2);

        if(x1 > x2)
        {
            x = x2;
            y = y2;
            x2 = x1;
            Vector3f temp = colorA;
            colorA = colorB;
            colorB = temp;
        }
        else
        {
            x = x1;
            y = y1;
        }
        DrawPixel(slopeLessThanOne ? x : y, (slopeLessThanOne ? y : x) * ((!slopePositive) ? -1 : 1), linInt(colorA, colorB, 1/((totalDist != 0) ? totalDist : 1)));
        while(x < x2)
        {
            x++;
            if(p < 0)
                p += twoDy;
            else
            {
                y++;
                p += twoDyMinusDx;
            }
            DrawPixel(slopeLessThanOne ? x : y, (slopeLessThanOne ? y : x) * ((!slopePositive) ? -1 : 1), linInt(colorA, colorB, (slopeLessThanOne ? x - x1 : y - y1)/((totalDist != 0) ? totalDist : 1)));
        }
    }
}

/*
void FillPolygon(int polygon)
    sec_die = rand() % (HIGH - LOW + 1) + LOW;
{
    vector<Point> points = polygons[polygon].GetPoints();
    Point bbLowerLeftCorner = points[0];
    Point bbUpperRightCorner = points[0];
    for(Point point : points)
    {
        if(point.x < bbLowerLeftCorner.x) bbLowerLeftCorner.x = point.x;
        if(point.y < bbLowerLeftCorner.y) bbLowerLeftCorner.y = point.y;
        if(point.x > bbUpperRightCorner.x) bbUpperRightCorner.x = point.x;
        if(point.y > bbUpperRightCorner.y) bbUpperRightCorner.y = point.y;
    }
    points.push_back(points[0]);
    for(float scanlineY = bbLowerLeftCorner.y + 0.001; scanlineY < bbUpperRightCorner.y; scanlineY++)
    {
        vector<Point> intersections;
        for(int edge = 0; edge < points.size() - 1; edge++)
        {
            if(((min(points[edge].y, points[edge+1].y) < scanlineY) && (max(points[edge].y, points[edge+1].y) > scanlineY)) || (points[edge].y == scanlineY) || (points[edge+1].y == scanlineY))
            {
                float x = (scanlineY - points[edge].y)*((points[edge+1].x-points[edge].x)/(points[edge+1].y-points[edge].y)) + points[edge].x;
                intersections.push_back({x, scanlineY,  (points[edge+1].x-points[edge].x)/(points[edge+1].y-points[edge].y)});
            }
        }
        if(!intersections.empty())
        {
            sort(intersections.begin(), intersections.end(), [](const Point &a, const Point &b)
            {
                return (a.x < b.x);
            });
            int currentIntersection = 0;
            bool turnOn = false;
            for(int currentX = floor(bbLowerLeftCorner.x); (currentX < bbUpperRightCorner.x) && (currentIntersection < intersections.size()); currentX++)
            {
                while((currentIntersection < intersections.size()) && (currentX == round(intersections[currentIntersection].x)))
                {
                    turnOn = !turnOn;
                    currentIntersection++;
                }
                if(turnOn)
                {
                    MakePix(currentX, scanlineY, PixelType::Fill, polygon);
                }

            }
        }
    }
}
*/

void
GLWidget::teardownGL(){
    ;
}

void
GLWidget::printContextInformation(){
    QString glType;
    QString glVersion;
    QString glProfile;

    // Get Version Information
    glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

    // Get Profile Information
    #define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
    switch (format().profile())
    {
    CASE(NoProfile);
    CASE(CoreProfile);
    CASE(CompatibilityProfile);
    }
    #undef CASE

    // qPrintable() will print our QString w/o quotes around it.
    qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}
