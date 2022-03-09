#include "core/application.hpp"

namespace Minecraft{namespace Application
{
    GLFWwindow* window;
    void ProcessInput(GLFWwindow* window);
    
    static Shader shader;
    
    bool b1_draw=false;
    bool b2_draw=false;
    bool b3_draw=false;
    bool b4_draw=false;

    bool Init()
    {
         glfwInit();

        window= window::create();
        glfwMakeContextCurrent(window);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("failed to initialize glad");
            return -1;
        }
        
        shader.compile();

        glViewport(0,0,800,600);
        shader.bind();
        glfwSetKeyCallback(window,input::key_callback);
        glfwSetMouseButtonCallback(window,input::mouse_button_callback);
        Ch1::SetUp();
        Ch2::SetUp();
        Ch3::SetUp();
        Ch4::SetUp();
        return 1;
    }
    void Run()
    {
       
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

            Ch1::Bind();
            b1_draw = true;
        }
        if(input::key_down(GLFW_KEY_2))
        {
            DeleteAll();
            glUniform1i(glGetUniformLocation(shader.programId, "Texture1"), 0);
            glUniform1i(glGetUniformLocation(shader.programId, "Texture2"), 1);

            Ch2::Bind();
            b2_draw=true;
        }
        if(input::key_down(GLFW_KEY_3))
        {
            DeleteAll();

            Ch3::Bind();
            b3_draw=true;
        }
         if(input::key_down(GLFW_KEY_4))
        {
            DeleteAll();

            Ch4::Bind();
            b4_draw=true;
        }
        if (input::key_down(GLFW_KEY_DELETE))
        {
            DeleteAll();
        }
    }
   
}
}