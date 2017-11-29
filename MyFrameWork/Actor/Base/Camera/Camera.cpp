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
//	//Nearはできる限り大きくしないとモデルにジャギが発生する
//	SetCameraNearFar(10.0f, 100000.0f);
//	SetupCamera_Perspective(VIEW_ANGLE);//60.0fの2択
//	//正射影バージョン
//	//SetupCamera_Ortho(Screen::SCREEN_HEIGHT);
//}
//
//void Camera::OnUpdate(float deltaTime)
//{
//	
//}
//void Camera::OnDraw()const
//{
//	//SetUseZBuffer3D(true);//基本図形用Zバッファを有効に 後でコメントアウト	
//}
//
////バネ係数を使った位置移動
//void Camera::Move(
//	const Vector3& restPosition,	//バネの静止位置
//	float stiffness,				//バネ定数（バネの強さ）
//	float friction,					//摩擦力
//	float mass)						//質量
//{
//	//バネの伸び具合を計算
//	Vector3 stretch = (m_position - restPosition);
//	//バネの力を計算
//	Vector3 force = stretch * -stiffness;
//	//加速度を追加
//	Vector3 acceleration = force / mass;
//	//移動計算を計算
//	m_velocity = (m_velocity + acceleration) * friction;
//	//座標の更新
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
//	//視野角よりも小さい場合true
//	return (VIEW_ANGLE >= deg);
//}
//
//void Camera::OnCollide(Actor & other, const HitInfo & info)
//{
//	
//}
