// 流式套接字接收变长数据

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 100

int main()
{

    return 0;
}

int recvvl(int s, char *recvbuf, unsigned int recvbuflen)
{
    int iResult;
    unsigned int reclen; //消息首部长度
    iResult = recvn(s, (char *)&reclen, sizeof(unsigned int));
    if (iResult != sizeof(unsigned int))
    {
        if (iResult == -1)
        {
            printf("error\n");
            return -1;
        }
        else
        {
            printf("链接关闭！\n");
            return 0;
        }
    }
    reclen = ntohl(reclen);
    if (reclen > recvbuflen)
    {
        while (reclen > 0)
        {
            iResult = recvn(s, recvbuf, recvbuflen);
            if (iResult != recvbuflen)
            {
                if (iResult == -1)
                {
                    printf("error\n");
                    return -1;
                }
                else
                {
                    printf("链接关闭\n");
                    return 0;
                }
            }
            reclen -= recvbuflen;
            if (reclen < recvbuflen)
                recvbuflen = reclen;
        }
        printf("overflow\n");
        return -1;
    }

    iResult = recvn(s,recvbuf,reclen);
    if(iResult !=reclen){
        if(iResult==-1){
            printf("error\n");
            return -1;
        }
        else{
            printf("closed\n");
            return 0;
        }
    }
    return iResult;
}