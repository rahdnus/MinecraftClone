    #pragma once
        #include "glm/vec2.hpp"
    #include "glm/vec3.hpp"
    #include "glm/vec4.hpp"
    #include "glm/mat4x4.hpp"
    #include"glm/gtc/type_ptr.hpp"
    #include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// #include "glm/integer.hpp"

namespace core
{
    namespace Math
    {
        
        struct Vertex
        {
            glm::vec4 color;
            glm::vec3 position;
            glm::vec2 texcoords;
            glm::vec3 normal;
        };
    }}