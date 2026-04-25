#ifndef MESSAGE_HPP
# define MESSAGE_HPP

#include <iostream>
#include <string>
#include <vector>

// This class is used to represent an IRC message received from the client.
class Message
{
    private:
        std::string _msg; // raw message
    
    public:
        Message();
        Message(const std::string& msg);
        ~Message();

        //read and modify _msg
        const std::string getMsg() const;
        void setMsg(const std::string& msg);

};

#endif

/*
** The server receives this as plain text, the role of Message will be to store
    this text and later to parse it properly.
*/