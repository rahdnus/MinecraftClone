#pragma once

#include "core.h"
#include "math1.h"
namespace Minecraft{

    extern bool b1_draw;
    extern bool b2_draw;
    extern bool b3_draw;
    extern bool b4_draw;

    namespace Ch1
    {
        extern GLuint Vao_ID;
        extern GLuint Vbo_ID;
        extern Math::Vertex vertex[3];
        
        void SetUp();
        void Draw();
        void Delete();
    }
     namespace Ch2
    {
        extern GLuint Vao_ID;
        extern GLuint Vbo_ID;
        extern GLuint Ebo_ID;

        extern GLuint indices[6];
        
        extern Math::Vertex vertex[4];
        void SetUp();
        void Draw();
        void Delete();
    }
     namespace Ch3
    {
        extern GLuint Vao_ID;
        extern GLuint Vbo_ID;
        extern GLuint Ebo_ID;

        extern GLuint indices[24];
        
        extern Math::Vertex vertex[10];
        void SetUp();
        void Draw();
        void Delete();
    }
      namespace Ch4
    {
        extern GLuint Vao_ID;
        extern GLuint Vbo_ID;
        extern GLuint Ebo_ID;

        extern GLuint indices[8];
        
        extern Math::Vertex vertex[4];
        void SetUp();
        void Draw();
        void Delete();
    }
}
