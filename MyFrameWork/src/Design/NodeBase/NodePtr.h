#pragma once

#include <memory>
#include "Util/RefPtr.h"

template<class T>
using BonePtr = std::shared_ptr<T>;

class NodeBase;
using NodePtr = BonePtr<NodeBase>;
using NodeRPtr = RefPtr<NodeBase>;
//using NodeWPtr = std::weak_ptr<NodeBase>;