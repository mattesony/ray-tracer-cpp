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

    glLineWidth(2.0); //sets the "width" of each line we are rendering


    //first line will be blue
    glColor3f(0,0,1.0);

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
        vector<Point> projectedPoints = polyhedron.GetProjectedPoints(this->projection);
        for(Triangle triangle : polyhedron.GetTriangles())
        {
            DrawBresenham({projectedPoints[triangle.v1].x*450, projectedPoints[triangle.v1].y*450}, {projectedPoints[triangle.v2].x*450, projectedPoints[triangle.v2].y*450});
            DrawBresenham({projectedPoints[triangle.v2].x*450, projectedPoints[triangle.v2].y*450}, {projectedPoints[triangle.v3].x*450, projectedPoints[triangle.v3].y*450});
            DrawBresenham({projectedPoints[triangle.v3].x*450, projectedPoints[triangle.v3].y*450}, {projectedPoints[triangle.v1].x*450, projectedPoints[triangle.v1].y*450});
//            Megapixel(projectedPoints[edge.v1].x*450, projectedPoints[edge.v1].y*450);
//            Megapixel(projectedPoints[edge.v2].x*450, projectedPoints[edge.v2].y*450);
        }
    }

    //tells opengl to interperate every two calls to glVertex as a line
    glBegin(GL_LINES);
    if(drawRotAxis)
    {
        glColor3f(1.0,0.0,0.0);
        glVertex3f(pointA(0)*450, pointA(1)*450, pointA(2)*450);
        glVertex3f(pointB(0)*450, pointB(1)*450, pointB(2)*450);
        drawRotAxis = false;
    }
    glEnd();
}

void GLWidget::Megapixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x-1, y-1);
    glVertex2f(x, y-1);
    glVertex2f(x+1, y-1);
    glVertex2f(x-1, y);
    glVertex2f(x, y);
    glVertex2f(x+1, y);
    glVertex2f(x-1, y+1);
    glVertex2f(x, y+1);
    glVertex2f(x+1, y+1);
    glEnd();
}

// Adapted from the book
void GLWidget::DrawBresenham(Vector2f pointA, Vector2f pointB)
{
    float slope = (pointB(1) - pointA(1))/(pointB(0) - pointA(0));
    // Special cases

    if(pointB(1) - pointA(1) == 0)
    {
        for(int j = 1; j < max(pointB(0), pointA(0)) - min(pointB(0), pointA(0)); j+=3)
        {
            Megapixel(min(pointB(0), pointA(0)) + j, pointA(1));
        }
    }
    else if(pointB(0) - pointA(0) == 0)
    {
        for(int j = 1; j < max(pointB(1), pointA(1)) - min(pointB(1), pointA(1)); j+=3)
        {
            Megapixel(pointA(0), min(pointB(1), pointA(1)) + j);
        }
    }
    else if(1 == abs(slope))
    {
        for(int j = 1; j < max(pointB(0), pointA(0)) - min(pointB(0), pointA(0)); j+=3)
        {
            Megapixel(min(pointB(0), pointA(0)) + j, (slope == 1) ? min(pointB(1), pointA(1)) + j : max(pointB(1), pointA(1)) - j);
        }
    }
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


    if(x1 > x2)
    {
        x = x2;
        y = y2;
        x2 = x1;
    }
    else
    {
        x = x1;
        y = y1;
    }
    Megapixel(slopeLessThanOne ? x : y, (slopeLessThanOne ? y : x) * ((!slopePositive) ? -1 : 1));
    while(x < x2)
    {
        x+=3;
        if(p < 0)
            p += twoDy;
        else
        {
            y+=3;
            p += twoDyMinusDx;
        }
        Megapixel(slopeLessThanOne ? x : y, (slopeLessThanOne ? y : x) * ((!slopePositive) ? -1 : 1));
    }
}

/*
void FillPolygon(int polygon)
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
