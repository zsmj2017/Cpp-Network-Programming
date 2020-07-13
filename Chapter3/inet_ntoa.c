#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]) {
	struct sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);
	addr2.sin_addr.s_addr = htonl(0x1010101);
	
	// inet_atoa内的字符串再获取后必须立刻拷贝
	str_ptr = inet_ntoa(addr1.sin_addr);
	strcpy(str_arr, str_ptr);
	printf("Dotted_Decimal notation1: %s \n", str_ptr);

	inet_ntoa(addr2.sin_addr);
	// str_ptr的内容已遭到修改
	printf("Dotted_Decimal notation1: %s \n", str_ptr);
	printf("Dotted_Decimal notation1: %s \n", str_arr);

	return 0;
}
