#include "Qclient.hpp"
#include <iostream>
#include "QDialog"
#include "../GUI/Window/window.hpp"
#include <cstring>

static bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

Client::Client(std::function<int(int)> fct) : QObject() {
    _username = "";
    _password = "";
    for (int i = 0; i < 7; i++) {
        this->_inputsValues[i] = "";
    }
    _socket = new QTcpSocket(this);
    _socketUDP = nullptr;
    _fctEvent = fct;
    _audio = new Audio::PAudio();
    _clientCalling = false;
}

Client::~Client() {

}

std::vector<std::pair<int, std::string>> Client::getFriends() const {
    return (_friends);
}

void Client::socketError(QAbstractSocket::SocketError error) {
    if (this->_socket->isOpen())
        this->_socket->disconnectFromHost();
}

void Client::socketConnected() {
    std::cout << "Successfully conneceted to the socket !" << std::endl;
    QDialog::connect(_socket, &QIODevice::readyRead, this, &Client::testRead);
}

void Client::resetTCPSocket() {
    if (_socket)
        _socket->deleteLater();
    _socket = new QTcpSocket(this);
}

void Client::setIsCalling(bool i) {
    _clientCalling = i;
} 

void Client::testRead() {

    QByteArray array;

    while (_socket->bytesAvailable() > 0) {
        array.append(_socket->readAll());
    }
    std::vector<uint8_t> buffer(array.size(), '\0');
    std::memcpy(buffer.data(), array.data(), array.size());
    _response = buffer;
    _fctEvent(PACKETRECEIVED);
}

std::vector<uint8_t> Client::getResponse() {
    return (_response);
}

void Client::addFriend(int id, std::string name) {
    this->_friends.push_back(std::make_pair(id, name));
}

void Client::write(std::vector<uint8_t> msg) {
    QByteArray array;
    array.setRawData((const char *)msg.data(), msg.size());
    _socket->write(array);
}

void Client::socketDisconnected() {
    if (this->_socket->isOpen())
        this->_socket->disconnectFromHost();
    return;
}

int Client::connectSocket(const std::string &port, const std::string &ip) {
    const QString str = QString::fromStdString(ip);
    if (!is_number(port) || port.empty() || ip.empty())
        return 0;
    connect(_socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)), this,SLOT(socketError(QAbstractSocket::SocketError)));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));  
    this->_socket->connectToHost(str, std::stoi(port));
    this->_socket->waitForConnected(4000);
    return (0);
}

void Client::cleanFriends() {
    this->_friends.clear();
}

void Client::setPassword(const std::string &str) {
    _password = str;
}

void Client::setUsername(const std::string &str) {
    _username = str;
}

std::string Client::getPassword() const {
    return (_password);
}

std::string Client::getUsername() const {
    return (_username);
}

std::string Client::getInputValue(int inputId) const {
    return (this->_inputsValues.at(inputId));
}

void Client::setInputValue(const std::string &str, int id) {
    this->_inputsValues[id] = str;
}

int Client::isConnected() const {
    return (int)_socket->state();
}

void Client::createCall(int port, int secondPort) {
    std::cout << port << std::endl;
    std::cout << secondPort << std::endl;
    this->_socketUDP = new QUdpSocket(this);
    _audio->startRecord();
    _audio->startDisplay();
    if (!this->_socketUDP->bind(QHostAddress::AnyIPv4, port))
        std::cout << "error binding socket 1" << std::endl;
    _clientCalling = true;
}

void Client::endCall() {
    if (_socketUDP) {
        this->_socketUDP->deleteLater();
        this->_socketUDP = nullptr;
    }
    _audio->stopRecord();
    _audio->stopDisplay();
}

int Client::getClientCalling() {
    return (_idCalling);
}

void Client::setClientCalling(int id) {
    _idCalling = id;
}

void Client::readyReadUDP() {
    QByteArray array;
    QHostAddress adress;
    quint16 port = -1;
    array.resize(_socketUDP->pendingDatagramSize());
    _socketUDP->readDatagram(array.data(), array.size(), &adress, &port);
    _audio->setOutputq(std::vector<unsigned char>(array.begin(), array.end()));
}

bool Client::getIsCalling() {
    return (_clientCalling);
}

int Client::getCallerId() {
    return (_callerId);
}

void Client::setCallerId(int id) {
    _callerId = id;
}

void Client::listenCall(int port, std::string ip) {

    while (_clientCalling) {
        if (!_audio->getUq().empty()) {
            QByteArray arrayData(reinterpret_cast<const char *>(_audio->getUq().front().data()),
                                 _audio->getUq().front().size());
            _socketUDP->writeDatagram(arrayData, QHostAddress(QString(ip.c_str())), port);
            _audio->set_popback_uq();
        }
        if (_socketUDP->hasPendingDatagrams()) {
            readyReadUDP();
        }
    }
    endCall();
    return;
}