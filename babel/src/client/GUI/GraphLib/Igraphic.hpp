#ifndef IGRAPHICBABEL
#define IGRAPHICBABEL

#include <iostream>
#include <functional>

class IGraphic {
    public:
        ~IGraphic() = default;
        virtual void initWindow(int, int, int &, char *[]) = 0;
        virtual void createLoginPage(std::string, std::string) = 0;
        virtual void setLastCreatedPage() = 0;
        virtual void createRegisterPage(std::string, std::string) = 0;
        virtual int display() = 0;
        virtual void sendEvent(int) = 0;
        virtual void createIpPage() = 0;
        virtual void setMessageRegister(const std::string &) = 0;
        virtual void setMessageLogin(const std::string &) = 0;
        virtual void createProfilePage(std::vector<std::pair<int, std::string>>,const std::string &, bool, std::string, bool) = 0;
        virtual void setMessageProfile(std::string) = 0;
};

#endif