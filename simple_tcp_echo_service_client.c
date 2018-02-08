/**
 * socket实验 回声服务器
 * 12.24
 * 客户端
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
    //向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    
    char bufSend[BUF_SIZE] = {0};
    char bufRecv[BUF_SIZE] = {0};

    while (1)
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        connect(sock, (struct sockaddr *)&sockAddr, sizeof(sockAddr));

        //获取用户输入的字符串并发送给服务器
        printf("input a string: ");
        scanf("%s", bufSend);

        send(sock, bufSend, strlen(bufSend), 0);

        // 退出
        if (bufSend[0] == 'q')
        {
            printf("over~\n");
            exit(0);
        }

        //接收服务器传回的数据
        recv(sock, bufRecv, BUF_SIZE, 0);

        //输出接收到的数据
        printf("server echo: %s\n", bufRecv);

        memset(bufSend, 0, BUF_SIZE); //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE); //重置缓冲区
                                      //关闭套接字
        close(sock);
    }

    return 0;
}