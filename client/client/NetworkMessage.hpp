#pragma once

#include <string>
#include <functional>
#include <memory>

struct NetworkMessage
{
	std::string message;
	std::function<void(std::shared_ptr<const std::string>)> callback;
};
typedef std::shared_ptr<NetworkMessage> NetworkMessagePtr;
