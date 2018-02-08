// 流式套接字接收定长数据

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

int recvn(int s, char *recvbuf, unsigned int fixedlen)
{
	int iResult; // 存储单次recv返回值
	int cnt;	 // 用于统计相对于固定长度还剩余多少字节
	cnt = fixedlen;
	while (cnt > 0)
	{
		iResult = recv(s, recvbuf, cnt, 0);
		if (iResult < 0)
		{
			printf("error\n");
			return -1;
		}
		else if (cnt == 0)
		{
			return fixedlen - cnt;
		}
		printf("%d\n", iResult);
		recvbuf += iResult;
		cnt -= iResult;
	}
	return fixedlen;
}