//
// Created by jeanningros on 3/18/21.
//

#ifndef B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_LIBLOADER_HPP
#define B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_LIBLOADER_HPP

#include <iostream>
#include <dlfcn.h>
#include "IGame.hpp"
#include "IGraphic.hpp"
#include "PersonnalType.hpp"
#include <filesystem>
#include <vector>
#include <math.h>
#include <exception>

namespace Arcade {
    class LibLoader {
    public:
        LibLoader();
        virtual ~LibLoader();
        void *getOpenLibrary();
        void setOpenLibrary();

        template<typename T>
        T *loadSharedLib(std::string const &fp, T *)
        {
            _sharedLib = dlopen(fp.c_str(), RTLD_LAZY);
            T *(*getLib)();

            if (_sharedLib) {
                getLib = reinterpret_cast<T * (*)()>(dlsym(_sharedLib, "getLib"));
                return getLib();
            }
            else {
                std::cout << "dlopen failed : "<< dlerror() << std::endl;
                return nullptr;
            }
        }
        std::vector<std::pair<std::string, std::string>> getLibAvailable(Arcade::LibType);
    private:

        void *_sharedLib;
    };
    std::string getNameLib(std::string &fp);
}

#endif //B_OOP_400_STG_4_1_ARCADE_NICOLAS_SCHNEIDER_LIBLOADER_HPP
