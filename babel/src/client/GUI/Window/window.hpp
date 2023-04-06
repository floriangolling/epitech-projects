#ifndef WINDOWBABEL
#define WINDOWBABEL

#include <QWidget>

class myWindow : public QWidget {
    Q_OBJECT

    public:
        myWindow(std::function<int(int)>, std::function<void(const std::string &, int)>, QWidget *parent = 0);
        myWindow(const myWindow&) =delete;
        myWindow& operator=(const myWindow&) =delete;
    private:
        std::function<int(int)> _fctClickEvent;
        std::function<void(const std::string &, int)> _fctTextEvent;
};

#endif