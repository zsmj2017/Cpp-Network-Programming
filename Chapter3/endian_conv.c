#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("Host Post: %#x\n", host_port);
    printf("NetWork Post: %#x\n", net_port);
    printf("Host Address: %#lx\n", host_addr);
    printf("NetWork Address: %#lx\n", net_addr);
}
