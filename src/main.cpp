#include<main.hpp>
#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
    if(!glfwInit())
        return -1;
 
   GLFWwindow* window=glfwCreateWindow(500,500,"New Project :(",NULL,NULL);
    if(!window)
    {
        printf("term");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}