#pragma once

#include "Resource.h"

#include <string>
#include <unordered_map>

namespace src
{
	class ResourceManager
	{
	public:
		template<typename TResourceType>
		static TResourceType* GetResource(std::string const& fileName);
		
		template<typename TResourceType>
		static TResourceType* Load(std::string const& fileName);

		static class ShaderProgram* LoadShader(
			const char* shaderProgramName,
			const char* vertShader,
			const char* fragShader
		);

		static void Unload(std::string const& fileName);
		static void ShutDown(void);

	private:
		ResourceManager(void) = default;
		ResourceManager(ResourceManager const& rManager) = delete;
		ResourceManager& operator=(ResourceManager const& rManager) = delete;

		static bool HasResource(std::string const& fileName);
		static ResourceManager* GetInstance(void);
		static ResourceManager* m_instance;

		std::unordered_map<std::string, IResource*> m_resources;
	};

	template<typename TResourceType>
	inline TResourceType* ResourceManager::GetResource(std::string const& fileName)
	{
		bool hasResource = GetInstance()->m_resources.contains(fileName);

		return (hasResource) ? 
					dynamic_cast<TResourceType*>(GetInstance()->m_resources[fileName]) :
					nullptr;
	}

	template<typename TResourceType>
	inline TResourceType* ResourceManager::Load(std::string const& fileName)
	{
		if (!GetInstance()->HasResource(fileName))
		{
			GetInstance()->m_resources[fileName] = new TResourceType();
			GetInstance()->m_resources[fileName]->LoadResource(fileName.c_str());

			std::printf("Successfully loaded resource '%s'.\n", fileName.c_str());

			return GetInstance()->GetResource<TResourceType>(fileName);
		}
		else
			std::printf("Failed to load resource, resource already loaded.\n");

		return nullptr;
	}
}