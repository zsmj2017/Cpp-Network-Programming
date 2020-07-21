#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    char* addr1 = "1.2.3.4";
    char* addr2 = "1.2.3.256";

    uint64_t conv_addr = inet_addr(addr1);
    if (conv_addr == INADDR_NONE) {
        printf("Here is a error in convert!\n");
    } else {
        printf("Network ordered addr: %#lx\n", conv_addr);
    }

    conv_addr = inet_addr(addr2);
    if (conv_addr == INADDR_NONE) {
        printf("Here is a error in convert!\n");
    } else {
        printf("Network ordered addr: %#lx\n", conv_addr);
    }

    return 0;
}
