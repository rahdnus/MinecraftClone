#include<core/Application.hpp>

int main()
{
    Core::Application app;

    if(!glfwInit())
        return -1;

    app.windowInit(500,500,"Yes");
    
    app.run();
    return 0;
}