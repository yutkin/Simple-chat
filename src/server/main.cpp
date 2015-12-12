#include <csignal>
#include "threaded_server.hpp"

ThreadedServer server(8080);

void ctrl_c_handler(int)
{
    std::cout << "\nKeyboard interrupt received, exiting..." << std::endl;
    server.stop_server();
    exit(EXIT_SUCCESS);
}

int main()
{
    std::signal(SIGINT, ctrl_c_handler);

    std::cout << "Serving HTTP on " << server.get_address() << "\n";
    std::cout << "Press Ctrl+C for interrupt server ..." << std::endl;

    server.serve_forever();

    return EXIT_SUCCESS;
}