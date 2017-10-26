#include "glwidget.h"
#include <QDebug>

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

void GLWidget::OpenData(std::string filename)
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
    this->polyhedrons[0].Scale(1, 2, 3);
    infile.close();
}

void
GLWidget::initializeGL(){
    // Initialize OpenGL Backend
    initializeOpenGLFunctions();
    printContextInformation();

    // Set global information
    glClearColor(1.0f,1.0f,1.0f,1.0f);

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
    glOrtho(0,1.0,0.0,1.0,-10,10);

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

    //tells opengl to interperate every two calls to glVertex as a line
    glBegin(GL_LINES);
    //first line will be blue
    glColor3f(0,0,1.0);
    glVertex2f(0.1,0.1);
    glVertex2f(.9,.9);

    //this will be a red line
    //notice we can use 3d points too
    //how will this change if we project to the XZ or YZ plane?
    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.1,0.9,0.5);
    glVertex3f(0.9,0.1,0.3);
    glEnd();
}

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
