#pragma once

#include "Base/LoadablesManager.h"
#include "Util/Render/GLSLShader.h"

class GLSLFragManager : public LoadablesManager<GLSLFragManager, GLSLShader> {
protected:
	AssetUPtr OnLoad(const std::string& filePath) override;
};