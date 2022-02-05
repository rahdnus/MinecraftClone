    #include "core.h"
    #include "core/window.h"
    #include "core/input.h"
    #include "math1.h"
    #include "renderer.h"
    #include "challenge.hpp"

    using namespace Minecraft;
    
    void ProcessInput(GLFWwindow* window);
    
    static Shader shader;

    bool Minecraft::b1_draw=false;
    bool Minecraft::b2_draw=false;
    bool Minecraft::b3_draw=false;
    bool Minecraft::b4_draw=false;


    int main()
    {
        glfwInit();
     
        GLFWwindow* window= window::create();

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
        shader.compile();
      
        glViewport(0,0,800,600);
      
        shader.bind();
        
        glfwSetKeyCallback(window,input::key_callback);
        glfwSetMouseButtonCallback(window,input::mouse_button_callback);

        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.2f, 0.2f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ProcessInput(window);
            if(b1_draw)
                Ch1::Draw();
            if(b2_draw)
                Ch2::Draw();
            if(b3_draw)
                Ch3::Draw();
            if(b4_draw)
                Ch4::Draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
           
        }
        glfwTerminate();
        return 0;
    }
     void DeleteAll()
    {
            b1_draw = false;
            b2_draw = false;
            b3_draw=false;
            b4_draw=false;
        Ch1::Delete();
        Ch2::Delete();
        Ch3::Delete();
        Ch4::Delete();
    }

    void ProcessInput(GLFWwindow* window)
    {
        if (input::key_down(GLFW_KEY_ESCAPE)){glfwSetWindowShouldClose(window, true);}
        if (input::key_down(GLFW_KEY_F11)){window::toggleFullscreen(window);}
        
        if (input::key_down(GLFW_KEY_1))
        {
            DeleteAll();

            Ch1::SetUp();
            b1_draw = true;
        }
        if(input::key_down(GLFW_KEY_2))
        {
            DeleteAll();

            Ch2::SetUp();
            b2_draw=true;
        }
        if(input::key_down(GLFW_KEY_3))
        {
            DeleteAll();

            Ch3::SetUp();
            b3_draw=true;
        }
         if(input::key_down(GLFW_KEY_4))
        {
            DeleteAll();

            Ch4::SetUp();
            b4_draw=true;
        }
        if (input::key_down(GLFW_KEY_DELETE))
        {
            DeleteAll();
            
        
        }
    }
   
