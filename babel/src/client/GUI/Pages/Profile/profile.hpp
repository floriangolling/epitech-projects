
//
// register.hpp
//

#ifndef PROFILEBABEL
#define PROFILEBABEL

#include "../../../utils/utils.hpp"
#include "../../Window/window.hpp"
#include <QSignalMapper>
#include <QFont>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>

class Profile : public QWidget {
    Q_OBJECT

    public:
        Profile(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, std::vector<std::pair<int, std::string>>, std::string, bool, std::string caller, bool, QWidget *parent = 0);
        void handleTextEvent(const std::string &txt, int id);
        Profile(const Profile&) =delete;
        Profile& operator=(const Profile&) =delete;
        void setMessage(const std::string &);
        void addFriend(const std::string &, int id);
        void setMessage(std::string &str);
    private:
        myWindow *_window;
        QScrollArea *_frame;
        QWidget *_content;
        QLabel *_errorMessage;
        QVBoxLayout *_mlayout;
        QSignalMapper *_mapper;
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
        bool _isCalling;
        std::string _caller;
        bool _isWaiting;
    public slots:
        int handleWindowEvents(int);
        void friendInputChange(const QString &);

};

#endif