#include "window.hpp"
#include <iostream>
#include "../../utils/utils.hpp"
#include <QLabel>
#include <QVBoxLayout>

myWindow::myWindow(std::function<int(int)> fctClickEvent,std::function<void(const std::string &, int)> fctTextEvent, QWidget *parent) : QWidget(parent) {
    _fctClickEvent = fctClickEvent;
    _fctTextEvent = fctTextEvent;
    this->setStyleSheet("background-color:#00aff0");
}