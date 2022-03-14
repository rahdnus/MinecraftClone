#include "core/application.hpp"

namespace Minecraft{namespace Application
{
    GLFWwindow* window;
    void ProcessInput(GLFWwindow* window);
    void mouse_callback(GLFWwindow* window,double xpos,double ypos);

    static Shader shader;

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  -10.0f), 
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
    

    glm::vec3 CameraPos{0,0,10};
    glm::vec3 CameraCenter{0,0,-1};
    glm::vec3 CameraUp{0,1,0};
    float lastFrame=0.0f;
    float deltatime=0.0f;

    float yaw=-90,pitch=0.0f;

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
        glfwSetCursorPosCallback(window,mouse_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        // Ch1::SetUp();
        Ch2::SetUp();
        // Ch3::SetUp();
        // Ch4::SetUp();
        return 1;
    }

    void Run()
    {
        glEnable(GL_DEPTH_TEST); 
        while (!glfwWindowShouldClose(window))
        {
            
            float currentFrame=glfwGetTime();
            deltatime=currentFrame-lastFrame;
            lastFrame=currentFrame;
            glClearColor(0.2f, 0.2f, 0.2f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

            glm::mat4 view;
            view = glm::lookAt(CameraPos, CameraPos+CameraCenter,CameraUp);
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

          
            int viewLoc = glGetUniformLocation(shader.programId, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
            int projectionLoc = glGetUniformLocation(shader.programId, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            glUniform1i(glGetUniformLocation(shader.programId, "Texture1"), 0);
            glUniform1i(glGetUniformLocation(shader.programId, "Texture2"), 1);
            Ch2::Bind();
            
            for (unsigned int i = 1; i < 10; i++)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                float angle = 20.0f * i;
                model = glm::rotate(model,glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                int modelLoc = glGetUniformLocation(shader.programId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

                Ch2::Draw();
            }
            
            ProcessInput(window);
        
                
            glfwSwapBuffers(window);
            glfwPollEvents();
           
        }
        glfwTerminate();
    }
    
    void ProcessInput(GLFWwindow* window)
    {
        float cameraSpeed=2.5f*deltatime;
        if (input::key_down(GLFW_KEY_ESCAPE)){glfwSetWindowShouldClose(window, true);}

        if (input::key_down(GLFW_KEY_F11)){window::toggleFullscreen(window);}
        if(glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS)
        {
            CameraPos += cameraSpeed * CameraCenter;
        }
          if(glfwGetKey(window,GLFW_KEY_A)==GLFW_PRESS)
        {
            CameraPos -= cameraSpeed * glm::normalize(glm::cross( CameraCenter,CameraUp));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            CameraPos -= cameraSpeed * CameraCenter;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            CameraPos += cameraSpeed * glm::normalize(glm::cross(CameraCenter, CameraUp));
        }

      
    }
    bool first=true;
    float sensitivity=0.1f;
    float lastx , lasty;
    void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
    {

        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
        float xoffset, yoffset;
        
        if (first)
        {
            lastx = xpos;
            lasty = ypos;
            first = false;
        }

        xoffset = xpos - lastx;
        yoffset = lasty - ypos;
         lastx = xpos;
        lasty = ypos;

        xoffset*=sensitivity;
        yoffset*=sensitivity;
        yaw += xoffset;
        pitch += yoffset;
       

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        CameraCenter = glm::normalize(direction);
    }
}
}