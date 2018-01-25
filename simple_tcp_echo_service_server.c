/**
 * socket实验 回声服务器
 * 12.24
 * 服务器端
 * macOS 10.12
 * by wjh
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 100

int main()
{
    //创建套接字
    int servSock = socket(AF_INET, SOCK_STREAM, 0);

    //绑定套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));            //每个字节都用0填充
    sockAddr.sin_family = PF_INET;                     //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //具体的IP地址
    sockAddr.sin_port = htons(1234);                   //端口
    bind(servSock, (struct sockaddr *)&sockAddr, sizeof(sockAddr));

    //进入监听状态
    listen(servSock, 20);

    char buffer[BUF_SIZE]; //缓冲区
    //接收客户端请求
    struct sockaddr_in clntAddr;
    socklen_t nSize = sizeof(clntAddr);

    while (1)
    {
        int clntSock = accept(servSock, (struct sockaddr *)&clntAddr, &nSize);

        int strLen = recv(clntSock, buffer, BUF_SIZE, 0); //接收客户端发来的数据

        // 客户端退出
        if (buffer[0] == 'q')
        {
            printf("over~\n");
            exit(0);
        }
        // 打印客户端发送的数据
        printf("string from client: %s\n", buffer);

        send(clntSock, buffer, strLen, 0); //将数据原样返回

        //关闭套接字
        close(clntSock);
        memset(buffer, 0, BUF_SIZE);
    }

    close(servSock);

    return 0;
}