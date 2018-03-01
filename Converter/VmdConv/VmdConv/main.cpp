#include"VMDFileReader.h"
#include<string>
#include<filesystem>
#include<algorithm>
#include<map>
#include"Math\Vector3.h"
#include"Math\Matrix.h"
#include"Math\Quaternion.h"

struct KeyFrame {
	float			frameNo;
	Vector3			scale;
	Quaternion		rotate;
	Vector3			position;
};

//�{�[���t���[��
using BoneFrame = std::map<std::string, mmd::vmd::Motions>;

//�{�[���t���[���쐬
BoneFrame create_bone_frame(const mmd::vmd::VMDFile& vmd) {
	BoneFrame result;
	//�{�[�������ɃL�[�t���[�����쐬
	for (const auto& motion : vmd.motions)
	{		
		result[motion.bone_name].push_back(motion);
	}
	//�t���[���ԍ����Ƀ\�[�g
	for (auto& key_frame : result) {
		std::sort(key_frame.second.begin(), key_frame.second.end(),
			[](auto&& m1, auto&& m2) {	return m1.frame_no < m2.frame_no;	});
	}
	return result;
}


//�A�j���[�V�����t�@�C���o��
void output_simple_animation(const std::string& simple_anim_file_name, const mmd::vmd::VMDFile& vmd) {
	std::ofstream file(simple_anim_file_name, std::ios::binary);
	const auto& bone_frame = create_bone_frame(vmd);
	unsigned int bone_frame_size = bone_frame.size();
	file.write((const char*)&bone_frame_size, sizeof(bone_frame_size));
	for (const auto& pair : bone_frame) {
		char bone_name[32];
		strcpy_s(bone_name, pair.first.c_str());
		file.write(bone_name, sizeof(bone_name));
		unsigned int key_frame_size = pair.second.size();
		file.write((const char*)&key_frame_size, sizeof(key_frame_size));
		for (const auto& motion : pair.second) {
			KeyFrame key_frame;
			key_frame.frameNo = motion.frame_no * 2.0f;//60�t���[����
			key_frame.scale = Vector3::One;
			key_frame.rotate = Quaternion(-motion.rotation.x, -motion.rotation.y, motion.rotation.z, motion.rotation.w);
			key_frame.position = Vector3(motion.location.x, motion.location.y, -motion.location.z);
			file.write((const char*)&key_frame, sizeof(key_frame));
		}
	}
}

int main(int argc, const char* argv[]) {
	if (argc < 3) return 1;
	//���̓t�@�C���̏�����
	std::string vmd_file_name = argv[1];
	//�o�̓t�@�C����������
	std::string out_anim_file_name = argv[2];
	//VMD�f�[�^�̓ǂݍ���
	mmd::vmd::VMDFile vmd;
	mmd::vmd::VMDFileReader(vmd).read(vmd_file_name);
	//�A�j���[�V�����t�@�C���̏o��
	output_simple_animation(out_anim_file_name, vmd);

	return 0;
}