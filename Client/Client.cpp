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

#include <netdb.h> //предоставляет определения для операций с сетевой базой данных.
// in_port_t и in_addr_t, а также структуры для работы с адресами узлов, сетей, протоколов и сервисов
//gethostbyname()


//#include <sys/uio.h> //пределяет структуру iovec, которая используется для векторных операций ввода-вывода (I/O)
#include <sys/time.h> //Время gettimeofday
//Детальная информация прошедшего процессорного времени в структуры
#include <sys/wait.h> //close 
//Чтобы использовать системный вызов wait(),
//#include <fcntl.h> //это заголовок в библиотеке C POSIX для языка программирования C
//открытие файла, получение и изменение разрешений файла, блокировка файла для редактирования
//#include <fstream> // C++ Работа с файлами



int main(int argc, char *argv[])
{
    // IP и порт для подлючения
    const char *serverIp = "127.0.0.1"; int port = 4321; 

    //Массив для передачи сообщений
    char msg[1500]; 

    

    struct hostent* host = gethostbyname(serverIp);  //извлекает сведения об узле, соответствующие имени узла, из базы данных узла.

    // Структура для хранения данных. Протокол и чтобы была связь с клиентом
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);

    // Сокет с протоколамии
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    //Cоединения сокета с сервера
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        std::cerr << "Error connecting to socket!\n"; 
        return 1;
    }

    std::cout << "Connected to the server!\n";
    //Для отслеживания объема отправленных данных
    int bytesRead, bytesWritten = 0;
    //Для отслеживания время сеанса
    struct timeval start1, end1;
    gettimeofday(&start1, nullptr);
    
    while(1)
    {
        //Cчитывание в строку сообщения с пробелами
        std::cout << ">";
        string data;
        std::getline(std::cin, data);

        
        memset(&msg, 0, sizeof(msg));

        //Преобразование string в char* и записывание в msg 
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }

        //Количетсов байт в сообщении(отправлено)
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        std::cout << "Awaiting server response...\n";

        //Очистка массива msg
        memset(&msg, 0, sizeof(msg));

        //Количетсов байт в сообщении(получено)
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);

        //Отключение серера и клиента
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        cout << "Server: " << msg << endl;
    }
    gettimeofday(&end1, nullptr);
    
    //Деструктор сокета
    close(clientSd);

    //Информация о соединении
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;    
}