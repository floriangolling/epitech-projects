//
// Created by jbroesch on 10/4/21.
//

#include <iostream>
#include <utility>
#include <functional>
#include "Database.hpp"

namespace babel_server {
    Database::Database() {
        _rc = sqlite3_open("babel.db", &_db);
        if(_rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(_db));
            sig = true;
        } else {
            fprintf(stderr, "Opened database successfully\n");
        }
        sqlite3_exec(_db, "PRAGMA foreign_keys = on", nullptr, nullptr, nullptr);
        _sql = "CREATE TABLE IF NOT EXISTS BABELUSER("  \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "USERNAME           VARCHAR(255)    NOT NULL," \
      "PASSWORD           VARCHAR(255)     NOT NULL);";

        add_request(_sql);
        _sql = "CREATE TABLE IF NOT EXISTS BABELFRIENDS("  \
      "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
      "USER_ONE           INT    NOT NULL," \
      "USER_TWO           INT     NOT NULL," \
      "FOREIGN KEY (USER_ONE) REFERENCES BABELUSER(ID)," \
      "FOREIGN KEY (USER_TWO) REFERENCES BABELUSER(ID));";

        add_request(_sql);
    }
    Database::~Database() {
        sqlite3_close(_db);
    }
    bool Database::add_request(std::string &sql) {
        _rc = sqlite3_exec(_db, sql.c_str(), callback, nullptr, &_zErrMsg);
        if( _rc != SQLITE_OK ){
            fprintf(stderr, "SQL error: %s\n", _zErrMsg);
            sqlite3_free(_zErrMsg);
            return false;
        } else {
            std::cout << "Request successful" << std::endl;
            return true;
        }
    }

    bool Database::check_if_good_password_username(const std::string &username, const std::string &password) {
        std::string sql = "SELECT 1 FROM BABELUSER WHERE USERNAME='" + std::string(username.c_str()) + "' AND PASSWORD='" + std::string(password.c_str()) + "'";
        if (check_if_request(sql))
        {
            std::cout << "User found, processing..." << std::endl;
            return true;
        }
        else
        {
            std::cout << "User not found" << std::endl;
            return false;
        }
    }

    bool Database::check_if_request(std::string &sql) {
        _sql = sql;
        struct sqlite3_stmt *selectstmt;
        int result = sqlite3_prepare_v2(_db, _sql.c_str(), -1, &selectstmt, nullptr);
        if (result == SQLITE_OK)
        {
            if (sqlite3_step(selectstmt) == SQLITE_ROW)
            {
                sqlite3_finalize(selectstmt);
                return true;
            }
            else
            {
                sqlite3_finalize(selectstmt);
                return false;
            }
        }
        fprintf(stderr, "SQL error: %s\n", _zErrMsg);
        return false;
    }
     int Database::callback(void *NotUsed, int argc, char **argv, char **azColName) {
        int i;
        for(i = 0; i<argc; i++) {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }
    void Database::add_user(const std::string& username, const std::string& password) {
        std::string sql = "INSERT INTO BABELUSER ('USERNAME', 'PASSWORD') VALUES ('" + std::string(username.c_str()) + "', '" + std::string(password.c_str()) + "');";
        if (add_request(sql))
            std::cout << username << " account created successfully" << std::endl;
    }
    bool Database::are_they_friends(const int& user_one, const int& user_two) {
        std::string sql = "SELECT * FROM BABELFRIENDS WHERE USER_ONE='" + std::to_string(user_one) + "' AND USER_TWO='" + std::to_string(user_two) + "'";
        std::string sql_inverse = "SELECT * FROM BABELFRIENDS WHERE USER_ONE='" + std::to_string(user_two) + "' AND USER_TWO='" + std::to_string(user_one) + "'";
        if (check_if_request(sql) || check_if_request(sql_inverse))
        {
            std::cout << "User " << id_to_name(user_one) << " and user " << id_to_name(user_two) << " are friends" << std::endl;
            return true;
        }
        else
        {
            std::cout << "User " << id_to_name(user_one) << " and user " << id_to_name(user_two) << " are not friends" << std::endl;
                return false;
        }
    }
    void Database::add_friends(const int& user_one, const int& user_two) {
        std::string sql = "INSERT INTO BABELFRIENDS ('USER_ONE', 'USER_TWO') VALUES ('" + std::to_string(user_one) + "', '" + std::to_string(user_two) + "');";
        if (add_request(sql))
            std::cout << id_to_name(user_one) << " and " << id_to_name(user_two) << " are now friends !" << std::endl;
    }
    void Database::display_database() {
        std::string query = "SELECT * FROM BABELUSER;";
        sqlite3_exec(_db, query.c_str(), callback, NULL, NULL);
        std::string query2 = "SELECT * FROM BABELFRIENDS;";
        sqlite3_exec(_db, query2.c_str(), callback, NULL, NULL);
    }
    bool Database::check_if_user_exist(const std::string& username) {
        std::string sql = "SELECT * FROM BABELUSER WHERE USERNAME='" + std::string(username.c_str()) + "'";
        if (check_if_request(sql))
        {
            std::cout << "User found, processing..." << std::endl;
            return true;
        }
        else
        {
            std::cout << "User not found" << std::endl;
            return false;
        }
    }
    static int id_name_callback(void *data, int argc, char **argv,
                                   char **azColName) {
        Database::_retrieve_name = argv[0];
        return 0;
    }

    static int name_id_callback(void *data, int argc, char **argv,
                                   char **azColName) {
        Database::_found_id = stoi(std::string(argv[0]));
        return 0;
    }
    std::string Database::id_to_name(int id) {
        std::string sql = "SELECT USERNAME FROM BABELUSER WHERE ID='" + std::to_string(id) + "'";
        struct sqlite3_stmt *selectstmt;
        _rc = sqlite3_exec(_db, sql.c_str(), id_name_callback, &selectstmt, &_zErrMsg);
        if (_rc != SQLITE_OK){
            std::cout << "SQL error:" << _zErrMsg;
            sqlite3_free(_zErrMsg);
        }
        return _retrieve_name;
    }

    int Database::name_to_id(std::string name) {
        _found_id = -1;
        std::string sql = "SELECT ID FROM BABELUSER WHERE USERNAME='" + std::string(name.c_str()) + "'";
        struct sqlite3_stmt *selectstmt;
        _rc = sqlite3_exec(_db, sql.c_str(), name_id_callback, &selectstmt, &_zErrMsg);
        if (_rc != SQLITE_OK){
            std::cout << "SQL error:" << _zErrMsg;
            sqlite3_free(_zErrMsg);
        }
        return _found_id;
    }

    std::vector<std::pair<std::string, int>> Database::list_user_friends(int id) {
        _list_friends.clear();
        _searching_id = id;
        std::string sql = "SELECT USER_ONE, USER_TWO FROM BABELFRIENDS WHERE USER_ONE ='" + std::to_string(id) + "' OR USER_TWO ='" + std::to_string(id) + "'";
        struct sqlite3_stmt *selectstmt;
        _rc = sqlite3_exec(_db, sql.c_str(), [](void *data, int argc, char **argv,
                                                    char **azColName) -> int {
            for (int i = 0; argv[i]; i++) {
                if (std::stoi(argv[i]) != Database::_searching_id) {
                    Database::_list_friends.emplace_back(
                            "", std::stoi(argv[i]));
                }
            }
            return 0;
            }, &selectstmt, &_zErrMsg);
        if (_rc != SQLITE_OK){
            std::cout << "SQL error:" << _zErrMsg;
            sqlite3_free(_zErrMsg);
        }
        for(auto & _list_friend : _list_friends)
        {
            _list_friend.first = id_to_name(_list_friend.second);
        }
        _searching_id = -1;
        return _list_friends;
    }
    std::string Database::_retrieve_name = "";
    std::vector<std::pair<std::string, int>> Database::_list_friends = {};
    int Database::_searching_id = -1;
    int Database::_found_id = -1;
}
