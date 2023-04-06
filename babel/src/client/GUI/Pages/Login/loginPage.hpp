
//
// register.hpp
//

#ifndef LOGINPAGEBABEL
#define LOGINPAGEBABEL

#include "../../../utils/utils.hpp"
#include "../../Window/window.hpp"
#include "loginPage.hpp"
#include <QSignalMapper>
#include <QFont>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class Login : public QWidget {
    Q_OBJECT

    public:
        Login(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, std::string, std::string, QWidget *parent = 0);
        Login(const Login&) =delete;
        Login& operator=(const Login&) =delete;
    void handleTextEvent(const std::string &txt, int id);
        void setMessage(const std::string &);
    private:
        myWindow *_window;
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
        QLabel *_inputUsername;
        QLabel *_errorMessage;
        QLabel *_inputPassword;
    public slots:
        void userInputChange(const QString&);
        void passwordInputChange(const QString &);
        int handleWindowEvents(int);

};

#endif