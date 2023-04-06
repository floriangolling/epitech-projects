//
// Created by jbroesch on 9/22/21.
//

#ifndef BABEL_SERVERTCP_H
#define BABEL_SERVERTCP_H

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

#include "IServerTCP.hpp"
#include "Database.hpp"
#include <iostream>
#include <list>
#include <functional>
#include <memory>

using asio::ip::tcp;

extern bool sig;

namespace babel_server {

    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    class Server : public IServerTCP {
    public:
        Server(asio::io_service& io_service, int port);
        Server(const Server&) =delete;
        Server& operator=(const Server&) =delete;
        ~Server();
        void run() override;
        void start_accept();
        void signal_handler();
        void update_list_status() override;
        void do_disconnected(ConnectionTCP &connection) override;
        void write_to_all_users(std::vector<uint8_t>);
        void send_to_id(std::vector<int>, std::vector<int>) override;
        void stopCall(int id);
        void friendHasBeenAddedEvent(int idOne, int idTwo);
        int askForCall(int id, int nameCaller);
        void tellToStopCall(int id);
    private:
            Database *_database;
        std::thread *_thread;
        std::list<std::shared_ptr<ConnectionTCP>> _connection_list;
        asio::io_service &_io_service;
        tcp::acceptor _acceptor;
        tcp::socket _socket;
        int _idClient = 0;
        bool _server_is_up = true;
        std::vector<std::pair<int ,int>> _areCallingIds;
    };
}

#endif //BABEL_SERVERTCP_H
