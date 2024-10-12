#pragma once
#include <sys/socket.h>
#include <iostream>
#include "Date.h"

#include <thread>

#include "zlib.h"


class Interface{
    int sock;
    Client_Dates client_dates;
    std::string status = "entrance";

    void send_all_date(){
        char* buffer = "all";
        send(sock, buffer,sizeof(buffer),0);

        send(sock, client_dates.get_client_login().c_str(), sizeof(client_dates.get_client_login()), 0);
        send(sock, client_dates.get_client_password().c_str(), sizeof(client_dates.get_client_password()), 0);
        send(sock, client_dates.get_client_role().c_str(), sizeof(client_dates.get_client_role()), 0);
        send(sock, client_dates.get_client_name().c_str(), sizeof(client_dates.get_client_name()), 0);
    }

    void recv_all_date(){
        
    }   

public:
    Interface(int socket){
        this->sock = socket;
    }
    



    void registration(){
        std::cout << "Hello user in my project!\nLet's go registration!\n";
        std::string buffer;

        std::cout << "Input your login: "; std::cin >> buffer; client_dates.set_client_login(buffer);
        
        while(true){
        std::cout << "Input your password: "; std::cin >> buffer;
        std::string other_buffer;
        std::cout << "Input your password again: "; std::cin >> other_buffer;
            if(buffer == other_buffer) {
                client_dates.set_client_password(buffer);
                break;
            }
            else std::cout << "The passwords are not identical!\nAgain!\n";
        }
        
        while(buffer != "Student" || buffer != "Teacher"){
            std::cout << "Input your role(Student or Teacher): "; std::cin >> buffer;
            std::cout << "Role dont correct!\nAgain\n";
        }
        client_dates.set_client_role(buffer);
        
        std::cout << "Input your name: "; std::cin >> buffer; client_dates.set_client_name(buffer);


        //Отправка данных на сервер
        


        //Do thread autorization and send date for server    
        autorization();
    }

    void autorization(){
        
    }

    void entrance(){
        int number;
        std::cout << "1 - Registration\n2 - Autorization\n";
        switch(number){
            case 1:
                registration();
                break;
            case 2:
                autorization();
                break;
            default:
                std::cout << "Uncorrect number!";
                break;
        }
    }



    ~Interface();
};