#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char* addr = "1.2.3.4";

    struct sockaddr_in addr_inet;

    // inet_aton 作用与 inet_addr 一致，但其配合struct使用，仅此使用频率更高
    if (!inet_aton(addr, &addr_inet.sin_addr)) {
        printf("Here is a error in conversion!\n");
    } else {
        printf("Network ordered addr: %#x\n", addr_inet.sin_addr.s_addr);
    }

    return 0;
}
