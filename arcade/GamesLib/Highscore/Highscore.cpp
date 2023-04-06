//
// Created by jbroesch on 30/03/2021.
//

#include "Highscore.hpp"
#include "SaveHighScore.hpp"

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
    return new Arcade::Highscore();
}

namespace Arcade {

    Highscore::Highscore() {
        std::ifstream in_l;
        in_l.exceptions ( std::ifstream::badbit );
        try {
            in_l.open("./GamesLib/Highscore/ascii_highscore.txt");
            std::string ascii_high;
            while (std::getline(in_l, ascii_high))
                _ascii_highscore.push_back(ascii_high);
        } catch (std::ifstream::failure &e) {
            std::cerr << "Can't open/read/close file : ascii_highscore.txt" << std::endl;
            throw std::exception();
        }
        in_l.close();
        _high_score = parse_file();
    }

    Highscore::~Highscore() {

    }

    CommandType Highscore::getEvent(IGraphic &graph) {
        CommandType ev = graph.getInput();
        return ev;
    }

    void Highscore::update(double elapsed_time) {
        elapsed_time += 1;
    }

    void Highscore::draw(IGraphic &graph) {
        graph.myClear();
        int x_pos = 0;
        int y_pos = 0;
        for(auto it = std::begin(_ascii_highscore); it != std::end(_ascii_highscore); ++it) {
            for (std::string::size_type i = 0; i < (*it).size(); i++) {
                Pixel *pix = new Pixel(y_pos, x_pos, BLACK, 1);
                if ((*it)[i] == '#')
                    pix->setColor(RED);
                graph.drawPixel(pix);
                delete(pix);
                y_pos += 1;
            }
            y_pos = 0;
            x_pos += 1;
        }
        x_pos = 27;
        y_pos = 20;
        int i = 0;
        for(auto it = std::begin(_high_score); it != std::end(_high_score); ++it, i++) {
            if (i == 10)
                break;
            Text *gameName = new Text(x_pos, y_pos, (*it)[0], WHITE, 22);
            Text *playerName = new Text(x_pos + 10, y_pos, (*it)[1], WHITE, 22);
            Text *score = new Text(x_pos + 25, y_pos, (*it)[2], WHITE, 22);
            graph.drawText(gameName);
            graph.drawText(score);
            graph.drawText(playerName);
            delete(gameName);
            delete(playerName);
            delete(score);
            y_pos += 3;
        }
        graph.myRefresh();
    }

    void Highscore::setPlayerName(std::string &name)
    {
        (void)name;
        return;
    }
}