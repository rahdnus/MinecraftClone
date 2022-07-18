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
            int Vno,Ino;
            Mesh()
            {
                this->vertex=nullptr;
                this->indices=nullptr;
                this->Vno=-1;
                this->Ino=-1;
            }
            Mesh(Vertex *vertex,int Vno,GLuint *indices,int Ino)
            {
                this->vertex=vertex;
                this->indices=indices;
                this->Vno=Vno;
                this->Ino=Ino;
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
        public:
            Mesh mesh;
            Transform transform;

           Object(Mesh mesh)
            {
                 this->mesh=mesh;
                this->mesh.Init(); 
            } 
            void Cycle()
            {
                mesh.Bind();
                mesh.Draw();

            }
    }; 


}
