#pragma once

#include "core.h"
#include "math1.h"
namespace Minecraft{

        struct ShaderProgram{
            uint32_t programId;

            bool compileAndlink(const char* vertexfile,const char* fragmentfile);
            void bind() const;
            void unbind() const;
            void destroy();

            void uploadVec4(const char* varname,const glm::vec4& value) const;
            void uploadVec3(const char* varname,const glm::vec3& value) const;
            void uploadVec2(const char* varname,const glm::vec2& value) const;
            void uploadIVec4(const char* varnmae,const glm::ivec4& value) const;
            void uploadIVec3(const char* varnmae,const glm::ivec3& value) const;
            void uploadIVec2(const char* varnmae,const glm::ivec2& value) const;
            void uploadFloat(const char* varname,float) const;
            void uploadInt(const char* varname,int) const;
            void uploadIntArray(const char* varName, int length, const int* array) const;
		    void uploadUInt(const char* varName, uint32_t value) const;
		    void uploadBool(const char* varName, bool value) const;

		    void uploadMat4(const char* varName, const glm::mat4& mat4) const;
		    void uploadMat3(const char* varName, const glm::mat3& mat3) const;

            static void clearAllShaderVariables();
        };
    
}