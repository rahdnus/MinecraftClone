#include <core/Application.hpp>
#include <Renderer/ShaderProgram.hpp>
#include <core/Object.hpp>

using namespace Engine;
ShaderProgram shaderProgram;
GLuint VAO_ID, VBO_ID, EBO_ID;

/* struct MEGA
{
    GLuint VAO_ID, VBO_ID, EBO_ID;
    Vertex* vertex;
    GLuint* indices;
   
    MEGA(Vertex* vertex,int Vno, GLuint* indices,int Ino)
    {
        this->vertex=vertex;
        this->indices=indices;
        this->Vno=Vno;
        this->Ino=Ino;
    }
}; */
int Application::windowInit(GLuint width, GLuint height, std::string name)
{

    mywindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!mywindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mywindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
int Application::run()
{
    shaderProgram.compile("Shaders/SimpleVert.glsl","Shaders/SimpleFrag.glsl");

    Vertex vertex[4] = {
        {glm::vec3(0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},   
        {glm::vec3(-0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},  
        {glm::vec3(-0.5f, -0.5f, 0), glm::vec4(1, 0, 1, 1)}, 
        {glm::vec3(0.5f, -0.5f, 0), glm::vec4(0, 1, 1, 1)}   
    };

    GLuint indices[]{
        0, 1, 3,
        1, 2, 3};

    Mesh mesh(vertex,sizeof(vertex)/sizeof(Vertex),indices,sizeof(indices)/sizeof(GLuint));
    Object obj(mesh);

    while (!glfwWindowShouldClose(mywindow))
    {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.bind();

        obj.Cycle();
        glfwSwapBuffers(mywindow);
        glfwPollEvents();

    }
}
