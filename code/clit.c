#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	char s1[100];
	char s2[100];

	if(argc != 5)
	{
		printf("Usage : %s <code> <IP> <port_1> <port_2>\n", argv[0]);
		exit(1);
	}

	strcpy(s1, "./client ");
	strcat(s1, argv[1]);
	strcat(s1, " ");
	strcat(s1, argv[2]);
	strcat(s1, " ");
	strcat(s1, argv[3]);
	system(s1);

	sleep(3);

	strcpy(s2, "./cli3 ");
	strcat(s2, argv[2]);
	strcat(s2, " ");
	strcat(s2, argv[4]);
	system(s2);

	return 0;
}
