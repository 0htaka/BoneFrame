#ifndef	  _CAMERA_H_
#define	  _CAMERA_H_

#include "../Base/Actor.h"

//クソース　あとで修正
class Camera : public Actor
{
public:
	Camera();

	void OnUpdate(float deltaTime) override;
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

};

#endif