#include "../include/Message.hpp"

//Initialize _msg to an empty string.
Message::Message() : _msg("")
{}

//Store the message
Message::Message(const std::string& msg) : _msg(msg)
{}

Message::~Message()
{}

//Allow to read the message
std::string Message::getMsg() const
{
	return _msg;
}

//Allow to change the message
void Message::setMsg(const std::string& msg)
{
	_msg = msg;
}
