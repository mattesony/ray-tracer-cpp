#include "glwidgets.h"

GLWidgets::GLWidgets(GLWidget *openGLWidgetXY, GLWidget *openGLWidgetXZ, GLWidget *openGLWidgetYZ)
{
    this->openGLWidgetXY = openGLWidgetXY;
    this->openGLWidgetXZ = openGLWidgetXZ;
    this->openGLWidgetYZ = openGLWidgetYZ;

    this->openGLWidgetXY->setPolyhedrons(this->polyhedrons);
    this->openGLWidgetXZ->setPolyhedrons(this->polyhedrons);
    this->openGLWidgetYZ->setPolyhedrons(this->polyhedrons);

    this->openGLWidgetXY->setProjection("AxoXY");
    this->openGLWidgetXZ->setProjection("AxoXZ");
    this->openGLWidgetYZ->setProjection("AxoYZ");
}

bool GLWidgets::OpenData(std::string filename, std::string matfilename, std::string lightfilename)
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

    this->openGLWidgetXY->setMaterials(this->materials);
    this->openGLWidgetXZ->setMaterials(this->materials);
    this->openGLWidgetYZ->setMaterials(this->materials);

    this->openGLWidgetXY->setLight(this->light);
    this->openGLWidgetXZ->setLight(this->light);
    this->openGLWidgetYZ->setLight(this->light);

    return true;
}

bool GLWidgets::SaveData(std::string filename)
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

void GLWidgets::Repaint()
{
    this->openGLWidgetXY->polyhedrons = this->polyhedrons;
    this->openGLWidgetXZ->polyhedrons = this->polyhedrons;
    this->openGLWidgetYZ->polyhedrons = this->polyhedrons;

    this->openGLWidgetXY->repaint();
    //this->openGLWidgetXZ->repaint();
    //this->openGLWidgetYZ->repaint();
}
