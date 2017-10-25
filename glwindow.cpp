#include "glwindow.h"
#include "ui_glwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    OpenData("../polyhedrons");
}

void GLWindow::OpenData(std::string filename)
{
    std::ifstream infile(filename);
    std::string line;
    int countPolyhedrons;
    std::getline(infile, line);
    std::istringstream iss(line);

    iss >> countPolyhedrons;

    for(int polyIndex = 0; polyIndex < countPolyhedrons; polyIndex++)
    {
        do //remove empty lines
        {
            std::getline(infile, line);
        }
        while(line.empty());
        int countPoints;
        std::istringstream iss(line);
        iss >> countPoints;
        std::vector<Point> points;

        for(int pointIndex = 0; pointIndex < countPoints; pointIndex++)
        {
            std::getline(infile, line);
            std::istringstream iss(line);
            float x, y, z;
            if(!(iss >> x >> y >> z))
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
        std::istringstream iss2(line);
        iss2 >> countEdges;
        std::vector<Edge> edges;

        for(int edgeIndex = 0; edgeIndex < countEdges; edgeIndex++)
        {
            std::getline(infile, line);
            std::istringstream iss(line);
            int v1, v2;
            if(!(iss >> v1 >> v2))
            {
                break;
                cout << "Failed to read edge " << line << ": must be formatted like \"1 2\"" << endl;
                cin >> line;
                exit(-1);
            }
            Edge newEdge = {v1, v2};
            edges.push_back(newEdge);
        }

        this->polyhedrons.push_back(Polyhedron(points, edges));
    }

    infile.close();
}

GLWindow::~GLWindow()
{
    delete ui;
}
