#ifndef SERVER_CPP_USER_HPP
#define SERVER_CPP_USER_HPP

#ifdef __APPLE__
    #define MSG_NOSIGNAL 0x4000
#endif

#include <array>
#include <iostream>
#include <string>
#include <memory>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/pointer.h"

typedef int sockfd_t;

/*!
	@brief Represents users that connecting to the server.
*/

class User
{

public:
    static constexpr size_t buffer_size = 4096; ///< Length of bytes that #user_socket accepts at a time.

    typedef std::array<char, buffer_size> buffer_t;
    typedef std::shared_ptr<User> user_ptr;

    explicit User(sockfd_t, sockaddr_in);
    ~User();

    int get_port() const;
    std::string get_ip() const;
    std::string get_address() const;
    std::string get_nickname() const;
    void set_nickname(std::string);

    ssize_t read_message();
    ssize_t send_message(const std::string) const;

    std::string last_message() const;

    void set_roommate(user_ptr);
    void detach_roommate();
    ssize_t send_to_roommate(std::string);
    bool has_roomate() const;

    bool operator< (const User&) const;
    void close_connection();

private:
    buffer_t inner_buffer; ///< This buffer stores bytes that were recieved from last call User::read_message.

    sockfd_t user_socket;
    sockaddr_in user_socket_addr;
    std::string nickname;
    user_ptr rommate = nullptr; ///< Points to #User who will recieve private messages.
};


#endif //SERVER_CPP_USER_HPP
