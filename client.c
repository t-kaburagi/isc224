#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
int main(int argc, char** argv)
{
    int sd;
    struct sockaddr_in addr;

    char buf[2014];
    sprintf( buf, "This is client process %d!", getpid() );
    perror( buf ); 

    // IPv4 TCP のソケットを作成する
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
 
    // 送信先アドレスとポート番号を設定する
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
 
    // サーバ接続（TCP の場合は、接続を確立する必要がある）
    connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));
 
    // パケットを TCP で送信
    sprintf( buf, "Client %d sending message...", getpid() );
    if(send(sd, buf, strlen(buf), 0) < 0) {
        perror("send");
        return -1;
    }
 
    close(sd);
 
    return 0;
}

