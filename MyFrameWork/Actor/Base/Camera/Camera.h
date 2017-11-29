#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_

#include"../Actor.h"

//�N�\�[�X�@���ƂŏC��
class Camera : public Actor
{
public:
	Camera(IWorld& world);

	void OnUpdate(float deltaTime) override;
	void OnDraw()const override;
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
	virtual void OnCollide(Actor& other, const HitInfo& info) override;
private:
	//�����_
	Vector3 m_target;
	//�J�����̏����
	Vector3 m_up;
	//�N���A����rotate
	Matrix m_clearRotate;

	//�N���A���Ă���̃^�C�}
	float m_clearTimer;

	/**************************************************************************/
	//���������]�����p�ϐ�
	float m_angleY;//Y���̉�]�p�x

	float m_angleX;//X���̉�]�p�x

	float m_distance;//�v���C���[����̋���

	ActorSPtr m_player;

	//std::shared_ptr<Line3D> m_line;

	//���̓����蔻��̉����o���Ƃ̊Ԃ��X���[�Y�ɑJ�ڂ����邽��
	float m_lerpTimer;

	float m_lerpBegin;
};

#endif