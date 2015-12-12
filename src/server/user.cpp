#include "user.hpp"

User::User(sockfd_t sock, sockaddr_in sock_addr) :
    user_socket(sock), user_socket_addr(sock_addr)
{
    // TODO
}

User::~User()
{
    // TODO
}

void User::close_connection()
{
    /*!
     * @brief Closes #user_socket.
     */

    if (get_nickname() != "")
    {
        std::cout << get_nickname() << " ";
    }
    std::cout << get_address() << " disconnected" << std::endl;
    close(user_socket);
}

std::string User::get_ip() const
{
    /*!
     * @brief Returns user's ip.
     */

    char buffer[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(user_socket_addr.sin_addr), buffer, INET_ADDRSTRLEN);
    return std::string(buffer);
}

int User::get_port() const
{
    /*!
     * @brief Returns user's port.
     */

    return user_socket_addr.sin_port;
}

std::string User::get_address() const
{
    /*!
     * @brief Returns user's address if the follow form: ip:port .
     */

    return get_ip() + ":" + std::to_string(get_port());
}

ssize_t User::send_message(const std::string msg_string) const
{
    /*!
     * @brief Sends string to user.
     * @param[in] msg_string - Source string.
     * @param[out] number - On success, returns the number of characters sent.
     * On error, -1
     */

    return send(user_socket, msg_string.c_str(), msg_string.size()+1, MSG_NOSIGNAL);
}

ssize_t User::read_message()
{
    /*!
     * @brief Read String from user.
     * @param[out] number - On success, returns the number of characters recieved.
     * On error, -1
     */

    ssize_t chars_recvd = recv(user_socket, inner_buffer.data(),
                               buffer_size - 1, MSG_NOSIGNAL);
    if (chars_recvd > -1)
    {
        inner_buffer[chars_recvd] = '\0';
    }
    return chars_recvd;
}

std::string User::last_message() const
{
    /*!
     * @brief Returns string that was made from #inner_buffer.
     */

    return std::string(inner_buffer.data());
}

bool User::operator<(const User &rhs) const
{
    /*!
     * @brief Compares two users. Using for storing in std::set.
     */

    return this->get_nickname() < rhs.get_nickname();
}

void User::set_nickname(std::string nickname)
{
    /*!
     * @brief Sets nickname to user.
     */

    this->nickname = nickname;
}

std::string User::get_nickname() const
{
    /*!
     * @brief Returns user nickname.
     */

    return nickname;
}

void User::set_roommate(user_ptr target)
{
    /*!
     * @brief Sets roommate for user.
     */

    rommate = target;
}

void User::detach_roommate()
{
    /*!
     * @brief Detaches current user's roommate.
     */

    rommate = nullptr;
}

bool User::has_roomate() const
{
    /*!
     * @brief Checks does the user have a roommate.
     */

    return rommate != nullptr;
}

ssize_t User::send_to_roommate(std::string msg)
{
    /*!
     * @brief Sends message to user's roommate.
     * @param[out] number - On success, returns the number of characters sent.
     * On error, -1
     */

    return rommate->send_message(msg);
}
