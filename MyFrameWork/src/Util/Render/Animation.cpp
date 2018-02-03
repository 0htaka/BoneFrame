// Animation.cpp
#include "Animation.h"
#include <fstream>
#include <algorithm>
#include "Util/Time.h"

inline std::pair<int, int> findKeyFrameSegment(const std::vector<Animation::KeyFrame>& keys, float deltaSec);

// コンストラクタ
Animation::Animation() {
}

Animation::Animation(const std::string & filePath) {
	Load(filePath);
}

// 指定ボーンのアニメーション変換行列を求める
Animation::KeyFrame Animation::GetKeyFrame(const std::string& boneName, float deltaSec) const {
	float frameNo = deltaSec * Time::TargetFPS();
	const auto keys = mBoneKeyFrames.find(boneName);
	KeyFrame result;
	if (keys == mBoneKeyFrames.end()) {
		// アニメーションキーが存在しない場合
		result.frameNo = frameNo;
		result.scale = Vector3(1.0f, 1.0f, 1.0f);
		result.rotate = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		result.position = Vector3(0.0f, 0.0f, 0.0f);
		return result;
	}
	const auto& segment = findKeyFrameSegment(keys->second, frameNo);
	if (segment.first == segment.second) {
		return keys->second[segment.first];
	}
	const auto& first = keys->second[segment.first];
	const auto& second = keys->second[segment.second];
	const float t = (frameNo - first.frameNo) / (second.frameNo - first.frameNo);
	result.frameNo = frameNo;
	result.scale = Vector3::Lerp(first.scale, second.scale, t);
	result.rotate = Quaternion::Slerp(first.rotate, second.rotate, t);
	result.position = Vector3::Lerp(first.position, second.position, t);
	return result;
}

// 消去
void Animation::Clear() {
	mBoneKeyFrames.clear();
}

// ファイルから読み込む
void Animation::Load(const std::string& fileName) {
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		throw std::runtime_error("can not open " + fileName);
	}
	Clear();
	unsigned int bone_frame_size = 0;
	auto temp3 = sizeof(bone_frame_size);
	file.read((char*)&bone_frame_size, sizeof(bone_frame_size));
	for (unsigned int i = 0; i < bone_frame_size; ++i) {
		char bone_name[32];
		auto temp2 = sizeof(bone_name);
		file.read(bone_name, sizeof(bone_name));

		unsigned int key_frame_size = 0;
		file.read((char*)&key_frame_size, sizeof(key_frame_size));
		mBoneKeyFrames[bone_name].resize(key_frame_size);
		unsigned int temp = sizeof(KeyFrame) * key_frame_size;
		file.read((char*)mBoneKeyFrames[bone_name].data(), sizeof(KeyFrame) * key_frame_size);
	}
}

// 終了フレーム数を返す
float Animation::EndTime() const {
	float result = 0.0f;
	for (const auto& keys : mBoneKeyFrames) {
		result = std::max(result, keys.second.back().frameNo);
	}
	return result / Time::TargetFPS();
}

// 変換行列を計算する
Matrix Animation::KeyFrame::matrix() const {
	return Matrix::CreateWorld(scale, rotate, position);
}


// キーフレームの区間を検索
inline std::pair<int, int> findKeyFrameSegment(const std::vector<Animation::KeyFrame>& keys, float deltaSec) {
	int start = 0;
	int end = (int)keys.size() - 1;
	if (keys[start].frameNo >= deltaSec) {
		return std::pair<int, int>(start, start);
	}
	if (keys[end].frameNo <= deltaSec) {
		return std::pair<int, int>(end, end);
	}
	while ((start + 1) < end) {
		const int mid = (start + end) / 2;
		if (keys[mid].frameNo == deltaSec) {
			return std::pair<int, int>(mid, mid);
		}
		else if (keys[mid].frameNo < deltaSec) {
			start = mid;
		}
		else {
			end = mid;
		}
	}
	return std::pair<int, int>(start, end);
}

