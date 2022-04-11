
#include<Application.hpp>

using namespace App;

int Application::WindowInit(GLuint width,GLuint height,std::string name)
{

    mywindow=glfwCreateWindow(width,height,name.c_str(),NULL,NULL);
    if(!mywindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mywindow);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
int Application::Run()
{
    while(!glfwWindowShouldClose(mywindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}
