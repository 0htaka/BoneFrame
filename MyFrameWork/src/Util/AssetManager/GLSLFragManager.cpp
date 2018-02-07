#include "GLSLFragManager.h"

GLSLFragManager::AssetUPtr GLSLFragManager::OnLoad(const std::string & filePath)
{
	return std::make_unique<GLSLShader>(GL_FRAGMENT_SHADER, filePath);
}
