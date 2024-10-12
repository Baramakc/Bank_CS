#include <iostream> // Ввод/вывод информации
#include <string.h> //Фукнции bzeto, c_str, memset, strcpy, strlen
//#include <string> // Для преобразования string в char (c_str())

//#include <stdio.h>
#include <sys/types.h> //Типы данных для сокетов
#include <sys/socket.h> //Сокеты
//#include <netinet/in.h> //Определение структур данных и функций,
// используемых для работы в сети IPv4 IPv6 

#include <arpa/inet.h> //определения функций для работы с интернет-адресами bind(Например)

//#include <stdlib.h>
//#include <unistd.h> //Фукнции многих системных вызовов, таких как srandom и random, функция write и getpid

//#include <netdb.h> //предоставляет определения для операций с сетевой базой данных.
// in_port_t и in_addr_t, а также структуры для работы с адресами узлов, сетей, протоколов и сервисов

//#include <sys/uio.h> //пределяет структуру iovec, которая используется для векторных операций ввода-вывода (I/O)
#include <sys/time.h> //Время gettimeofday
//Детальная информация прошедшего процессорного времени в структуры
#include <sys/wait.h> //close 
//Чтобы использовать системный вызов wait(),
//#include <fcntl.h> //это заголовок в библиотеке C POSIX для языка программирования C
//открытие файла, получение и изменение разрешений файла, блокировка файла для редактирования
//#include <fstream> // C++ Работа с файлами

int main()
{
    char msg[1500];
     
    // Структура для хранения данных. Протокол и чтобы была связь с клиентом
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(4321);
 
    //Создание сокета с нужным протоколом
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        std::cerr << "Error establishing the server socket\n";
        exit(0);
    }

    //Привязываем сокет к сокету с протоколом и структуре хранения данных
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, sizeof(servAddr));
    if(bindStatus < 0)
    {
        std::cerr << "Error binding socket to local address\n";
        exit(0);
    }
    std::cout << "Waiting for a client to connect...\n";
    
    // Прослушиваем и ждём подклбчения. SOMAXCONN - количество доступных подключений(максимум)
    listen(serverSd, SOMAXCONN);
    
    //Для получения запроса от клиента с помощью accept
    //нам нужен новая структура для связи с клиентом
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    //Accept(Принять соединение Клиента) - создание нового дескриптор сокета 
    //для обработки нового соединения с клиентом
    int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    if(newSd < 0)
    {
        std::cerr << "Error accepting request from client!\n";
        exit(1);
    }
    std::cout << "Connected with client!\n";


    //Для отслеживания время сеанса
    struct timeval start1, end1;
    gettimeofday(&start1, nullptr);
    //Для отслеживания объема отправленных данных
    int bytesRead, bytesWritten = 0;
    
    while(1)
    {
        //receive a message from the client (listen)
        std::cout << "Awaiting client response...\n";
       
        memset(&msg, 0, sizeof(msg));

        //Принятие информации и записи ее в массив msg
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

        // //Для проверки завершения работы Сервера и Клиента(поступает информация от клиента)
        if(!strcmp(msg, "exit"))
        {
            std::cout << "Client has quit the session\n";
            break;
        }
        std::cout << "Client: " << msg << "\n";
        std::cout << ">";

        //Запись в строку данных с пробелами
        std::string data;
        std::getline(std::cin, data);
        
        // Очиска массива msg 
        memset(&msg, 0, sizeof(msg)); 
        //Преобразование string в char*
        strcpy(msg, data.c_str());
        //Для завершения работы Сервера и Клиента
        if(data == "exit")
        {
            //sОтправка сообщения о завершении работы клиенту
            send(newSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        //Запись количества памяти в сообщении
        bytesWritten += send(newSd, (char*)&msg, strlen(msg), 0);
    }
    //Работа сервера завершилась
    gettimeofday(&end1, nullptr);
    
    //Закрытие сокетов
    close(newSd);
    close(serverSd);

        //Вывод времени работы сервера и количество байтов сообщений
    std::cout << "********Session********\n";
    std::cout << "Bytes written: " << bytesWritten << " Bytes read: " << bytesRead << "\n";
    std::cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) << " secs\n";
    std::cout << "Connection closed...\n";
    return 0;   
}