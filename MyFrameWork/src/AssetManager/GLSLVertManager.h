#pragma once

#include "Base\LoadablesManager.h"
#include "Render\GLSLShader.h"

//class GLSLVertManager : public LoadablesManager<GLSLVertManager, GLSLShader> {
//
//};
//
//template<>
//void LoadablesManager<GLSLVertManager, std::unique_ptr<GLSLShader>>::OnLoad(const std::string& filePath) {
//	//std::make_unique<GLSLShader>(GL_VERTEX_SHADER, filePath);
//	//mAssets.emplace(GetFileName(filePath), );
//}