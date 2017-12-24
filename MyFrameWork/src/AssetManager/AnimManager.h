#pragma once

#include "Base/LoadablesManager.h"
#include "Render/Animation.h"
#include <string>

//using AnimManager = LoadablesManager<AnimManager, Animation>;

class AnimManager : public LoadablesManager<AnimManager, Animation> {
//protected:
//	void OnLoad(const std::string& filePath) override;
};