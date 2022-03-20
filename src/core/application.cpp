#include "core/application.hpp"

namespace Minecraft{namespace Application
{
    GLFWwindow* window;
    void ProcessInput(GLFWwindow* window);
    void mouse_callback(GLFWwindow* window,double xpos,double ypos);

    static Shader shader;
    static Shader light;

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
        const char* fragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 FragPos;
in vec4 fColor;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);     
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength=0.5;

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  


    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    
    vec3 result=(diff+ambient+specular)*objectColor;
    FragColor=vec4(result,1.0);
    

})";
// FragColor = mix(texture(Texture1,TexCoord),texture(Texture2,TexCoord),0.2)*vec4(lightColor*objectColor,1.0);
       const char* lightfragmentShaderSource = R"(
#version 460 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
})";
    const char* vertexShaderSource = R"(
#version 460 core
layout (location = 0) in vec4 aColor;
layout (location = 1) in vec3 aPosition;
layout(location=2) in vec2 aTexCoords;
layout(location=3) in vec3 aNormal;

out vec4 fColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fColor = aColor;
    gl_Position = projection * view * model * vec4(aPosition, 1.0);
    FragPos=vec3(model*vec4(aPosition,1.0));
    TexCoord=aTexCoords;
    Normal = mat3(transpose(inverse(model))) * aNormal; 
})";
  Math::Vertex vertex[] = {{glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(  0.0f,  0.0f, -1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  0.0f, -1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, -1.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  0.0f, 1.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  0.0f, 1.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(1.0f,  0.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f, -1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f, -1.0f,  0.0f)},

                       {glm::vec4(1, 1, 0, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 1, 0, 1), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(1, 0, 1, 1), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f),glm::vec3(0.0f,  1.0f,  0.0f)},
                       {glm::vec4(0, 1, 1, 1), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f),glm::vec3(0.0f,  1.0f,  0.0f)}};
  
 
    glm::vec3 CameraPos{0,0,10};
    glm::vec3 CameraCenter{0,0,-1};
    glm::vec3 CameraUp{0,1,0};
    float lastFrame=0.0f;
    float deltatime=0.0f;
    
    float yaw=-90,pitch=0.0f;

    GLuint VAO,VBO;

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
        
        shader.compile(vertexShaderSource,fragmentShaderSource);
        light.compile(vertexShaderSource,lightfragmentShaderSource);

        glViewport(0,0,800,600);
        shader.bind();
        glfwSetKeyCallback(window,input::key_callback);
        glfwSetMouseButtonCallback(window,input::mouse_button_callback);
        glfwSetCursorPosCallback(window,mouse_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
        // Ch1::SetUp();
        Ch2::SetUp();
            glUniform3f(glGetUniformLocation(shader.programId, "lightPos"),10,10,10);

         light.bind();
        glCreateVertexArrays(1,&VAO);
        glBindVertexArray(VAO);
        glCreateBuffers(1,&VBO);
        glBindBuffer(GL_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

        
        glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,sizeof(Math::Vertex),(void*)offsetof(Math::Vertex,color));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Math::Vertex),(void*)offsetof(Math::Vertex,position));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Math::Vertex),(void*)offsetof(Math::Vertex,texcoords));
        glEnableVertexAttribArray(2);  
        glBindVertexArray(0);

        // Ch3::SetUp();
        // Ch4::SetUp();
        return 1;
    }

    void Run()
    {

        glEnable(GL_DEPTH_TEST); 
        while (!glfwWindowShouldClose(window))
        {
            shader.bind();
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

            glUniform3f(glGetUniformLocation(shader.programId, "objectColor"),0.5f,0.5f,0.7f);
            glUniform3f(glGetUniformLocation(shader.programId, "lightColor"),1.0f,1.0f,0.2f);
            glUniform3f(glGetUniformLocation(shader.programId,"cameraPos"),CameraPos.x,CameraPos.y,CameraPos.z);
        
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
            light.bind();

            glBindVertexArray(VAO);
            viewLoc = glGetUniformLocation(light.programId, "view");
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

            projectionLoc = glGetUniformLocation(light.programId, "projection");
            glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
            // glUniform1i(glGetUniformLocation(light.programId, "Texture1"), 0);
            // glUniform1i(glGetUniformLocation(light.programId, "Texture2"), 1);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3{10,10,10});
                float angle = 20.0f ;
                model = glm::rotate(model,glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
                int modelLoc = glGetUniformLocation(light.programId, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES,0,36);

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