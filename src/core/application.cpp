#include "core/application.hpp"

namespace Minecraft{namespace Application
{
    GLFWwindow* window;
    void ProcessInput(GLFWwindow* window);
    
    static Shader shader;

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
        // Ch1::SetUp();
        Ch2::SetUp();
        // Ch3::SetUp();
        // Ch4::SetUp();
        return 1;
    }
    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
};
    void Run()
    {
        glEnable(GL_DEPTH_TEST); 
        while (!glfwWindowShouldClose(window))
        {
            glClearColor(0.2f, 0.2f, 0.2f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
            
            // glm::mat4 trans = glm::mat4(1.0f);
            // trans=glm::translate(trans,glm::vec3(0.5f,-0.5f,0));
            // trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
            // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
            
            glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);      

            glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
            
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
            glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

            glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

            const float radius = 10.0f;
            float camX = sin(glfwGetTime()) * radius;
            float camZ = cos(glfwGetTime()) * radius;
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

          
               int viewLoc = glGetUniformLocation(shader.programId, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projectionLoc = glGetUniformLocation(shader.programId, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform1i(glGetUniformLocation(shader.programId, "Texture1"), 0);
            glUniform1i(glGetUniformLocation(shader.programId, "Texture2"), 1);
            // unsigned int transformLoc = glGetUniformLocation(shader.programId, "transform");
            // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
            Ch2::Bind();
            
            for (unsigned int i = 1; i < 11; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                 model = glm::rotate(model,glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                int modelLoc = glGetUniformLocation(shader.programId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                Ch2::Draw();
            }
            
       



            
            // Ch2::Draw();
            
            ProcessInput(window);
            /*if(b1_draw)
                Ch1::Draw();
            // if(b2_draw)
            //     Ch2::Draw();
            if(b3_draw)
                Ch3::Draw();
            if(b4_draw)
                Ch4::Draw();
                */
            glfwSwapBuffers(window);
            glfwPollEvents();
           
        }
        glfwTerminate();
    }
    
    // void DeleteAll()
    // {
    //         b1_draw = false;
    //         b2_draw = false;
    //         b3_draw=false;
    //         b4_draw=false;
    //     Ch1::Delete();
    //     Ch2::Delete();
    //     Ch3::Delete();
    //     Ch4::Delete();
    // }
    void ProcessInput(GLFWwindow* window)
    {
        if (input::key_down(GLFW_KEY_ESCAPE)){glfwSetWindowShouldClose(window, true);}

        if (input::key_down(GLFW_KEY_F11)){window::toggleFullscreen(window);}
        /*
        
        // if (input::key_down(GLFW_KEY_1))
        // {
        //     DeleteAll();

        //     Ch1::Bind();
        //     b1_draw = true;
        // }
        // if(input::key_down(GLFW_KEY_2))
        // {
        //     DeleteAll();
        //     glm::mat4 trans = glm::mat4(1.0f);
        //     trans=glm::translate(trans,glm::vec3(0.5f,-0.5f,0));
        //     trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
        //     trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));  
            
        //     unsigned int transformLoc = glGetUniformLocation(shader.programId, "transform");
        //     glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        //     glUniform1i(glGetUniformLocation(shader.programId, "Texture1"), 0);
        //     glUniform1i(glGetUniformLocation(shader.programId, "Texture2"), 1);

        //     Ch2::Bind();
        //     // b2_draw=true;
        // }
        // if(input::key_down(GLFW_KEY_3))
        // {
        //     DeleteAll();

        //     Ch3::Bind();
        //     b3_draw=true;
        // }
        //  if(input::key_down(GLFW_KEY_4))
        // {
        //     DeleteAll();

        //     Ch4::Bind();
        //     b4_draw=true;
        // }
        // if (input::key_down(GLFW_KEY_DELETE))
        // {
        //     DeleteAll();
        // }
        */
    }
   
}
}