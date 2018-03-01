#pragma once

#include <functional>
#include "Animation.h"

class AnimationManager {
	class Branch {
	public:
		Branch(Animation* anim, Animation* anim2, std::function<bool(Animation& anim)> isChage = [](Animation& anim) { return anim.; });
		bool IsChage();
	private:
		Animation * mNode1;
		Animation* mNode2;
		std::function<bool(Animation& anim)> mIsChage;
	};
public:
	void Update(float dt);
	void Add(Branch branch);
	void GetAnim(std::string name);
};
