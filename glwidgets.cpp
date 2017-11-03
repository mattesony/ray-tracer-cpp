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

void GLWidgets::OpenData(std::string filename)
{
    polyhedrons.clear();
    std::ifstream infile(filename);
    std::string line;
    int countPolyhedrons;
    std::getline(infile, line);

    std::istringstream(line) >> countPolyhedrons;

    int offset;
    (this->indicesStartAt1) ? offset = 1 : offset = 0;

    for(int polyIndex = 0; polyIndex < countPolyhedrons; polyIndex++)
    {
        do //remove empty lines
        {
            std::getline(infile, line);
        }
        while(line.empty());
        int countPoints;
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
        int countEdges;
        std::istringstream(line) >> countEdges;
        std::vector<Edge> edges;

        for(int edgeIndex = 0; edgeIndex < countEdges; edgeIndex++)
        {
            std::getline(infile, line);
            int v1, v2;
            if(!(std::istringstream(line) >> v1 >> v2))
            {
                break;
                cout << "Failed to read edge " << line << ": must be formatted like \"1 2\"" << endl;
                cin >> line;
                exit(-1);
            }

            Edge newEdge = {v1 - offset, v2 - offset};
            edges.push_back(newEdge);
        }

        this->polyhedrons.push_back(Polyhedron(points, edges));
    }
    infile.close();
}

void GLWidgets::SaveData(std::string filename)
{
    ofstream fout(filename);

    fout << this->polyhedrons.size() << endl;

    int offset;
    (this->indicesStartAt1) ? offset = 1 : offset = 0;

    for(Polyhedron polyhedron : this->polyhedrons)
    {
        fout << endl;
        fout << polyhedron.GetPoints().size() << endl;
        for(Point point : polyhedron.GetPoints())
        {
            fout << point.x << " " << point.y << " " << point.z << endl;
        }

        fout << polyhedron.GetEdges().size() << endl;
        for(Edge edge : polyhedron.GetEdges())
        {

            fout << edge.v1 + offset << " " << edge.v2 + offset << endl;
        }
    }

    fout.close();
}

void GLWidgets::Repaint()
{
    this->openGLWidgetXY->polyhedrons = this->polyhedrons;
    this->openGLWidgetXZ->polyhedrons = this->polyhedrons;
    this->openGLWidgetYZ->polyhedrons = this->polyhedrons;

    this->openGLWidgetXY->repaint();
    this->openGLWidgetXZ->repaint();
    this->openGLWidgetYZ->repaint();
}
