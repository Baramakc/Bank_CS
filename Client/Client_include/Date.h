#pragma once
#include <iostream>

class Client_Dates{
    std::string client_login;
    std::string client_password;
    std::string client_name;
    std::string client_role;

public:
    void set_client_login(std::string buffer){
        this->client_login = buffer;
    }
    void set_client_password(std::string buffer){
        this->client_password = buffer;
    }
    void set_client_name(std::string buffer){
        this->client_name = buffer;
    }
    void set_client_role(std::string buffer){
        this->client_role = buffer;
    }

    std::string get_client_login(){
        return this->client_login;
    }
    std::string get_client_password(){
        return this->client_password;
    }
    std::string get_client_name(){
        return this->client_name;
    }
    std::string get_client_role(){
        return this->client_role;
    }
};