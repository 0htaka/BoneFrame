#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_

#include"../Actor.h"

//クソース　あとで修正
class Camera : public Actor
{
public:
	Camera(IWorld& world);

	void OnUpdate(float deltaTime) override;
	void OnDraw()const override;
	void Move(
		const Vector3& restPosition,	//バネの静止位置
		float stiffness,				//バネ定数（バネの強さ）
		float friction,					//摩擦力
		float mass						//質量
		);
	///<summary>カメラの視野内にいるかどうか</summary>
	///<param name ='position'>判定するオブジェクトの位置</param>
	///<param name ='angle'>視野内からどれくらいまでを許容するか</param>
	bool IsView(const Vector3& position, const float& angle = 0.0f);
private:
	virtual void OnCollide(Actor& other, const HitInfo& info) override;
private:
	//注視点
	Vector3 m_target;
	//カメラの上方向
	Vector3 m_up;
	//クリア時のrotate
	Matrix m_clearRotate;

	//クリアしてからのタイマ
	float m_clearTimer;

	/**************************************************************************/
	//ここから回転処理用変数
	float m_angleY;//Y軸の回転角度

	float m_angleX;//X軸の回転角度

	float m_distance;//プレイヤーからの距離

	ActorSPtr m_player;

	//std::shared_ptr<Line3D> m_line;

	//線の当たり判定の押し出しとの間をスムーズに遷移させるため
	float m_lerpTimer;

	float m_lerpBegin;
};

#endif