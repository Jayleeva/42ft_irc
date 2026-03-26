#include "../include/Message.hpp"

Message::Message() : _msg("")
{}

Message::Message(const std::string& msg) : _msg(msg)
{}

Message::~Message()
{}

std::string Message::getMsg() const
{
	return _msg;
}

void Message::setMsg(const std::string& msg)
{
	_msg = msg;
}
