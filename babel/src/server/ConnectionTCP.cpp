//
// Created by jbroesch on 9/23/21.
//

#include <iostream>
#include <utility>
#include "ConnectionTCP.hpp"
#include "ServerTCP.hpp"
#include "../common/utils.hpp"

namespace babel_server {
    ConnectionTCP::ConnectionTCP(tcp::socket socket, Database &database, Server *server) : _socket(std::move(socket))
    {
        this->_serv = server;
        this->_database = &database;
        _name = -1;
        _isCalling = false;
    }
    tcp::socket& ConnectionTCP::Socket()
    {
        return _socket;
    }
    void ConnectionTCP::setId(int id) {
        _id = id;
    }
    int ConnectionTCP::getId() {
        return _id;
    }
    std::string ConnectionTCP::getIp() {
        return _ip;
    }
    void ConnectionTCP::setIP(std::string ip) {
        _ip = std::move(ip);
    }
    char *ConnectionTCP::getData() {
        return _data;
    }
    void ConnectionTCP::start() {
        do_read();
    }
    bool ConnectionTCP::get_connection_status() const {
        return _is_connected;
    }
    void ConnectionTCP::do_write(std::vector<uint8_t> packet) {
        auto self(shared_from_this());
        asio::async_write(
                _socket,
                asio::buffer(packet, packet.size()),
                [this, self](std::error_code ec, std::size_t)
                {
                    if(ec) {
                        std::cerr << "An error occurred: " << ec.message( ) << std::endl;
                    }
                }
        );
    }

    void ConnectionTCP::handlerCommand(std::vector<uint8_t> data) {
        PacketDecoder decoder;
        PacketEncoder encoder;

        decoder.decodeHeader(&data);    // Fill class with header infos;
        decoder.decodePacket(&data);    // Fill class with data body;
        /*std::cout << "found a packet" << std::endl;
        std::cout << "code : " << decoder.getCode() << std::endl;
        std::cout << "size : " << decoder.getPacketSize() << std::endl;
        std::cout << "magicNumber : " << decoder.getMagicNumber() << std::endl;
        std::cout << "now showing all arguments in the packet" << std::endl;
        */
        auto packet = decoder.getDataVector();
        /*
        for (auto it = packet.begin(); it != packet.end(); it++) {
            if (it->first == STRING) {
                std::cout << std::get<std::string>(it->second) << std::endl;
            } else if (it->first == INT) {
                std::cout << std::get<int>(it->second) << std::endl;
            } else {
                std::cout << std::get<bool>(it->second) << std::endl;
            }
        } else if (decoder.getCode() == 103) {
            std::string username = std::get<std::string>(packet[0].second);
            std::string password = std::get<std::string>(packet[1].second);
            if (_database->check_if_good_password_username(username, password)) {
                do_write(encoder.createPacket(201));
                return;
            } else {
                do_write(encoder.createPacket(402));
                return;
            }
        }
        */
        if (decoder.getCode() == 101) {
            std::string username = std::get<std::string>(packet[0].second);
            std::string password = std::get<std::string>(packet[1].second);

            if (!_database->check_if_user_exist(username)) {
                _database->add_user(username, password);
                do_write(encoder.createPacket(200));
                return;
            } else {
                do_write(encoder.createPacket(403));
                return;
            }
        } else if (decoder.getCode() == 100) {
            std::string username = std::get<std::string>(packet[0].second);
            std::string password = std::get<std::string>(packet[1].second);
            if (_database->check_if_good_password_username(username, password)) {
                do_write(encoder.createPacket(201));
                this->setName(_database->name_to_id(username));
                return;
            } else {
                do_write(encoder.createPacket(402));
                return;
            }
        } else if (decoder.getCode() == 102) {
            std::string toAdd = std::get<std::string>(packet[0].second);
            std::string adder = std::get<std::string>(packet[1].second);
            int userOne = _database->name_to_id(adder);
            int userTwo = _database->name_to_id(toAdd);
            if (userOne == -1 || userTwo == -1) {
                do_write(encoder.createPacket(404));
                return;
            }
            if (_database->are_they_friends(userOne, userTwo)) {
                do_write(encoder.createPacket(405));
                return;
            }
            _database->add_friends(userOne, userTwo);
            std::vector<std::pair<std::string, int >> vec = _database->list_user_friends(userOne);
            for (auto it = vec.begin(); it != vec.end(); it++) {
                encoder.addInt(it->second);
                encoder.addString(it->first);
            }
            _serv->friendHasBeenAddedEvent(userOne, userTwo);
            do_write(encoder.createPacket(203));
            return;
        } else if (decoder.getCode() == 104) {
            std::string toAdd = std::get<std::string>(packet[0].second);
            int user = _database->name_to_id(toAdd);   
            std::vector<std::pair<std::string, int >> vec = _database->list_user_friends(user);
            for (auto it = vec.begin(); it != vec.end(); it++) {
                encoder.addInt(it->second);
                encoder.addString(it->first);
            }
            do_write(encoder.createPacket(204));
            return;
        } else if (decoder.getCode() == 105) {
            int port = (rand() % (4000 - 1000) + 1000);
            int port2 = (rand() % (4000 - 1000) + 1000);
            while (port == port2)
                port2 = (rand() % (4000 - 1000) + 1000);
            std::vector<int> names;
            std::vector<int> ports;
            ports.push_back(port);
            ports.push_back(port2);
            names.push_back(std::get<int>(packet[0].second));
            names.push_back(_name);
            _serv->send_to_id(names , ports);
            return;
        } else if (decoder.getCode() == 106) {
            _serv->stopCall(this->getName());
        } else if (decoder.getCode() == 107) {
            if (_serv->askForCall(std::get<int>(packet[0].second), this->getName()) == 84) {
                do_write(encoder.createPacket(406));
                return;
            } else {
                do_write(encoder.createPacket(207));
                return;
            }
        } else if (decoder.getCode() == 108) {
            _serv->tellToStopCall(std::get<int>(packet[0].second));
            return;
        }
        return;
    }

    void ConnectionTCP::do_read() {
        auto self(shared_from_this());
        _socket.async_read_some(
                asio::buffer(_data, max_length),
                [this, self](std::error_code ec, std::size_t length)
                {
                    if (!ec) {
                        _length = length;
                        std::vector<uint8_t> buffer(length, '\0');
                        std::memcpy(buffer.data(), _data, length);
                        handlerCommand(buffer);
                        do_read();
                    }
                    else if(ec == asio::error::eof || ec == asio::error::operation_aborted) {
                        _is_connected = false;
                        if (_isCalling)
                            _serv->stopCall(this->getName());
                    }
                }
        );
    }
    int ConnectionTCP::getName() {
        return (_name);
    }

    void ConnectionTCP::setName(int name) {
        _name = name;
    }

    bool ConnectionTCP::getIsCalling() {
        return (_isCalling);
    }

    void ConnectionTCP::setIsCalling(bool i) {
        _isCalling = i;
    }
}