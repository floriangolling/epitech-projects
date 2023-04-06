//
// Created by jbroesch on 30/03/2021.
//

#include "HowToPlay.hpp"

void __attribute__((constructor)) ctor()
{
}

void __attribute__((destructor)) dtor()
{
}

extern "C" Arcade::LibType getLibType()
{
    return Arcade::GAME;
}

extern "C" Arcade::IGame *getLib()
{
    return new Arcade::Howtoplay();
}

namespace Arcade {
    Howtoplay::Howtoplay() {
        int y_pos = 13;
        int count = 2;
        set_dispGraphical();
        _disp_info.push_back(Text(10, 10, std::string("Hi there ! You will find below some useful informations !"), WHITE,22));
        _disp_info.push_back(Text(10, 13, "Press F1 to load the " + _dispGraphical.at(0) + " librarie.", WHITE,22));
        if (_dispGraphical.size() > 1) {
            y_pos += 3;
            _disp_info.push_back(
                    Text(10, y_pos, "Press F" + std::to_string(count) + " to load the " + _dispGraphical.at(1) + " librarie.",
                         WHITE, 22));
        }
        if (_dispGraphical.size() > 2) {
            y_pos += 3;
            count += 1;
            _disp_info.push_back(
                    Text(10, y_pos, "Press F" + std::to_string(count) + " to load the " + _dispGraphical.at(2) + " librarie.",
                         WHITE, 22));
        }
        y_pos += 3;
        _disp_info.push_back(Text(10, y_pos, "Play games with the arrow keys.", WHITE,22));
        y_pos += 3;
        _disp_info.push_back(Text(10, y_pos, "Press ESC in game to go back to the menu or, if you already are, to exit the game.", WHITE,22));
        y_pos += 3;
        _disp_info.push_back(Text(10, y_pos, "You can enter your username on the menu interface to show who run the world !", WHITE,22));
        y_pos += 3;
        _disp_info.push_back(Text(10, y_pos, "Have fun playing our games !", WHITE,22));
        std::ifstream in_l;
        in_l.exceptions ( std::ifstream::badbit );
        try {
            in_l.open("./GamesLib/HowToPlay/greenghost.txt");
            std::string howtochar;
            while (std::getline(in_l, howtochar))
                _ascii_howto.push_back(howtochar);
        } catch (std::ifstream::failure &e) {
            std::cerr << "Can't open/read/close file : greenghost.txt" << std::endl;
            throw std::exception();
        }
        in_l.close();
    }

    Howtoplay::~Howtoplay() {

    }

    CommandType Howtoplay::getEvent(IGraphic &graph) {
        CommandType ev = graph.getInput();
        return ev;
    }

    void Howtoplay::update(double elapsed_time) {
        elapsed_time += 1;
    }

    void Howtoplay::draw(IGraphic &graph) {
        graph.myClear();
        int x_pos = 0;
        int y_pos = 0;
        for(auto it = std::begin(_ascii_howto); it != std::end(_ascii_howto); ++it) {
            for (std::string::size_type i = 0; i < (*it).size(); i++) {
                Pixel *pix = new Pixel(y_pos, x_pos, BLACK, 1);
                if ((*it)[i] == '1')
                    pix->setColor(GREEN);
                if ((*it)[i] == 'L')
                    pix->setColor(WHITE);
                if ((*it)[i] == 'P')
                    pix->setColor(BLACK);
                graph.drawPixel(pix);
                delete(pix);
                y_pos += 1;
            }
            y_pos = 0;
            x_pos += 1;
        }
        for(auto it = std::begin(_disp_info); it != std::end(_disp_info); ++it)
            graph.drawText(&(*it));
        graph.myRefresh();
    }
        void Howtoplay::setPlayerName(std::string &name)
    {
        (void)name;
        return;
    }

    std::string Howtoplay::getNameGraphical(std::string &fp) {
        std::string newStr = fp;

        newStr.erase(0, 13);
        newStr.erase(newStr.size() - 3, newStr.size());
        return newStr;
    }

    void Howtoplay::set_dispGraphical() {
        std::string fp;
        void *sharedLib;
        LibType (*getLibType)();
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
                if (getLibType() == GRAPHIC)
                    tmp.push_back(getNameGraphical(fp));
                dlclose(sharedLib);
            }
        }
        std::sort(tmp.begin(), tmp.end());
        for(auto it = std::begin(tmp); it != std::end(tmp); ++it)
            _dispGraphical.push_back((*it).c_str());
    }

}