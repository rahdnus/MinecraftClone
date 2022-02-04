    #include "core.h"
    #include "core/window.h"
    #include "core/input.h"
    #include "glm/vec3.hpp"
    #include "glm/vec4.hpp"
    #include "renderer.h"

    void ProcessInput(GLFWwindow* window);
    void Draw();

    static MinecraftClone::Shader shader;

    struct Vertex
    {
        glm::vec4 color;
        glm::vec3 pos;
    }; 
     GLuint vaoID;
    GLuint vboID;
       Vertex vertexarray[]=
        {
            {glm::vec4(1,1,1,1),glm::vec3(0.5f,-0.5f,0)},
            {glm::vec4(1,1,1,1),glm::vec3(-0.5f,0.5f,0)},
            {glm::vec4(1,1,1,1),glm::vec3(0.5f,0.5f,0)}

        };
        bool draw=false;
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
            if(draw)
                Draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
           
        }
        glfwTerminate();
        return 0;
    }

    void ProcessInput(GLFWwindow* window)
    {
         if(input::key_down(GLFW_KEY_ESCAPE))
           {
               glfwSetWindowShouldClose(window,true);
           }
           if(glfwGetKey(window,GLFW_KEY_F11))
           {
               window::toggleFullscreen(window);
           }
           if(input::mouse_down(GLFW_MOUSE_BUTTON_1))
           {
                draw=true;

           } if(input::mouse_down(GLFW_MOUSE_BUTTON_2))
           {
                glDeleteBuffers(1,&vboID);
                glDeleteVertexArrays(1,&vaoID);
                draw=false;

           }
    }
    void Draw()
    {
            glCreateVertexArrays(1, &vaoID);
                glBindVertexArray(vaoID);

                    glCreateBuffers(1, &vboID);
                    glBindBuffer(GL_ARRAY_BUFFER, vboID);
                    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);

                    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
                    glEnableVertexAttribArray(0);

                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, pos));
                    glEnableVertexAttribArray(1);

                glBindVertexArray(vaoID);
                glDrawArrays(GL_TRIANGLES,0,3);
    }
