#include "GLSLVertManager.h"

GLSLVertManager::AssetUPtr GLSLVertManager::OnLoad(const std::string & filePath)
{
	return std::make_unique<GLSLShader>(GL_VERTEX_SHADER, filePath);	
}
