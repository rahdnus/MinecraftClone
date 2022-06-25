#include<core/Application.hpp>
// #include<core/Object.hpp>

using namespace Engine;
int main()
{
    Engine::Application app;

    if(!glfwInit())
        return -1;

    app.windowInit(500,500,"Yes");

    // Vertex vertex[]{
    //     {glm::vec3(0.5f,0.5f,0),glm::vec4(1,0,1,1)},//0
    //     {glm::vec3(-0.5f,0.5f,0),glm::vec4(1,0,1,1)},//1
    //     {glm::vec3(-0.5f,-0.5f,0),glm::vec4(1,0,1,1)},//2
    //     {glm::vec3(0.5f,-0.5f,0),glm::vec4(0,1,1,1)}//3};
    // };
    // GLuint indices[]{
    //     0,1,3,
    //     1,2,3
    // };
    // Mesh mesh(vertex,indices);
    // Object obj(&mesh);
    // obj.mesh->Init();
    app.run();
    return 0;
}