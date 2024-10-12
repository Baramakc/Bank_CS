#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

class Client_Dates{
    std::string client_login;
    std::string client_password;
    std::string client_name;
    std::string client_key;
    std::string client_role;

    std::string main_path = "./Client_Dates/";

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

    void load_client_login(std::string buffer){
        this->client_login = buffer;
    }
    void load_client_password(std::string buffer){
        this->client_password = buffer;
    }
    void load_client_name(std::string buffer){
        this->client_name = buffer;
    }
    void load_client_role(std::string buffer){
        this->client_role = buffer;
    }

    std::string save_client_login(){
        return this->client_login;
    }
    std::string save_client_password(){
        return this->client_password;
    }
    std::string save_client_name(){
        return this->client_name;
    }
    std::string save_client_role(){
        return this->client_role;
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


    // Сохранение(загрузка) в(из) класс(а) данных из файла(в файл)
    void save_all_date(){
    std::vector <std::string> date {save_client_login(), save_client_password(),
                                    save_client_name(), save_client_role()}; 
    std::ofstream file(main_path + date[0]);
    for(int i = 0; i < date.size(); i++){
        file << date[i];
    } 
    file.close();
    }
    void load_all_date(std::string buffer){
        if(std::filesystem::exists(main_path + buffer)){
            std::vector <std::string> date(4);
            std::ifstream file(main_path + buffer);
            for(int i = 0; i < date.size(); i++){
                file >> date[i];
            }
            load_client_login(date[0]); load_client_password(date[1]); load_client_name(date[2]); load_client_role(date[3]);
            file.close();
        }
    }


};