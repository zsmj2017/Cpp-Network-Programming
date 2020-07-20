#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(const char* message);

int main(int argc, char* argv[]) {
    int serv_sock;
    int clnt_sock;

    // struct sockaddr_in
    // {
    //     sa_family_t    sin_family // 地址族
    //     uint16_t       sin_port   // 16位端口号
    //     struct in_addr sin_addr   // 32位IP地址
    //     char           zero[8]    // 暂未使用
    //  }
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World";

    // 输入参数检测
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 返回值类似于文件标识符
    // PF_INET:IPv4 PF_INET6:IPv6
    // SOCK_STREAM:面向连接 SOCK_DGRAM:面向消息
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }

    // 结构体赋值
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // h:host n:network l:long s:short
    // 转为网络字节序(大端序)
    // INADDR_ANY:自动分配IP地址
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    // struct sockaddr
    // {
    //     sa_family_t sin_family  // 地址族
    //     char        sa_data[14] // 地址信息（包含IP,端口号）
    // }
    // bind 函数第二参数需要传入sockaddr格式的指针(并非仅为IPv4设计)
    // 显然，sa_data目前仅使用了2前6个字节,末尾补0,正确填写sockaddr_in
    // 结构可保证bind函数正确使用
    // bind : 向已获取到的socket分配网络地址
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) ==
        -1) {
        error_handling("bind() error");
    }

    // 执行listen
    if (listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }

    // 这个变量似乎并不需要被定义，直接使用sizeof即可
    // 执行accept
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock =
        accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        error_handling("accept() error");
    }

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(const char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
