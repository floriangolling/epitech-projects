//
// Created by jbroesch on 9/23/21.
//

#include <iostream>
#include "ServerTCP.hpp"
#include "ConnectionTCP.hpp"
#include "../common/PacketEncoder.hpp"
#include "../common/PacketDecoder.hpp"

namespace babel_server {
    #ifdef __linux__
    std::string exec(const char* cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
    #endif
    Server::Server(asio::io_service& io_service, int port) : _io_service(io_service),
        _acceptor(io_service, tcp::endpoint(tcp::v4(), port)), _socket(_io_service){
        if ((port < 1024) || (port > 60000)) {
            sig = true;
            throw std::runtime_error("Port have to be in range 1024-60000");
        }
        else {
            _database = new Database();
            std::cout << "Server IP : ";
            #ifdef __linux__
            std::string ipaddr = exec("hostname -I");
            const char *cstr = ipaddr.c_str();
            for (int i = 0; i < ipaddr.length(); i++) {
                if (cstr[i] == ' ' || cstr[i] == '\n')
                    break;
                std::cout << cstr[i];
            }
            printf("\n");
            #endif
            std::cout << "Server listen on port "
                      << _acceptor.local_endpoint().port() << std::endl;
        }
        start_accept();
    }
    Server::~Server() {
        _thread->join();
    }
    void Server::run() {
        _thread = new std::thread{([this]() {asio::io_service::work work(_io_service); _io_service.run();})};
        while (_server_is_up) {
            update_list_status();
            if (sig)
                signal_handler();
        }
    }
    void Server::signal_handler() {
        _io_service.stop();
        _acceptor.close();
        for (const auto& it : _connection_list) {
            do_disconnected(*it);
        }
        std::cout << "Server closed successfully" << std::endl;
        _server_is_up = false;
    }
    void Server::do_disconnected(ConnectionTCP &connection) {
        std::cout << "Client ID : " << connection.getId() << " disconnected." << std::endl;
        //std::string disconnected_mess = "Client " + std::to_string(connection.getId()) + " has left the server";
        PacketEncoder encoder;
        auto it = encoder.createPacket(2);
        write_to_all_users(it);
        std::error_code ec;
        connection.Socket().shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        connection.Socket().close();
    }
    void Server::write_to_all_users(std::vector<uint8_t> data) {
        for (const auto& it : _connection_list) {
            if (it->get_connection_status()) {
                it->do_write(data);
            }
        }
    }
    void Server::update_list_status() {
        for (auto it = _connection_list.begin(); it != _connection_list.end();) {
            if (!((*it)->get_connection_status())) {
                do_disconnected(**it);
                _connection_list.erase(it);
                it = _connection_list.begin();
            } else {
                it++;
            }
        }
    }
    void Server::start_accept() {
        _acceptor.async_accept(_socket,
                               [this](std::error_code ec) {
                    if(!ec) {
                        std::string ip = _socket.remote_endpoint().address().to_string();
                        std::shared_ptr<ConnectionTCP> _newTCPConnection =
                                std::make_shared<ConnectionTCP>(std::move(_socket), *_database, this);
                        _newTCPConnection->setIP(ip);
                        _newTCPConnection->start();
                        _idClient++;
                        _newTCPConnection->setId(_idClient);
                        std::cout << "Connection from: " << _newTCPConnection->getIp() << " ID client : " << _newTCPConnection->getId() << "\n";
                        _connection_list.push_back(_newTCPConnection);
                        PacketEncoder encoder;
                        auto it = encoder.createPacket(1);
                        //std::string notify_entry = std::to_string(_newTCPConnection->getId()) + " has join the server";
                        write_to_all_users(it);
                    } else {
                        std::cerr << "An error occurred: " << ec.message( ) << std::endl;
                    }
                    start_accept();
                }
        );
    }

    void Server::friendHasBeenAddedEvent(int idOne, int idTwo) {
        for (const auto& it : _connection_list) {
            if (it->get_connection_status() && it->getName() == idTwo) {
                PacketEncoder encoder;
                std::vector<std::pair<std::string, int >> vec = _database->list_user_friends(idTwo);
                for (auto it = vec.begin(); it != vec.end(); it++) {
                    encoder.addInt(it->second);
                    encoder.addString(it->first);
                }
                std::cout << "writing 204" << std::endl;
                it->do_write(encoder.createPacket(204));
                return;
            }
        }
    }

    void Server::stopCall(int id) {

        int secondId = -1;

        for (auto it = _areCallingIds.begin(); it != _areCallingIds.end(); it++) {
            if (it->first == id)
                secondId = it->second;
            else if (it->second == id) {
                secondId = it->first;
            }
        }

        if (secondId == -1) {
            std::cout << "error while getting stopcall id" << std::endl;
            return;
        }

        for (const auto& it : _connection_list) {
            if (it->get_connection_status() && it->getName() == id || it->getName() == secondId) {
                PacketEncoder encoder;
                it->do_write(encoder.createPacket(206));
                it->setIsCalling(false);
            }
        }
        return;
    }

    int Server::askForCall(int id, int nameCaller) {
        int foundId = -1;

        for (const auto& it : _connection_list) {
            if (it->get_connection_status() && it->getName() == id && it->getIsCalling() == false) {
                foundId = id;
                break;
            }
        }

        if (foundId == -1)
            return (84);

        for (const auto& it : _connection_list) {
            if (it->get_connection_status() && it->getName() == id) {
                PacketEncoder encoder;
                encoder.addString(_database->id_to_name(nameCaller));
                encoder.addInt(nameCaller);
                it->do_write(encoder.createPacket(302));
                break;
            }
        }
        return (0);
    }

    void Server::tellToStopCall(int id) {
        for (const auto& it : _connection_list) {
            if (it->get_connection_status() && it->getName() == id) {
                PacketEncoder encoder;
                it->do_write(encoder.createPacket(303));
            }
        }
        return;
    }

    void Server::send_to_id(std::vector<int> names, std::vector<int> ports) {
        int NumberOfConnected = 0;
        int NumberNotInCall = 0;
        int alreadySend = -1;
        int alreadySendTwo = -1;
        std::string ip1 = "";
        std::string ip2 = "";

        for (const auto& it : _connection_list) {
            if (it->get_connection_status()) {
                for (auto secondeIt = names.begin(); secondeIt != names.end(); secondeIt++) {
                    if (it->getName() == *secondeIt && alreadySendTwo == -1) {
                        ip1 = it->getIp();
                        NumberOfConnected++;
                        alreadySendTwo = it->getName();
                        if (it->getIsCalling() == false)
                            NumberNotInCall++;
                    } else if (it->getName() == *secondeIt && alreadySendTwo != it->getName()) {
                        ip2 = it->getIp();
                        NumberOfConnected++;
                        if (it->getIsCalling() == false)
                            NumberNotInCall++;
                    }
                }
            }
        }

        if (NumberOfConnected != 2 || NumberNotInCall != 2) {
            for (const auto& it : _connection_list) {
                if (it->get_connection_status() && it->getName() == names[1]) {
                    PacketEncoder encoder;
                    it->do_write(encoder.createPacket(406));
                    return;
                }
            }
            return;
        }
        _areCallingIds.push_back(std::make_pair(names[0], names[1]));
        for (const auto& it : _connection_list) {
            if (it->get_connection_status()) {
                for (auto secondeIt = names.begin(); secondeIt != names.end(); secondeIt++) {
                    if (it->getName() == *secondeIt && alreadySend == -1) {
                        PacketEncoder encoder;
                        encoder.addInt(ports[0]);
                        encoder.addInt(ports[1]);
                        encoder.addString(ip2);
                        it->do_write(encoder.createPacket(205));
                        alreadySend = it->getName();
                        it->setIsCalling(true);
                    } else if (it->getName() == *secondeIt && alreadySend != it->getName()) {
                        PacketEncoder encoder;
                        encoder.addInt(ports[1]);
                        encoder.addInt(ports[0]);
                        encoder.addString(ip1);
                        it->setIsCalling(true);
                        it->do_write(encoder.createPacket(205));
                    }
                }
            }
        }
    }
}