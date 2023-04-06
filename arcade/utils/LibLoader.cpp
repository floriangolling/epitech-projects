//
// Created by jeanningros on 3/18/21.
//

#include "LibLoader.hpp"

Arcade::LibLoader::LibLoader() : _sharedLib(nullptr){
}

Arcade::LibLoader::~LibLoader() {
}

std::vector<std::pair<std::string, std::string>> Arcade::LibLoader::getLibAvailable(Arcade::LibType type) {
    std::vector<std::pair<std::string, std::string>> libAvailable;
    std::vector<std::string> tmp;
    std::string fp;
    void *sharedLib;
    LibType (*getLibType)();
    int count;

    for (const auto &entry : std::filesystem::directory_iterator("./lib/")) {
        fp = entry.path();
        sharedLib = dlopen(fp.c_str(), RTLD_LAZY);
        if (sharedLib) {
            getLibType = reinterpret_cast<Arcade::LibType (*)()>(dlsym(sharedLib, "getLibType"));
            if (!getLibType) {
                std::cerr << fp << " not a valide library, please delete it and try again." << std::endl;
                throw std::exception();
            }
            if (getLibType() == type) {
                tmp.push_back(fp);
                count += 1;
            }
        }
    }
    if (count == 0 && type == GRAPHIC) {
        std::cerr << "No graphical library available" << std::endl;
        throw std::exception();
    }
    std::sort(tmp.begin(), tmp.end());
    for(auto it = std::begin(tmp); it != std::end(tmp); ++it) {
        std::string tmps = (*it).c_str();
        libAvailable.push_back(std::make_pair(getNameLib(tmps), (*it).c_str()));
    }
    return libAvailable;
}

std::string Arcade::getNameLib(std::string &fp) {
    std::string newStr = fp;

    newStr.erase(0, 13);
    newStr.erase(newStr.size() - 3, newStr.size());
    return newStr;
}

void *Arcade::LibLoader::getOpenLibrary() {
    return _sharedLib;
}

void Arcade::LibLoader::setOpenLibrary() {
    _sharedLib = nullptr;
}