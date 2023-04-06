#include "QtGraphic.hpp"
#include <QWidget>
#include <iostream>

QTGraphic::QTGraphic(std::function<int(int)> fctClickEvent, std::function<void(const std::string &, int)> fctTextEvent) {
    _fctClickEvent = fctClickEvent;
    _fctTextEvent = fctTextEvent;
    _actualPage = nullptr;    
}

QTGraphic::~QTGraphic() {

}

void QTGraphic::initWindow(int width, int height, int &ac, char *av[]) {
    _application = new QApplication(ac ,av);
    _window = new myWindow(_fctClickEvent, _fctTextEvent);
    _window->resize(width, height);
    _window->setWindowTitle(QApplication::translate("toplevel", "Babel 2021"));
    _layout = new QVBoxLayout();
    _pages = new QStackedWidget();
}

void QTGraphic::createIpPage() {
    if (_actualPage)
        _actualPage->deleteLater();
    _actualPage = new portIpPage(this->_window, _fctClickEvent, _fctTextEvent);
}

void QTGraphic::createLoginPage(std::string user, std::string password) {
    if (_actualPage)
        _actualPage->deleteLater();
    _actualPage = new Login(this->_window, _fctClickEvent, _fctTextEvent, user, password);
}

void QTGraphic::setLastCreatedPage() {
    _pages->addWidget(_actualPage);
    _layout->addWidget(_pages);
    this->_window->setLayout(_layout);
}

int QTGraphic::display() {
    _window->show();
    return (_application->exec());
}

void QTGraphic::setMessageProfile(std::string str) {
    Profile *page = (Profile *)_actualPage;
    page->setMessage(str);
}

void QTGraphic::createRegisterPage(std::string user, std::string password) {
    if (_actualPage)
        _actualPage->deleteLater();
    _actualPage = new Register(this->_window, _fctClickEvent, _fctTextEvent, user, password);
}

void QTGraphic::createProfilePage(std::vector<std::pair<int, std::string>> vec, const std::string &username, bool isCalling, std::string caller, bool waiting) {
    if (_actualPage)
        _actualPage->deleteLater();
    _actualPage = new Profile(this->_window, _fctClickEvent, _fctTextEvent, vec, username, isCalling, caller, waiting);
}

void QTGraphic::sendEvent(int event) {
    std::cout << event << std::endl;
}

void QTGraphic::setMessageRegister(const std::string &str) {
    Register *page = (Register *)_actualPage;
    page->setMessage(str);
}

void QTGraphic::setMessageLogin(const std::string &str) {
    Login *page = (Login *)_actualPage;
    page->setMessage(str);
}