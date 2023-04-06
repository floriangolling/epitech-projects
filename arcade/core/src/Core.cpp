//
// Created by Jean-Baptiste ROESCH on 29/03/2021.
//

#include "Core.hpp"

    std::map<Arcade::CommandType, int> keycoreMap {
        {Arcade::CommandType::A, 'a'},
        {Arcade::CommandType::B, 'b'},
        {Arcade::CommandType::C, 'c'},
        {Arcade::CommandType::D, 'd'},
        {Arcade::CommandType::E, 'e'},
        {Arcade::CommandType::F, 'f'},
        {Arcade::CommandType::G, 'g'},
        {Arcade::CommandType::H, 'h'},
        {Arcade::CommandType::I, 'i'},
        {Arcade::CommandType::J, 'j'},
        {Arcade::CommandType::K, 'k'},
        {Arcade::CommandType::L, 'l'},
        {Arcade::CommandType::M, 'm'},
        {Arcade::CommandType::N, 'n'},
        {Arcade::CommandType::O, 'o'},
        {Arcade::CommandType::P, 'p'},
        {Arcade::CommandType::Q, 'q'},
        {Arcade::CommandType::R, 'r'},
        {Arcade::CommandType::S, 's'},
        {Arcade::CommandType::T, 't'},
        {Arcade::CommandType::U, 'u'},
        {Arcade::CommandType::V, 'v'},
        {Arcade::CommandType::W, 'w'},
        {Arcade::CommandType::X, 'x'},
        {Arcade::CommandType::Y, 'y'},
        {Arcade::CommandType::Z, 'z'},
        {Arcade::CommandType::NUM0, '0'},
        {Arcade::CommandType::NUM1, '1'},
        {Arcade::CommandType::NUM2, '2'},
        {Arcade::CommandType::NUM3, '3'},
        {Arcade::CommandType::NUM4, '4'},
        {Arcade::CommandType::NUM5, '5'},
        {Arcade::CommandType::NUM6, '6'},
        {Arcade::CommandType::NUM7, '7'},
        {Arcade::CommandType::NUM8, '8'},
        {Arcade::CommandType::NUM9, '9'},
        {Arcade::CommandType::BACKSPACE, 45},
        {Arcade::CommandType::DELETE, 45},
    };

Arcade::Core::Core(const std::string &fp) : _charge_lib() {
    update_lib();
    _libGraphic = _charge_lib.loadSharedLib(fp, _libGraphic);
    std::string newStr = fp;
    bool check = false;
    newStr.erase(0, 11);
    newStr.erase(newStr.size() - 3, newStr.size());
    for(auto it = std::begin(_libsAvailable.at(0)); it != std::end(_libsAvailable.at(0)); ++it) {
        if ((*it).first == newStr)
            check = true;
    }
    if (!_libGraphic || !check)
        throw std::exception();
    _graph_Lib = _charge_lib.getOpenLibrary();
    _libGame = _charge_lib.loadSharedLib("lib/arcade_menu.so", _libGame);
    if (!_libGame)
        throw std::exception();
    _game_Lib = _charge_lib.getOpenLibrary();
    _actual_charged_game = MENU;
    _playerName = "__________";
    _is_highlight = 0;
}

void Arcade::Core::update_lib()
{
    if (!_libsAvailable.empty())
        _libsAvailable.clear();
    std::vector<std::pair<std::string, std::string>> tmp_lib;
    tmp_lib = _charge_lib.getLibAvailable(GRAPHIC);
    _libsAvailable.push_back(tmp_lib);
    tmp_lib.clear();
    tmp_lib = _charge_lib.getLibAvailable(GAME);
    _libsAvailable.push_back(tmp_lib);
}

void Arcade::Core::load_library(const std::string &fp, LibType type) {
    size_t start_pos = 0;
    if (type == MENU || type == GAME) {
        _charge_lib.setOpenLibrary();
        _game_Lib = nullptr;
        if (type == MENU) {
            _libGame = _charge_lib.loadSharedLib(fp, _libGame);
            if (!_libGame)
                throw std::exception();
            _actual_charged_game = MENU;
            if (_playerName != "__________") {
                while((start_pos = _playerName.find(' ', start_pos)) != std::string::npos) {
                    _playerName.replace(start_pos, 1, "_");
                    start_pos += 1;
                }
                if (_playerName == "Anonymous")
                    _playerName = "__________";
                _libGame->setPlayerName(_playerName);
            }
        }
        else {
            delete (_libGame);
            _game_Lib = nullptr;
            _libGame = _charge_lib.loadSharedLib(fp, _libGame);
            if (!_libGame)
                throw std::exception();
            _actual_charged_game = GAME;
        }
        _game_Lib = _charge_lib.getOpenLibrary();
    } else if (type == GRAPHIC) {
        _charge_lib.setOpenLibrary();
        delete(_libGraphic);
        _graph_Lib = nullptr;
        _libGraphic = _charge_lib.loadSharedLib(fp, _libGraphic);
        if (!_libGame)
            throw std::exception();
        _graph_Lib = _charge_lib.getOpenLibrary();
    } else {
        _charge_lib.setOpenLibrary();
        _game_Lib = nullptr;
        _graph_Lib = nullptr;
        std::cerr << "Error when loaded library" << std::endl;
        throw std::exception();
    }
}

void Arcade::Core::loop() {
    std::chrono::system_clock::time_point cut = std::chrono::system_clock::now();

    while (!(event())) {
        cut = std::chrono::system_clock::now();
        if (1000 / 30 > (std::chrono::duration<float>(std::chrono::system_clock::now() - cut)).count() * 1000) {
            long time = ((1000 / 30) -  (std::chrono::duration<float>(std::chrono::system_clock::now() - cut)).count() * 1000);
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
        }
        update((std::chrono::duration<float>(std::chrono::system_clock::now() - cut)).count() * 1000);
        display();
    }
}

int Arcade::Core::event() {
    if (!_libGraphic)
        std::exit(84);
    CommandType ev = _libGame->getEvent(*_libGraphic);
    if (ev == CLOSE_WINDOW)
        return 1;
    if (ev == ESC) {
        if (_actual_charged_game == MENU)
            return 1;
        else
            load_library("lib/arcade_menu.so", MENU);
    }
    if (ev == F1 || ev == F2 || ev == F3) {
        auto it = _libsAvailable.at(0).begin();
        if (ev == F1 && (_libGraphic->getName() != it->first) && _libsAvailable.at(0).size() > 0) {
            load_library(it->second, GRAPHIC);
        }
        if (ev == F2 && _libsAvailable.at(0).size() > 1) {
            it++;
            if (_libGraphic->getName() != it->first)
                load_library(it->second, GRAPHIC);
        }
        if (ev == F3 && _libsAvailable.at(0).size() > 2) {
            it += 2;
            if (_libGraphic->getName() != it->first)
                load_library(it->second, GRAPHIC);
        }
        return 0;
    }
    if (ev == UP && _is_highlight > 0 && _actual_charged_game == MENU)
        _is_highlight -= 1;
    if (ev == DOWN && _is_highlight < (short)_libsAvailable.at(1).size() - 1 && _actual_charged_game == MENU)
        _is_highlight += 1;
    if (ev == ENTER && _actual_charged_game == MENU) {
        update_lib();
        auto it_s = _libsAvailable.at(1).begin();
        it_s += _is_highlight;
        if ((short)_libsAvailable.at(1).size() - 1 >= _is_highlight) {
            load_library(it_s->second, GAME);
            _libGame->setPlayerName(_playerName);
            _is_highlight = 0;
        } else {
            update_lib();
            _is_highlight = 0;
        }
    }
    if (ev == SPACE && _actual_charged_game == MENU) {
        update_lib();
        _is_highlight = 0;
    }
    for (const auto&[key, value] : keycoreMap) {
            if (ev == key && _actual_charged_game == MENU)
                if (change_name(value))
                    _libGame->setPlayerName(_playerName);
    }
    return 0;
}

void Arcade::Core::display() {
    if (_libGame)
        _libGame->draw(*_libGraphic);
}

void Arcade::Core::update(double elapsed) {
    if (_libGame)
        _libGame->update(elapsed);
}

bool Arcade::Core::change_name(int letter)
{
    if (letter == 45) {
        if (_playerName[0] == '_')
            return false;
        if (_playerName[9] != '_') {
            _playerName[9] = '_';
            return true;
        }
        _playerName[_playerName.find('_') - 1] = '_';
        return true;
    }
    if (_playerName[9] != '_')
        return false;
    _playerName[_playerName.find('_')] = letter;
    return true;
}

Arcade::Core::~Core() {
    if (_graph_Lib)
        dlclose(_graph_Lib);
    if (_game_Lib)
        dlclose(_game_Lib);
}
