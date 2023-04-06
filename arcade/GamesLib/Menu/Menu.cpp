//
// Created by jbroesch on 30/03/2021.
//

#include "Menu.hpp"

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::MENU;
}

extern "C" Arcade::IGame *getLib()
{
    return new Arcade::Menu();
}

namespace Arcade {
    Menu::Menu() {
        set_dispGame();
        _pixels.push_back(Pixel(0, 0, BLACK, 800));
        _disp_Game.at(0).setHighlight(true);
        _playerName = new Text(37, 18, "__________", WHITE, 22);
        std::ifstream in_l;
        in_l.exceptions ( std::ifstream::badbit );
        try {
            in_l.open("./GamesLib/Menu/banner.txt");
            std::string banner;
            while (std::getline(in_l, banner))
                _ascii_arcade.push_back(banner);
        } catch(std::ifstream::failure &e) {
            std::cerr << "Can't open/read/close file : banner.txt" << std::endl;
            throw std::exception();
        }
        in_l.close();
    }

    Menu::~Menu() {
        delete(_playerName);
    }

    CommandType Menu::getEvent(IGraphic &graph) {
        CommandType ev = graph.getInput();
        bool was_high = false;
        if (ev == DOWN) {
            for(auto it = std::begin(_disp_Game); it != std::end(_disp_Game); ++it) {
                if (was_high && (it != std::end(_disp_Game))) {
                    (*it).setHighlight(true);
                    break;
                }
                if ((*it).getHighlight() && (it + 1 != std::end(_disp_Game))) {
                    (*it).setHighlight(false);
                    was_high = true;
                }
            }
            return ev;
        }
        if (ev == UP) {
            for(auto it = std::begin(_disp_Game); it != std::end(_disp_Game); ++it) {
                if ((*it).getHighlight() && (it != std::begin(_disp_Game))) {
                    (*it).setHighlight(false);
                    --it;
                    (*it).setHighlight(true);
                    break;
                }
            }
            return ev;
        }
        if (ev == SPACE) {
            _disp_Game.clear();
            set_dispGame();
            _disp_Game.at(0).setHighlight(true);
        }
        if (ev == ENTER) {
            _disp_Game.clear();
            set_dispGame();
            _disp_Game.at(0).setHighlight(true);
        }
        return ev;
    }

    void Menu::update(double elapsed_time) {
        elapsed_time += 1;
    }

    void Menu::draw(IGraphic &graph) {
        graph.myClear();
        int x_pos = 0;
        int y_pos = 0;
        for(auto it = std::begin(_ascii_arcade); it != std::end(_ascii_arcade); ++it) {
            for (std::string::size_type i = 0; i < (*it).size(); i++) {
                Pixel *pix = new Pixel(y_pos, x_pos, BLACK, 1);
                if ((*it)[i] == '#')
                    pix->setColor(RED);
                if ((*it)[i] == '1')
                    pix->setColor(MAGENTA);
                if ((*it)[i] == '2')
                    pix->setColor(BLUE);
                if ((*it)[i] == '3')
                    pix->setColor(YELLOW);
                if ((*it)[i] == 'L')
                    pix->setColor(WHITE);
                if ((*it)[i] == 'P')
                    pix->setColor(BLACK);
                graph.drawPixel(pix);
                y_pos += 1;
                delete(pix);
            }
            x_pos += 1;
            y_pos = 0;
        }
        if (_disp_Game.size() == 2) {
            Text *empty_lib = new Text(33, 30, "No game avalaible...", WHITE, 22);
            graph.drawText(empty_lib);
            delete(empty_lib);
        } else {
            Text *enteruser = new Text(36, 15, "Enter username", WHITE, 22);
            graph.drawText(enteruser);
            delete(enteruser);
            graph.drawText(_playerName);
            for (auto it = std::begin(_disp_Game);
                 it != std::end(_disp_Game); ++it) {
                if ((&(*it).getStr())->compare("howtoplay") == 0) {
                    std::string how = "how to play";
                    (*it).setStr(how);
                }
                graph.drawText(&(*it));
            }
        }
        graph.myRefresh();
    }

    void Menu::setPlayerName(std::string &name)
    {
        delete(_playerName);
        _playerName = new Text(37, 18, name, WHITE, 22);
    }

    void Menu::set_dispGame() {
        std::string fp;
        void *sharedLib;
        LibType (*getLibType)();
        int Yposition = 32;
        std::vector<std::string> tmp;

        for (const auto &entry : std::filesystem::directory_iterator("./lib/")) {
            fp = entry.path();
            sharedLib = dlopen(fp.c_str(), RTLD_LAZY);
            if (!sharedLib) {
                std::cerr << dlerror() << std::endl;
                throw std::exception();
            }
            if (sharedLib) {
                getLibType = reinterpret_cast<Arcade::LibType (*)()>(dlsym(sharedLib, "getLibType"));
                if (getLibType() == GAME)
                    tmp.push_back(getNameLib(fp));
                dlclose(sharedLib);
            }
        }
        std::sort(tmp.begin(), tmp.end());
        for(auto it = std::begin(tmp); it != std::end(tmp); ++it) {
            _disp_Game.push_back(Text(37, Yposition, (*it).c_str(), WHITE, 22));
            Yposition += 4;
        }
    }
}