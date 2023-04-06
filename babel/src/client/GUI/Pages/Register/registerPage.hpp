
//
// register.hpp
//

#ifndef REGISTERPAGEBABEL
#define REGISTERPAGEBABEL

#include "../../Window/window.hpp"
#include "registerPage.hpp"
#include <QSignalMapper>
#include <QFont>
#include "../../../utils/utils.hpp"
#include <QGridLayout>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class Register : public QWidget {
    Q_OBJECT
    
    public:
        Register(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, std::string, std::string, QWidget *parent = 0);
        Register(const Register&) =delete;
        Register& operator=(const Register&) =delete;
    void handleTextEvent(const std::string &txt, int id);
        void setMessage(const std::string &);
    private:
        QLabel *_inputUsername;
        QLabel *_inputPassword;
        myWindow *_window;
        QLabel *_errorMessage;
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
    public slots:
        void userInputChange(const QString &);
        void passwordInputChange(const QString &);
        int handleWindowEvents(int);
};

#endif