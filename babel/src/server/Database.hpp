//
// Created by jbroesch on 10/4/21.
//

#ifndef BABEL_DATABASE_HPP
#define BABEL_DATABASE_HPP

#include <sqlite3.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "IDatabase.hpp"

extern bool sig;

namespace babel_server {

    class Database : public IDatabase{
    public:
        Database();
        Database(const Database&) =delete;
        Database& operator=(const Database&) =delete;
        ~Database();
        void add_user(const std::string&, const std::string&) override;
        bool check_if_user_exist(const std::string&) override;
        static int callback(void *NotUsed, int argc, char **argv, char **azColName);
        void display_database() override;
        bool are_they_friends(const int& user_one, const int& user_two) override;
        void add_friends(const int& user_one, const int& user_two) override;
        bool add_request(std::string&) override;
        bool check_if_request(std::string&) override;
        bool check_if_good_password_username(const std::string &, const std::string &) override;
        std::string id_to_name(int);
        static std::string _retrieve_name;
        int name_to_id(std::string name) override;
        std::vector<std::pair<std::string, int>> list_user_friends(int);
        static std::vector<std::pair<std::string, int>> _list_friends;
        static int _searching_id;
        static int _found_id;

    private:
        sqlite3 *_db;
        char *_zErrMsg = nullptr;
        int _rc;
        std::string _sql;
    };
}


#endif //BABEL_DATABASE_HPP
