//#include"Camera.h"
//#include"../IWorld.h"
//#include"Math/Matrix.h"
//#include<math.h>
//
//#include"Screen\Screen.h"
//
//const float VIEW_ANGLE = 45.0f;
//const float LERP_TIME = 10.0f;
//
//Camera::Camera(IWorld& world):
//Actor(world, "Camera", Vector3(0, 0, 0)),
//m_up(Vector3(0.0f,1.0f,0.0f)),
//m_distance(200.0f),
//m_angleY(0.0f),
//m_angleX(0.0f),
//m_clearTimer(0.0f),
//m_lerpTimer(LERP_TIME)
//{
//	/*m_shapes3DMap[Shape3DEnum::SPHERE_3D].push_back(std::make_shared < Sphere3D>(m_position, 10.0f));
//	m_line = std::make_shared<Line3D>(m_position, m_position);
//	m_shapes3DMap[Shape3DEnum::Line_3D].push_back(m_line);*/
//	m_position = Vector3(0.0f, 0.0f, 0.0f);
//	m_player = m_world->FindActor("Player");
//
//
//	//Near�͂ł������傫�����Ȃ��ƃ��f���ɃW���M����������
//	SetCameraNearFar(10.0f, 100000.0f);
//	SetupCamera_Perspective(VIEW_ANGLE);//60.0f��2��
//	//���ˉe�o�[�W����
//	//SetupCamera_Ortho(Screen::SCREEN_HEIGHT);
//}
//
//void Camera::OnUpdate(float deltaTime)
//{
//	
//}
//void Camera::OnDraw()const
//{
//	//SetUseZBuffer3D(true);//��{�}�`�pZ�o�b�t�@��L���� ��ŃR�����g�A�E�g	
//}
//
////�o�l�W�����g�����ʒu�ړ�
//void Camera::Move(
//	const Vector3& restPosition,	//�o�l�̐Î~�ʒu
//	float stiffness,				//�o�l�萔�i�o�l�̋����j
//	float friction,					//���C��
//	float mass)						//����
//{
//	//�o�l�̐L�ы���v�Z
//	Vector3 stretch = (m_position - restPosition);
//	//�o�l�̗͂��v�Z
//	Vector3 force = stretch * -stiffness;
//	//�����x��ǉ�
//	Vector3 acceleration = force / mass;
//	//�ړ��v�Z���v�Z
//	m_velocity = (m_velocity + acceleration) * friction;
//	//���W�̍X�V
//	m_position += m_velocity;
//}
//
//bool Camera::IsView(const Vector3& position, const float& angle)
//{
//	Vector3 toPlayer = m_target - m_position;
//	Vector3 toObject = position - m_position;
//
//	float deg = Mathf::ToDegrees(Vector3::Angle(toPlayer, toObject)) + angle;
//
//	//����p�����������ꍇtrue
//	return (VIEW_ANGLE >= deg);
//}
//
//void Camera::OnCollide(Actor & other, const HitInfo & info)
//{
//	
//}
