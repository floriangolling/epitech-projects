#include "profile.hpp"
#include <iostream>
#include <QTimer>

Profile::Profile(myWindow *window, std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, std::vector<std::pair<int, std::string>> vec, std::string username, bool isCalling, std::string caller, bool waiting, QWidget *parent) : QWidget(parent) {
    QWidget *box = new QWidget(this);
    _isWaiting = waiting;
    _caller = caller;
    _mapper = new QSignalMapper();
    box->setGeometry(40, 40, 1180, 620);
    box->setStyleSheet("background-color:#009cd6;border-radius:25px");

    _fctClickEvent = fctClickEvent;
    _fctTextEvent = fctTextEvent;

    _frame = new QScrollArea(this);
    _frame->horizontalScrollBar()->setEnabled(false);
    _frame->horizontalScrollBar()->setVisible(false);
    if (vec.size() > 13) {
        _frame->setGeometry(40, 40, 220, 620);
    } else {
        _frame->setGeometry(40, 40, 200, 620);
    }
    _content = new QWidget();
    _mlayout = new QVBoxLayout();
    _content->setLayout(_mlayout);
    _isCalling = isCalling;
    
    for (auto it = vec.begin(); it != vec.end(); it++) {
        addFriend(it->second, it->first);
    }
    _frame->setWidget(_content);
    QLabel *name = new QLabel(this);
    name->setGeometry(640, 40, 200, 35);
    name->setStyleSheet("background-color:none");
    std::string welcome = "Welcome " + username + " !";
    QFont sansFont("Helvetica [Cronyx]", 15);
    sansFont.setWeight(300);
    _errorMessage = new QLabel(this);
    _errorMessage->setFont(sansFont);
    _errorMessage->setGeometry(470, 80, 430, 35);
    _errorMessage->setStyleSheet("background-color:none;color:red");
    _errorMessage->setVisible(false);
    if (isCalling == true) {
        std::cout << isCalling << std::endl;
        QPushButton *btn = new QPushButton("stop", this);
        btn->setGeometry(610, 350, 200, 35);
        btn->setStyleSheet("background-color:red;border-radius:5px");
        connect(btn, SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(btn, STOPCALLPLEASE);
    }
    if (caller != "") {
        std::string isCal = " " + caller + "is Calling";
        QLabel *lbl = new QLabel(this);
        lbl->setGeometry(610, 370, 200, 35);
        lbl->setStyleSheet("background-color:none");
        lbl->setText(isCal.c_str());
        QPushButton *btn = new QPushButton("decline", this);
        btn->setGeometry(610, 400, 200, 35);
        btn->setStyleSheet("background-color:red;border-radius:5px");
        QPushButton *btn2 = new QPushButton("accept", this);
        btn2->setGeometry(610, 450, 200, 35);
        btn2->setStyleSheet("background-color:green;border-radius:5px");
        connect(btn, SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(btn, DECLINECALL);
        connect(btn2, SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(btn2, ACCEPTCALL); 
    }
    if (_isWaiting) {
        QPushButton *btn = new QPushButton("Cancel", this);
        btn->setGeometry(610, 350, 200, 35);
        btn->setStyleSheet("background-color:red;border-radius:5px");
        connect(btn, SIGNAL(clicked()), _mapper, SLOT(map()));
        _mapper->setMapping(btn, 1000);
    }
    name->setText(welcome.c_str());
    QLineEdit *addFriend = new QLineEdit("", this);
    addFriend->setGeometry(610, 240, 200, 35);
    addFriend->setStyleSheet("background-color:white");
    QPushButton *button = new QPushButton("Ajouter l'ami", this);
    button->setGeometry(610, 285, 200, 35);
    button->setStyleSheet("background-color:white");
    if (isCalling || caller != "" || _isWaiting)
        button->setEnabled(false);
    connect(button, SIGNAL(clicked()), _mapper, SLOT(map()));
    _mapper->setMapping(button, addFriendEvent);
    connect(_mapper, SIGNAL(mapped(int)), this, SLOT(handleWindowEvents(int)));
    connect(addFriend, SIGNAL(textChanged(const QString &)), this, SLOT(friendInputChange(const QString &)));
}

void Profile::addFriend(const std::string &str, int id) {
    QHBoxLayout *layout = new QHBoxLayout();
    _mlayout->addLayout(layout);
    QWidget *widget = new QWidget();
    widget->setFixedSize(180, 40);
    widget->setStyleSheet("background-color:white;border-radius:5px");
    QLabel *label = new QLabel(widget);
    QPushButton *button = new QPushButton("appel", widget);
    button->setStyleSheet("background-color:green;border-radius:5px");
    if (_isCalling || _caller != "" || _isWaiting) {
        button->setEnabled(false);
    }
    button->setGeometry(130, 20, 50, 20);
    label->setText(str.c_str());
    connect(button, SIGNAL(clicked()), _mapper, SLOT(map()));
    _mapper->setMapping(button, id + 600);
    layout->addWidget(widget);

}

void Profile::setMessage(std::string &str) {
    _errorMessage->setStyleSheet("background-color:red;color:black");
    _errorMessage->setAlignment(Qt::AlignHCenter);
    if (str == "user not found") {
        _errorMessage->setGeometry(610, 195, 200, 20);
    } else
        _errorMessage->setGeometry(470, 80, 430, 20);
    _errorMessage->setText(str.c_str());
    if (_errorMessage->isVisible() == false) {
        _errorMessage->setVisible(true);
        _errorMessage->repaint();
        QTimer::singleShot(3000, _errorMessage, SLOT(hide()));
    }
}

int Profile::handleWindowEvents(int ev) {
    int response = this->_fctClickEvent(ev);
    return (response);
}

void Profile::handleTextEvent(const std::string &str, int id) {
    this->_fctTextEvent(str, id);
}

void Profile::friendInputChange(const QString &str) {
    this->handleTextEvent(str.toStdString(), friendChanged);
}