#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_

#include "../Base/Actor.h"

//�N�\�[�X�@���ƂŏC��
class Camera : public Actor
{
public:
	Camera();

	void OnUpdate(float deltaTime) override;
	void Move(
		const Vector3& restPosition,	//�o�l�̐Î~�ʒu
		float stiffness,				//�o�l�萔�i�o�l�̋����j
		float friction,					//���C��
		float mass						//����
	);
	///<summary>�J�����̎�����ɂ��邩�ǂ���</summary>
	///<param name ='position'>���肷��I�u�W�F�N�g�̈ʒu</param>
	///<param name ='angle'>���������ǂꂭ�炢�܂ł����e���邩</param>
	bool IsView(const Vector3& position, const float& angle = 0.0f);
private:

};

#endif