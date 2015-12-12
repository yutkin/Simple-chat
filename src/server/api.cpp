#include "api.hpp"

std::string api::authorized(std::string status)
{
    std::ostringstream stringStream;
    stringStream << "{\"authorization_status\": \"" << status << "\"}";
    return stringStream.str();
}


std::string api::user_disconnected(std::string user)
{
    std::ostringstream stringStream;
    stringStream << "{\"user_disconnected\": \"" << user << "\"}";
    return stringStream.str();
}

std::string api::user_connected(std::string user){
    std::ostringstream stringStream;
    stringStream << "{\"user_connected\": \"" << user << "\"}";
    return stringStream.str();
}

std::string api::api_error(std::string error)
{
    std::ostringstream stringStream;
    stringStream << "{\"api_error\": \"" << error << "\"}";
    return stringStream.str();
}

std::string api::msg_from_user(std::string user, std::string msg)
{
    std::ostringstream stringStream;
    stringStream << "{\"msg_from_user\": \"" << user <<
            "\", \"msg\": \"" << msg << "\"}";
    return stringStream.str();
}

std::string api::msg_delivery_error(std::string receiver, std::string msg)
{
    std::ostringstream stringStream;
    stringStream <<
            "{\"msg_delivery_error\": {" <<
            "\"receiver\": \"" << receiver << "\", " <<
            "\"msg\": \"" << msg << "\"}}";
    return stringStream.str();
}
