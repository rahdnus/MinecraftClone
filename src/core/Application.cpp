
#include <core/Application.hpp>
#include <Renderer/ShaderProgram.hpp>
#include <core/Object.hpp>

using namespace Engine;

GLuint VAO_ID, VBO_ID, EBO_ID;

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

    Object *gameObject;
    Vertex vertex[4] = {
        {glm::vec3(0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},   // 0
        {glm::vec3(-0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},  // 1
        {glm::vec3(-0.5f, -0.5f, 0), glm::vec4(1, 0, 1, 1)}, // 2
        {glm::vec3(0.5f, -0.5f, 0), glm::vec4(0, 1, 1, 1)}   // 3

    };
    GLuint indices[]{
        0, 1, 3,
        1, 2, 3};
    ShaderProgram shaderProgram;
    Mesh *mesh=new Mesh(vertex, indices, shaderProgram);
    mesh->Init(); 
    while (!glfwWindowShouldClose(mywindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        mesh->Bind();
        mesh->Draw();

        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}

