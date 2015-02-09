#ifndef NETWORK_MESSAGE_HPP_
#define NETWORK_MESSAGE_HPP_

#include <string>
#include <functional>
#include <memory>
#include <tuple>

struct NetworkMessage
{
	std::string message;

	bool operator==(const NetworkMessage& b) const
	{
		return message == b.message;
	}
};
typedef std::shared_ptr<NetworkMessage> NetworkMessagePtr;

#endif  // NETWORK_MESSAGE_HPP_
