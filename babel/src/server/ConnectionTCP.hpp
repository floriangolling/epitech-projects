//
// Created by jbroesch on 9/23/21.
//

#ifndef BABEL_CONNECTIONTCP_H
#define BABEL_CONNECTIONTCP_H

#ifdef _WIN32
#define _WIN32_WINNT  0x0601
#endif

#include <memory>
#include <asio.hpp>
#include "Database.hpp"
#include <csignal>
#include "../common/PacketEncoder.hpp"
#include "../common/PacketDecoder.hpp"
#include "IConnectionTCP.hpp"

using asio::ip::tcp;

namespace babel_server {
    class Server;
    class ConnectionTCP : public IConnectionTCP {
    public:
        explicit ConnectionTCP(tcp::socket socket, Database &database, Server *server);
        tcp::socket &Socket() override;
        void start() override;
        void do_read() override;
        void do_write(std::vector<uint8_t>) override;
        int getId() override;
        bool get_connection_status() const override;
        void setId(int) override;
        char *getData() override;
        std::string getIp() override;
        void setIP(std::string) override;
        void handlerCommand(std::vector<uint8_t> ) override;
        int getName() override;
        void setName(int) override;
        bool getIsCalling() override;
        void setIsCalling(bool) override;

    private:
        Server *_serv;
        int _id;
        tcp::socket _socket;
        enum {
            max_length = 6579
        };
        size_t _length = 0;
        char _data[max_length]{};
        bool _is_connected = true;
        std::string _ip;
        Database *_database;
        int _name;
        bool _isCalling;
    };
}

#endif //BABEL_CONNECTIONTCP_H
