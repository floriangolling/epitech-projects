//
// Created by jbroesch on 10/16/21.
//

#ifndef BABEL_ICONNECTIONTCP_HPP
#define BABEL_ICONNECTIONTCP_HPP

namespace babel_server {
    using asio::ip::tcp;
    class Server;
    class IConnectionTCP : public std::enable_shared_from_this<IConnectionTCP> {
    public:
        virtual tcp::socket &Socket() = 0;
        virtual void start() = 0;
        virtual void do_read() = 0;
        virtual void do_write(std::vector<uint8_t>) = 0;
        virtual int getId() = 0;
        virtual bool get_connection_status() const = 0;
        virtual void setId(int) = 0;
        virtual char *getData() = 0;
        virtual std::string getIp() = 0;
        virtual void setIP(std::string) = 0;
        virtual void handlerCommand(std::vector<uint8_t> ) = 0;
        virtual int getName() = 0;
        virtual void setName(int) = 0;
        virtual  bool getIsCalling() = 0;
        virtual void setIsCalling(bool) = 0;

    };
}

#endif //BABEL_ICONNECTIONTCP_HPP
