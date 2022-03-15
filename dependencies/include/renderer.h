#pragma once

#include "core.h"

namespace Minecraft
{
	struct Shader
	{
		uint32_t programId;

		void bind();
		void compile(const char* ,const char* );
	};
}