#include <core/Application.hpp>
#include <Renderer/ShaderProgram.hpp>
#include <core/Object.hpp>

using namespace Engine;
ShaderProgram shaderProgram;
GLuint VAO_ID, VBO_ID, EBO_ID;

struct MEGA
{
    GLuint VAO_ID, VBO_ID, EBO_ID;
    Vertex* vertex;
    GLuint* indices;
    MEGA(Vertex* vertex, GLuint* indices)
    {
        this->vertex=vertex;
        this->indices=indices;
        // vertex=(Vertex*)malloc(sizeof(Vertex)*4);
        // vertex[0] = {glm::vec3(0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)};
        // vertex[1] = {glm::vec3(-0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)};
        // vertex[2] = {glm::vec3(-0.5f, -0.5f, 0), glm::vec4(1, 0, 1, 1)};
        // vertex[3] = {glm::vec3(0.5f, -0.5f, 0), glm::vec4(0, 1, 1, 1)};

        // indices=(GLuint*)malloc(sizeof(GLuint)*6);
        // indices[0]=0;
        // indices[1]=1;
        // indices[2]=3;
        // indices[3]=1;
        // indices[4]=2;
        // indices[5]=3;
    }
};
int Application::windowInit(GLuint width, GLuint height, std::string name)
{

    mywindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!mywindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(mywindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}
int Application::run()
{
    shaderProgram.compile("Shaders/SimpleVert.glsl","Shaders/SimpleFrag.glsl");

    Vertex vertex[4] = {
        {glm::vec3(0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},   // 0
        {glm::vec3(-0.5f, 0.5f, 0), glm::vec4(1, 0, 1, 1)},  // 1
        {glm::vec3(-0.5f, -0.5f, 0), glm::vec4(1, 0, 1, 1)}, // 2
        {glm::vec3(0.5f, -0.5f, 0), glm::vec4(0, 1, 1, 1)}   // 3

    };
    GLuint indices[]{
        0, 1, 3,
        1, 2, 3};
    // Mesh *mesh=new Mesh(vertex, indices);
    // mesh->Init();
    MEGA m(vertex,indices);

    glCreateVertexArrays(1, &m.VAO_ID);
    glBindVertexArray(m.VAO_ID);

    glCreateBuffers(1, &m.VBO_ID);
    glBindBuffer(GL_ARRAY_BUFFER, m.VBO_ID);

    int vertlength=sizeof(m.vertex);

    Vertex Vertices[vertlength];
    for(int i=0;i<vertlength;i++)
    {
        Vertices[i]=m.vertex[i];
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

    glCreateBuffers(1, &m.EBO_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.EBO_ID);
    int indlength=sizeof(m.indices);
    printf("\nLENGTH:%d",indlength);
    GLuint Indices[indlength];
    for(int i=0;i<indlength;i++)
    {
        Indices[i]=m.indices[i];
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(mywindow))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(m.VAO_ID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        shaderProgram.bind();
        // mesh->Bind();
        // mesh->Draw();

        glfwSwapBuffers(mywindow);
        glfwPollEvents();
    }
}
