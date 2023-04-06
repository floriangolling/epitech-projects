
//
// register.hpp
//

#ifndef IPPAGEBABEL
#define IPPAGEBABEL

#include "../../../utils/utils.hpp"
#include "../../Window/window.hpp"
#include <QSignalMapper>
#include <QFont>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class portIpPage : public QWidget {
    Q_OBJECT

    public:
        portIpPage(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, QWidget *parent = 0);
        portIpPage(const portIpPage&) =delete;
        portIpPage& operator=(const portIpPage&) =delete;
    void handleTextEvent(const std::string &txt, int id);
    private:
        myWindow *_window;
        QLabel *_label;
        QLabel *_ipError;
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
    public slots:
        void IPInputChange(const QString &);
        void portInputChange(const QString &);
        int handleWindowEvents(int);
};

#endif