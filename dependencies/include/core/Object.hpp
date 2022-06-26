#pragma once
#include <core.hpp>
#include <math1.h>
#include<Renderer/ShaderProgram.hpp>

namespace Engine
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 color;
    };

    struct Mesh
    {
        private:
   
        public:
             GLuint VAO_ID, VBO_ID, EBO_ID;
            struct Vertex *vertex;
            GLuint *indices;

            Mesh(Vertex *vertex,GLuint *indices)
            {
                this->vertex=vertex;
                this->indices=indices;
            }
            void Init();
            void Bind();
            void Draw();

    };
    struct Transform
    {
        glm::vec3 position;
        glm::vec4 rotation;
        glm::vec3 scale;
        
    };
    class Object
    {
           private:
        public:
            Mesh *mesh;

            Transform transform;
            Object(Mesh *mesh)
            {
                this->mesh=mesh;
            }
            //Components components[]
    };
}
