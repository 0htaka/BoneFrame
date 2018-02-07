#pragma once

#include <memory>
#include "Util/RefPtr.h"

//boneframe�̃^�X�N�V�X�e���Ŏg�p����|�C���^
template<class T>
using BonePtr = std::unique_ptr<T>;//std::shared_ptr<T>;

class NodeBase;
using NodePtr = BonePtr<NodeBase>;
using NodeRPtr = RefPtr<NodeBase>;
//using NodeWPtr = std::weak_ptr<NodeBase>;