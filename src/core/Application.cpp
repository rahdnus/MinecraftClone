
#include<core/Application.hpp>

using namespace Core;

int Application::windowInit(GLuint width,GLuint height,std::string name)
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
int Application::run()
{
    while(!glfwWindowShouldClose(mywindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}
