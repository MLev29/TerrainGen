#include "ResourceManager.h"

void src::ResourceManager::LoadShader(const char* shaderProgramName, const char* vertShader, const char* fragShader)
{
	if (GetInstance()->HasResource(shaderProgramName))
	{
		std::printf("Failed to load shader '%s', shader already exists.\n", shaderProgramName);
		return;
	}

	// TODO: load shader...
}

void src::ResourceManager::Unload(std::string const& fileName)
{
	if (GetInstance()->HasResource(fileName))
	{
		delete GetInstance()->m_resources[fileName];
		std::printf("Successfully unloaded resource '%s'.\n", fileName.c_str());
	}
	else
		std::printf("Failed to unload resource '%s', resource was not found.\n", fileName.c_str());
}

void src::ResourceManager::ShutDown(void)
{
	for (auto resource : GetInstance()->m_resources)
		Unload(resource.first);

	delete m_instance;
	m_instance = nullptr;
}

bool src::ResourceManager::HasResource(std::string const& fileName)
{
	return GetInstance()->m_resources.contains(fileName);
}

src::ResourceManager* src::ResourceManager::GetInstance(void)
{
	if (!m_instance)
		m_instance = new ResourceManager();

	return m_instance;
}
