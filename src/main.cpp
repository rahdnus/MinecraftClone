    #include "core.h"
    #include "core/window.h"
    #include "core/input.h"

    int main()
    {
       glfwInit();

        GLFWwindow* window= window::create();

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }

        glfwSetKeyCallback(window,input::key_callback);
        glfwSetMouseButtonCallback(window,input::mouse_button_callback);
        
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(1.0f, 1.f, 0.0f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            //TODO:check input here//
           if(input::key_down(GLFW_KEY_ESCAPE))
           {
               glfwSetWindowShouldClose(window,true);
           }
           if(glfwGetKey(window,GLFW_KEY_F11))
           {
               window::toggleFullscreen(window);
           }
           if(input::mouse_down(GLFW_MOUSE_BUTTON_LAST))
           {
               
           }
            glfwSwapBuffers(window);
            glfwPollEvents();
           
        }
        glfwTerminate();
        return 0;
    }