#pragma once

#include <memory>
class NodeBase;
using NodeSPtr = std::shared_ptr<NodeBase>;
using NodeWPtr = std::weak_ptr<NodeBase>;