#include "core.hpp"
#include "../GUI/GraphLib/QtGraphic.hpp"
#include <iostream>
#include <thread>

Core::Core() {

};

Core::~Core() {
    
};

void Core::init(int &ac, char *av[]) {

    std::function<int(int)> functionClickEvent = [=](int ev) { return this->manageEvent(ev); };
    std::function<void(const std::string &, int)> functionTextEvent = [=](const std::string &txt, int id) { this->manageTextEvent(txt, id); };

    _libgraphic = new QTGraphic(functionClickEvent, functionTextEvent);
    _libgraphic->initWindow(1280, 720, ac, av);
    _client = new Client(functionClickEvent);
    _libgraphic->createIpPage();
    _libgraphic->setLastCreatedPage();
}

void Core::manageTextEvent(const std::string &str, int id) {
    this->_client->setInputValue(str, id);
}

int Core::managePacket(std::vector<uint8_t> package) {
    PacketDecoder decoder;

    decoder.decodeHeader(&package);
    decoder.decodePacket(&package);

    int code = decoder.getCode();

    if (code == 200) {
        _libgraphic->setMessageRegister("Account created.");
    } else if (code == 403) {
        _libgraphic->setMessageRegister("Account already exists.");
    } else if (code == 201) {
        _libgraphic->setMessageLogin("Succes connection.");
        PacketEncoder encoder;
        encoder.addString(this->_client->getInputValue(LoginUsernameInput));
        this->_client->write(encoder.createPacket(104));
        return (OKEVENT);
    } else if (code == 402) {
        _libgraphic->setMessageLogin("Wrong usr/passwd.");
    } else if (code == 404) {
        _libgraphic->setMessageProfile(std::string("user not found"));
        return (OKEVENT);
    } else if (code == 405) {
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        return (OKEVENT);
    } else if (code == 203 || code == 204) {
        std::cout << "receive 204 or 203" << std::endl;
        this->_client->cleanFriends();
        auto packet = decoder.getDataVector();
        int test;
        std::string str;
        int i = 0;
        for (auto it = packet.begin(); it != packet.end(); it++) {
            if (i == 0) {
                test = std::get<int>(it->second);
                i = 1;
            } else {
                str = std::get<std::string>(it->second);
                i = 0;
                this->_client->addFriend(test, str);
            }
        }
        std::vector<std::pair<int, std::string>>  testVec = this->_client->getFriends();
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        return (OKEVENT);
    } else if (code == 205) {
        auto packet = decoder.getDataVector();
        //std::cout << "receving port = " << std::get<int>(packet[0].second) << std::endl;
        //std::cout << "writing port = " << std::get<int>(packet[1].second) << std::endl;
        this->_client->createCall(std::get<int>(packet[0].second), std::get<int>(packet[1].second));
        this->_client->setIsCalling(true);

        //*
        //  TEST THREADING
        //*

        std::thread t(&Client::listenCall, this->_client ,std::get<int>(packet[1].second), std::get<std::string>(packet[2].second));
        t.detach();
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput), this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        //this->_client->listenCall(std::get<int>(packet[1].second), std::get<std::string>(packet[2].second));
    } else if (code == 406) {
        this->_libgraphic->setMessageProfile(std::string("user disconnected or already in call"));
    } else if (code == 206) {
        this->_client->setIsCalling(false);
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
    } else if (code == 302) {
        auto packet = decoder.getDataVector();
        this->_client->setCallerId(std::get<int>(packet[1].second));
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), std::get<std::string>(packet[0].second), false);
        _libgraphic->setLastCreatedPage();     
    } else if (code == 207) {
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", true);
        _libgraphic->setLastCreatedPage();
    } else if (code == 303) {
        this->_client->setIsCalling(false);
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();    
    }
    return (OKEVENT);
}

void Core::manageIDCall(int id) {
    this->_client->setClientCalling(id);
    PacketEncoder encoder;
    encoder.addInt(id);
    this->_client->write(encoder.createPacket(107));
    return;
}

int Core::manageEvent(int ev) {
    PacketEncoder encoder;

    if (ev >= 600 && ev < 999) {
        manageIDCall(ev - 600);
        return (OKEVENT);
    }

    if (ev == DECLINECALL) {
        this->_client->setIsCalling(false);
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        encoder.addInt(this->_client->getCallerId());
        this->_client->write(encoder.createPacket(108));
    }

    if (ev == ACCEPTCALL) {
        encoder.addInt(this->_client->getCallerId());
        this->_client->write(encoder.createPacket(105));
    }

    if (ev == STOPTRYINGTOCALL) {
        this->_client->setIsCalling(false);
        _libgraphic->createProfilePage(this->_client->getFriends(),this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        encoder.addInt(this->_client->getClientCalling());
        this->_client->write(encoder.createPacket(108));
        return (OKEVENT);
    }

    if (ev == STOPCALLPLEASE) {
        this->_client->write(encoder.createPacket(106));
        return (OKEVENT);
    }

    if (ev == addFriendEvent) {
        if (this->_client->getInputValue(friendChanged) != "") {
            encoder.addString(this->_client->getInputValue(friendChanged));
            encoder.addString(this->_client->getInputValue(LoginUsernameInput));
            this->_client->write(encoder.createPacket(102));
        }
        this->_client->setInputValue("", friendChanged);
        _libgraphic->createProfilePage(this->_client->getFriends(), this->_client->getInputValue(LoginUsernameInput),  this->_client->getIsCalling(), "", false);
        _libgraphic->setLastCreatedPage();
        return (OKEVENT);
    } else if (ev == PACKETRECEIVED) {
        return (managePacket(this->_client->getResponse()));
    } else if (ev == goToLogin) {
        _libgraphic->createLoginPage(this->_client->getInputValue(LoginUsernameInput), this->_client->getInputValue(LoginPasswordInput));
        _libgraphic->setLastCreatedPage();
    } else if (ev == goToRegister) {
        _libgraphic->createRegisterPage(this->_client->getInputValue(RegisterUsernameInput), this->_client->getInputValue(RegisterPasswordInput));
        _libgraphic->setLastCreatedPage();
    } else if (ev == LoginEvent) {
        encoder.addString(this->_client->getInputValue(LoginUsernameInput));
        encoder.addString(this->_client->getInputValue(LoginPasswordInput));
        this->_client->write(encoder.createPacket(100));
    } else if (ev == RegisterEvent) {
        encoder.addString(this->_client->getInputValue(RegisterUsernameInput));
        encoder.addString(this->_client->getInputValue(RegisterPasswordInput));
        this->_client->write(encoder.createPacket(101));
    } else if (ev == connectToServerEvent) {
        this->_client->connectSocket(this->_client->getInputValue(LoginPortInput), this->_client->getInputValue(LoginIPInput));
        while (this->_client->isConnected() == SOCKETCONNECTINGSTATE || this->_client->isConnected() == SOCKETHOSLOOKUPSTATE);
        if (this->_client->isConnected() == SOCKETUNCONNECTED) {
            this->_client->resetTCPSocket();
            return (IPNOTOKEVENT);
        } else if (this->_client->isConnected() == SOCKETCONNECTEDSTATE) { 
            _libgraphic->createLoginPage(this->_client->getInputValue(LoginUsernameInput), this->_client->getInputValue(LoginPasswordInput));
            _libgraphic->setLastCreatedPage();
            return (OKEVENT);
        }
    }
    return (OKEVENT);
}

int Core::display() {
    return (_libgraphic->display());
}