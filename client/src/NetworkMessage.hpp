#pragma once

#include <string>
#include <functional>
#include <memory>
#include <tuple>

struct NetworkMessage
{
	std::string message;
	std::function<void(std::shared_ptr<const std::string>)> callback;

	bool operator==(const NetworkMessage& b) const
	{
		return message == b.message;
	}
};
typedef std::shared_ptr<NetworkMessage> NetworkMessagePtr;
