//
// Created by jbroesch on 10/16/21.
//

#ifndef BABEL_IDATABASE_HPP
#define BABEL_IDATABASE_HPP

namespace babel_server {

    class IDatabase {
    public:
        IDatabase() = default;
        IDatabase(const IDatabase&) =delete;

        virtual IDatabase& operator=(const IDatabase&) =delete;
        virtual void add_user(const std::string&, const std::string&) = 0;
        virtual bool check_if_user_exist(const std::string&) = 0;
        virtual void display_database() = 0;
        virtual bool are_they_friends(const int& user_one, const int& user_two) = 0;
        virtual void add_friends(const int& user_one, const int& user_two) = 0;
        virtual bool add_request(std::string&) = 0;
        virtual bool check_if_request(std::string&) = 0;
        virtual bool check_if_good_password_username(const std::string &, const std::string &) = 0;
        virtual int name_to_id(std::string name) = 0;
    };
}

#endif //BABEL_IDATABASE_HPP
