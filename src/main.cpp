#include<Application.hpp>

int main()
{
    App::Application app;

    if(!glfwInit())
        return -1;

    app.WindowInit(500,500,"Yes");
    
    app.Run();
    return 0;
}