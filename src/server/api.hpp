#ifndef SERVER_API_HPP
#define SERVER_API_HPP

#include <string>
#include <sstream>

#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/writer.h"


namespace api {
    using std::string;

    const string get_online_users = "get_online_users";

    const string send_to_user = "send_to_user";

    string authorized(string status);

    string user_disconnected(string user);

    string user_connected(string user);

    string msg_from_user(string user, string msg);

    string api_error(string error);

    string msg_delivery_error(string receiver, string msg);
}

#endif //SERVER_API_HPP
