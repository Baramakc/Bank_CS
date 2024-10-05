#pragma once
#include <iostream>

class Client_Date{
    std::string client_login;
    std::string client_password;
    std::string client_name;
    std::string client_key;
    std::string client_role;
    void set_client_key(){
        std::string buffer;
        for(int i = 0; i < 5; i++){
            buffer[i] += rand()%126;
        }
    }
    char get_client_key(int buffer){
        return this->client_key[buffer];
    }

    std::string hash(std::string buffer){
        if(this->client_key.empty()) set_client_key();
        int lenght = buffer.size();
        for(int i = 0; i < lenght; i++){
            if(buffer[i]%2) buffer.push_back(get_client_key(i%5));
        }
        if(buffer.size() == lenght) buffer.push_back(get_client_key(buffer[0]%5));
        return buffer;
    }
    std::string rehash(std::string buffer){
        int lenght = buffer.size();
        for(int i = 0; i < lenght; i++){
            if(buffer[i]%2) buffer.pop_back();
        }
        if(buffer.size() == lenght) buffer.pop_back();
        return buffer;
    }

public:
    void set_client_login(std::string buffer){
        buffer = hash(buffer);
        this->client_login = buffer;
    }
    void set_client_password(std::string buffer){
        buffer = hash(buffer);
        this->client_password = buffer;
    }
    void set_client_name(std::string buffer){
        this->client_name = buffer;
    }
    void set_client_role(std::string buffer){
        this->client_role = buffer;
    }

    std::string get_client_login(){
        return rehash(this->client_login);
    }
    std::string get_client_password(){
        return rehash(this->client_password);
    }
    std::string get_client_name(){
        return this->client_name;
    }
    std::string get_client_role(){
        return this->client_role;
    }
};