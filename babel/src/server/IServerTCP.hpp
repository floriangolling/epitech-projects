//
// Created by jbroesch on 9/22/21.
//

#ifndef BABEL_ISERVERTCP_HPP
#define BABEL_ISERVERTCP_HPP

#include <asio.hpp>
#include "ConnectionTCP.hpp"

namespace babel_server {
    class ConnectionTCP;
    class IServerTCP {
    public :
        IServerTCP() = default;

        virtual void run() = 0;

        virtual void update_list_status() = 0;

        virtual void do_disconnected(ConnectionTCP &connection) = 0;

        virtual void send_to_id(std::vector<int>,  std::vector<int>) = 0;
    };
}

#endif //BABEL_ISERVERTCP_HPP
