#pragma once

#include "Base/LoadablesManager.h"
#include "Render/Animation.h"
#include <string>

class AnimManager : public LoadablesManager<AnimManager, Animation> {
	//protected:
	//	void OnLoad(const std::string& filePath) override;
};

template<>
void LoadablesManager<AnimManager, Animation>::OnLoad(const std::string& filePath) {
	mAssets.emplace(GetFileName(filePath), Animation(filePath));
}