#include<core/Object.hpp>
using namespace Engine;

void Mesh::Init()
{
    printf("\nVERTEX0:%s\n",glm::to_string(vertex[0].position).c_str());
}
