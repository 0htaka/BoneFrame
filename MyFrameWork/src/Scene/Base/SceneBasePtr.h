#ifndef	  _ISCENE_PTR_H_
#define	  _ISCENE_PTR_H_

#include<memory>

//�V�[���|�C���^
class SceneBase;
using ScenePtr = std::shared_ptr<SceneBase>;

#endif