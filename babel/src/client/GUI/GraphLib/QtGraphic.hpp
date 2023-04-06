#ifndef QTGRAPHICBABEL
#define QTGRAPHICBABEL

#include "Igraphic.hpp"
#include "../Pages/Login/loginPage.hpp"
#include "../Pages/Register/registerPage.hpp"
#include "../Pages/ipPage/IpPage.hpp"
#include "../Pages/Profile/profile.hpp"
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QComboBox>
#include <map>
#include <QSignalMapper>
#include "../Window/window.hpp"

class QTGraphic : public IGraphic {
    public:
        QTGraphic(std::function<int(int)>, std::function<void(const std::string &, int)>);
        QTGraphic(const QTGraphic&) =delete;
        QTGraphic& operator=(const QTGraphic&) =delete;
        ~QTGraphic();
        void initWindow(int, int, int &, char *[]) override;
        void createLoginPage(std::string, std::string) override;
        void setLastCreatedPage() override;
        int display() override;
        void createRegisterPage(std::string, std::string) override;
        void createProfilePage(std::vector<std::pair<int, std::string>>, const std::string &, bool, std::string, bool);
        void sendEvent(int) override;
        void createIpPage() override;
        void setMessageRegister(const std::string &) override;
        void setMessageLogin(const std::string &) override;
        void setMessageProfile(std::string) override;
    private:
        myWindow *_window;
        QApplication *_application;
        QLayout *_layout;
        QStackedWidget *_pages;
        QWidget *_actualPage;
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
};

#endif