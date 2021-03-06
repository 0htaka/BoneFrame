#pragma once

#include "Base/LoadablesManager.h"
#include "Util/Render/Animation.h"
#include <string>

class AnimManager : public LoadablesManager<AnimManager, Animation> {
	//protected:
	//	void OnLoad(const std::string& filePath) override;
};

//template<>
//void LoadablesManager<AnimManager, Animation>::OnLoad(const std::string& filePath) {
//	auto temp = std::make_unique<Animation>(filePath);
//	mAssets.emplace(GetFileName(filePath), temp);
//}