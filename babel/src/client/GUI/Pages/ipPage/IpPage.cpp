#include "IpPage.hpp"
#include <iostream>
#include <QPainter>

portIpPage::portIpPage(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, QWidget *parent) : QWidget(parent) {
    QWidget *widget = new QWidget(this);
    widget->setStyleSheet("background-color:#009cd6;border-radius:25px");
    widget->setGeometry(400, 200, 500, 300);
    _label = new QLabel(this);
    _ipError = new QLabel(this);
    QLineEdit *IPInput = new QLineEdit("", this);
    QLineEdit *portInput = new QLineEdit("", this);
    QPushButton *button2 = new QPushButton("Connexion", this);
    QSignalMapper *mapper = new QSignalMapper();
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);

    QLabel *title = new QLabel(this);
    QFont sansFont("Helvetica [Cronyx]", 40);
    sansFont.setWeight(300);
    title->setFont(sansFont);
    title->setText("SKYPE");
    title->setGeometry(570, 100, 200, 160);
    title->setStyleSheet("background-color:none");
    this->_window = window;
    _fctClickEvent = fctClickEvent;
    _fctTextEvent = fctTextEvent;
    _label->setGeometry(530, 550, 270 , 35);
    _label->setText("Trying to connect to the port (4s...)");
    _label->setVisible(false);
    _label->setStyleSheet("background-color:red;color:black");
    _ipError->setGeometry(545, 550, 230, 35);
    _ipError->setStyleSheet("background-color:red;color:black");
    _ipError->setText("couldnt connect to this ip/port");
    _ipError->setVisible(false);
    IPInput->setPlaceholderText("IP");
    portInput->setPlaceholderText("PORT");
    portInput->setStyleSheet("background-color:white;border-radius:25px");
    IPInput->setStyleSheet("background-color:white;border-radius:25px");
    button2->setStyleSheet("background-color:white;border-radius:25px");
    IPInput->setGeometry(550, 260, 200, 35);
    portInput->setGeometry(550, 335, 200, 35);
    button2->setGeometry(550, 410, 200, 35);
    connect(button2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(button2, connectToServerEvent);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleWindowEvents(int)));
    connect(IPInput, SIGNAL(textChanged(const QString &)), this, SLOT(IPInputChange(const QString &)));
    connect(portInput, SIGNAL(textChanged(const QString &)), this, SLOT(portInputChange(const QString &)));
}

int portIpPage::handleWindowEvents(int ev) {
    if (ev == connectToServerEvent) {
        if (_ipError->isVisible() == true)
            _ipError->setVisible(false);
        if (_label->isVisible() == false) {
            _label->setVisible(true);
            _label->repaint();
        }
    }
    int response = this->_fctClickEvent(ev);
    if (response == IPNOTOKEVENT && _ipError->isVisible() == false) {
        _ipError->setVisible(true);
        _ipError->repaint();
        _label->setVisible(false);
    }
    return (0);
}

void portIpPage::handleTextEvent(const std::string &str, int id) {
    this->_fctTextEvent(str, id);
}

void portIpPage::portInputChange(const QString &str) {
    this->handleTextEvent(str.toStdString(), LoginPortInput);
}

void portIpPage::IPInputChange(const QString &str) {
    this->handleTextEvent(str.toStdString(), LoginIPInput);
}