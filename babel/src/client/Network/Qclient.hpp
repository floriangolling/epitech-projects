#ifndef BABELCLIENT
#define BABELCLIENT

#include "IClient.hpp"
#include "../Audio/audio.hpp"
#include <qtcpsocket.h>
#include <iostream>
#include <QUdpSocket>
#include <map>

class Client : public QObject, public IClient{
    Q_OBJECT

    public:
        Client(std::function<int(int)>);
        Client(const Client&) =delete;
        Client& operator=(const Client&) =delete;
        ~Client();
        void setUsername(const std::string &str) override;
        std::string getUsername() const override;
        void setPassword(const std::string &str) override;
        std::string getPassword() const override;
        void setInputValue(const std::string &str, int inputId) override;
        std::string getInputValue(int inputId) const override;
        int connectSocket(const std::string &port, const std::string &ip) override;
        int isConnected() const override;
        void testRead() override;
        std::vector<uint8_t> getResponse() override;
        void write(std::vector<uint8_t>);
        std::vector<std::pair<int, std::string>> getFriends() const override;
        void addFriend(int id, std::string) override;
        void cleanFriends() override;
        void createCall(int port, int) override;
        void endCall() override;
        void listenCall(int port, std::string ip) override;
        void resetTCPSocket() override;
        void setIsCalling(bool) override;
        bool getIsCalling() override;
        void setClientCalling(int) override;
        int getClientCalling(void) override;
        void setCallerId(int) override;
        int getCallerId() override;
    private:
        Audio::PAudio *_audio;
        QUdpSocket *_socketUDP;
        std::string _username;
        std::string _password;
        std::map<int, std::string> _inputsValues;
        QTcpSocket *_socket;
        std::vector<uint8_t> _response;
        std::function<int(int)> _fctEvent;
        std::vector<std::pair<int, std::string>> _friends;
        bool _clientCalling;
        int _idCalling;
        int _callerId;
    private slots:
        void socketError(QAbstractSocket::SocketError);
        void socketConnected();
        void socketDisconnected();
        void readyReadUDP();
};

#endif