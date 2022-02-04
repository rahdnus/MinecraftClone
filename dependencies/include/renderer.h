#pragma once

#include "core.h"

namespace MinecraftClone
{
	struct Shader
	{
		uint32_t programId;

		void bind();
		void compile();
	};
}