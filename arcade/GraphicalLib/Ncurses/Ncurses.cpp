//
// Created by jbroesch on 30/03/2021.
//

#include "Ncurses.hpp"

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::GRAPHIC;
}

extern "C" Arcade::IGraphic *getLib()
{
    return new Arcade::Ncurses();
}

Arcade::Ncurses::Ncurses()
{
    initscr();
    start_color();
    if (!(can_change_color())) {
        endwin();
        std::cout << "Your terminal does not support color" << std::endl;
        std::exit(84);
    }
        raw();
        noecho();
        cbreak();
        mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
        keypad(stdscr,TRUE);
        curs_set(0);
        nodelay(stdscr,TRUE);
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_WHITE);
        init_pair(3, COLOR_WHITE, COLOR_RED);
        init_pair(4, COLOR_WHITE, COLOR_GREEN);
        init_pair(5, COLOR_WHITE, COLOR_BLUE);
        init_pair(6, COLOR_WHITE, COLOR_YELLOW);
        init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(8, COLOR_WHITE, COLOR_CYAN);
        refresh();
}

Arcade::Ncurses::~Ncurses()
{
    endwin();
}

std::string Arcade::Ncurses::getName()
{
    return std::string("ncurses");
}

void Arcade::Ncurses::drawPixel(Pixel *pixel)
{
    int x = pixel->getXPos();
    int y = pixel->getYPos();
    int size = pixel->getSize();
    for (int i = 0; i < size; i++) {
        attron(COLOR_PAIR(pixel->getColor() + 1));
        mvhline(y, x, ' ', size);
        attroff(COLOR_PAIR(pixel->getColor()));
    }
}

void Arcade::Ncurses::drawText(Text *text) {

    int x = text->getXPos();
    int y = text->getYPos();
    if (!(text->getHighlight())) {
        attron(COLOR_PAIR(text->getColor()));
        mvprintw(y, x, text->getStr().c_str());
        attroff(COLOR_PAIR(text->getColor()));
    } else {
        attron(A_STANDOUT);
        mvprintw(y, x, text->getStr().c_str());
        attroff(A_STANDOUT);
    }
}

void Arcade::Ncurses::myClear() {
    clear();
}

void Arcade::Ncurses::myRefresh() {
    refresh();
}

Arcade::CommandType Arcade::Ncurses::getInput() {
    int ch = getch();
    for (const auto& [key, value] : keyncursesMap) {
        if (ch == key)
            return value;
    }
    return NO_EVENT;
}