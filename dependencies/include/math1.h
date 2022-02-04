    #pragma once
    
    #include "glm/vec3.hpp"
    #include "glm/vec4.hpp"

    namespace Minecraft{namespace Math{
        
        struct Vertex
        {
            glm::vec4 color;
            glm::vec3 position;
        };
    }}