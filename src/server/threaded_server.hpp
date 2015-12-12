#ifndef THREADED_SERVER_HPP
#define THREADED_SERVER_HPP

#include <sstream>
#include <mutex>
#include <set>
#include <thread>

#include "base_server.hpp"
#include "user.hpp"
#include "api.hpp"

/*!
	@brief Main server which handles client's requests in different threads.
*/

class ThreadedServer : public BaseServer
{
public:
    ThreadedServer() = delete;
    ~ThreadedServer() override;
    explicit ThreadedServer(int port);

    void serve_forever() override;
    void stop_server() override;
private:
    std::set<User::user_ptr> users; ///< All online users stores in std::set. Users are compared by nicknames.

    std::mutex mutex;

    void handle_request(User::user_ptr);
    void send_to_all_users(std::string);
    bool authorize(User::user_ptr) const;
    User::user_ptr search_by_nickname(std::string) const;
    std::string online_users() const;
};

#endif //THREADED_SERVER_HPP