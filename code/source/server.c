/*
Receive a file over a socket.

Saves it to output.tmp by default.

Interface:

    ./executable [<output_file> [<port>]]

Defaults:

- output_file: output.tmp
- port: 12345
*/

#define _XOPEN_SOURCE 700
#define BUFF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h> /* getprotobyname */
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    char *file_path = "output.tmp";
    char buffer[BUFSIZ];
    char protoname[] = "tcp";
    int client_sockfd;
    int enable = 1;
    int filefd;
    int i;
    int server_sockfd;
    socklen_t client_len;
    ssize_t read_return;
    struct protoent *protoent;
    struct sockaddr_in client_address, server_address;
    unsigned short server_port = 12345u;

	 char* s1;
	 char* s2;
	 char s3[BUFF_SIZE];
	 char s4[100];
	 char s5[100];
	 FILE* s3fp;
	 FILE* result;

	 char s6[100];

//	 FILE* fp_send;
//	 int read_cnt_send;
//	 char message[BUFF_SIZE];

    if (argc > 1) {
        file_path = argv[1];
        if (argc > 2) {
            server_port = strtol(argv[2], NULL, 10);
        }
    }

    /* Create a socket and listen to it.. */
    protoent = getprotobyname(protoname);
    if (protoent == NULL) {
        perror("getprotobyname");
        exit(EXIT_FAILURE);
    }
    server_sockfd = socket(
        AF_INET,
        SOCK_STREAM,
        protoent->p_proto
    );
    if (server_sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        exit(EXIT_FAILURE);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(server_port);
    if (bind(
            server_sockfd,
            (struct sockaddr*)&server_address,
            sizeof(server_address)
        ) == -1
    ) {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_sockfd, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "listening on port %d\n", server_port);

    while (1) {

        client_len = sizeof(client_address);
        puts("waiting for client");
        client_sockfd = accept(
            server_sockfd,
            (struct sockaddr*)&client_address,
            &client_len
        );
        filefd = open(file_path,
                O_WRONLY | O_CREAT | O_TRUNC,
                S_IRUSR | S_IWUSR);
        if (filefd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        do {
            read_return = read(client_sockfd, buffer, BUFSIZ);
            if (read_return == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            if (write(filefd, buffer, read_return) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        } while (read_return > 0);
        close(filefd);

		  s1 = malloc(sizeof(char) * 100);
		  s2 = malloc(sizeof(char) * 100);
		  strcpy(s1, "gcc ");
		  strcat(s1, file_path);
		  strcat(s1, " -o ");
		  strcpy(s5, file_path);
		  strcpy(s2, strtok(s5, "."));
		  strcpy(s4, s2);
		  strcat(s4, ".res");
		  if((result = fopen(s4, "w")) == NULL)
		  {
			  printf("Failed to open result file");	
			  return 1;
		  }
		  strcat(s2, ".out");
		  strcat(s1, s2);
		  printf("%s\n", s1);
		  system(s1);
		  free(s1);
		  s1 = malloc(sizeof(char) * 100);
		  strcat(s1, "./");
		  strcat(s1, s2);
		  printf("%s\n", s1);
		  s3fp = popen(s1, "r");
		  if(NULL == s3fp)
		  {
			  perror("popen failed");
			  return -1;
		  }
		  while(fgets(s3, BUFF_SIZE, s3fp))
		  {
			  printf("%s", s3);
			  fprintf(result, "%s", s3);
		  }
		  pclose(s3fp);
		  fclose(result);
		  //system(s1);

		  strcpy(s6, "./ser3 23456 ");
		  strcat(s6, s4);
		  system(s6);

//		  fp_send = fopen(s4, "rb");
//		  while(1)
//		  {
//			  read_cnt_send = fread((void*) message, 1, BUFF_SIZE, fp_send);
//			  if(read_cnt_send < BUFF_SIZE)
//			  {
//				  write(client_sockfd, message, read_cnt_send);
//				  break;
//			  }
//			  write(client_sockfd, message, BUFF_SIZE);
//		  }
//		  fclose(fp_send);
		 
		  free(s1);
		  free(s2);
        close(client_sockfd);
    }
    return EXIT_SUCCESS;
}
