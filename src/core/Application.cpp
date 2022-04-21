
#include<core/Application.hpp>
#include<Renderer/ShaderProgram.hpp>

using namespace Core;

    GLuint VAO_ID,VBO_ID,EBO_ID;

Vertex vertex[4]={
    {glm::vec3(0.5f,0.5f,0),glm::vec4(1,0,1,1)},//0
    {glm::vec3(-0.5f,0.5f,0),glm::vec4(1,0,1,1)},//1
    {glm::vec3(-0.5f,-0.5f,0),glm::vec4(1,0,1,1)},//2
    {glm::vec3(0.5f,-0.5f,0),glm::vec4(0,1,1,1)}//3

};
GLuint indices[]
{
    0,1,3,
    1,2,3
};
ShaderProgram program;
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
    
    program.compile("Shaders/SimpleVert.glsl","Shaders/SimpleFrag.glsl");

    glCreateVertexArrays(1,&VAO_ID);
    glBindVertexArray(VAO_ID);
    
    glCreateBuffers(1,&VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER,VBO_ID);
    
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);
    glCreateBuffers(1,&EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);



}
int Application::run()
{
    while(!glfwWindowShouldClose(mywindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        program.bind();
        glBindVertexArray(VAO_ID);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}
