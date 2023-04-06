#ifndef BABELICLIENT
#define BABELICLIENT

#include <iostream>
#include "../utils/utils.hpp"
#include <vector>
#include <utility>

class IClient {

    public:
        virtual ~IClient() = default;
        virtual void setUsername(const std::string &str) = 0;
        virtual std::string getUsername() const = 0;
        virtual void setPassword(const std::string &str) = 0;
        virtual std::string getPassword() const = 0;
        virtual void setInputValue(const std::string &str, int inputId) = 0;
        virtual std::string getInputValue(int inputId) const = 0;
        virtual int connectSocket(const std::string &port, const std::string &ip) = 0;
        virtual int isConnected() const = 0;
        virtual void testRead() = 0;
        virtual void write(std::vector<uint8_t>) = 0;
        virtual std::vector<uint8_t> getResponse() = 0;
        virtual std::vector<std::pair<int, std::string>> getFriends() const = 0;
        virtual void cleanFriends() = 0;
        virtual void addFriend(int id, std::string) = 0;
        virtual void createCall(int port, int) = 0;
        virtual void endCall() = 0;
        virtual void listenCall(int port, std::string ip) = 0;
        virtual void resetTCPSocket() = 0;
        virtual void setIsCalling(bool) = 0;
        virtual bool getIsCalling() = 0;
        virtual void setClientCalling(int) = 0;
        virtual int getClientCalling(void) = 0;
        virtual void setCallerId(int) = 0;
        virtual int getCallerId() = 0;
};

#endif