#pragma once

#include "Base/LoadablesManager.h"
#include "Util/Render/GLSLShader.h"

class GLSLVertManager : public LoadablesManager<GLSLVertManager, GLSLShader> {
protected:
	AssetUPtr OnLoad(const std::string& filePath) override;
};