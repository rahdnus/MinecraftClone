#pragma once

#include "core.h"
#include "math1.h"
namespace Minecraft{

    extern bool b1_draw;
        extern bool b2_draw;

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
}
