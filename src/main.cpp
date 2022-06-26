#include<core/Application.hpp>
// #include<core/Object.hpp>

using namespace Engine;
int main()
{
    Engine::Application app;

    if(!glfwInit())
        return -1;

    app.windowInit(500,500,"Yes");
    app.run();
    return 0;
}