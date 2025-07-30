#pragma once

namespace src
{
	class IResource
	{
	public:
		IResource(void) = default;
		virtual ~IResource(void) = default;

		virtual bool LoadResource(const char* filePath) = 0;
	};
}