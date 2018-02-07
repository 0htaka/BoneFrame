#pragma once

#include "Base/LoadablesManager.h"
#include "Util/Render/GLSLShader.h"

class GLSLFragManager : public LoadablesManagerBase<GLSLFragManager, GLSLShader> {
protected:
	AssetUPtr OnLoad(const std::string& filePath) override;
};