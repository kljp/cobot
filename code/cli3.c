#include <stdio.h> 
  #include <stdlib.h> 
  #include <string.h> 
  #include <unistd.h> 
  #include <arpa/inet.h> 
  #include <fcntl.h> 
  #include <sys/types.h> 
  #include <sys/socket.h> 
   
  #define BUFSIZE 30 
   
  void error_handling(char *message); 
   
  int main(int argc, char **argv) 
  { 
      int fd; 
      int sd; 
       
      char buf[BUFSIZE];
      char cbuf[BUFSIZE]; 
      int len; 
      struct sockaddr_in serv_addr; 

		char file_path[BUFSIZE];

      if(argc!=3){ 
          printf("Usage : %s <IP> <port>\n", argv[0]); 
          exit(1); 
      } 
               
      /* 서버 접속을 위한 소켓 생성 */ 
      sd=socket(PF_INET, SOCK_STREAM, 0);    
      if(sd == -1) 
           error_handling("socket() error"); 
      
       memset(&serv_addr, 0, sizeof(serv_addr)); 
       serv_addr.sin_family=AF_INET; 
       serv_addr.sin_addr.s_addr=inet_addr(argv[1]); 
      serv_addr.sin_port=htons(atoi(argv[2])); 
 
     if( connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1 ) 
         error_handling("connect() error!"); 

	  len = read(sd, file_path, BUFSIZE);
	  fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	  if(fd == -1)
		  error_handling("File open error");

    /* 데이터를 전송 받아서 파일에 저장한다 */ 
     while( (len=read(sd, buf, BUFSIZE )) != 0 ) 
     { 
         write(fd, buf, len);  
     } 
          
     close(fd); 
     close(sd);

	  char str_temp[100];
	  strcpy(str_temp, "cat ");
	  strcat(str_temp, file_path);
	  system(str_temp);

     return 0; 
 } 
  
void error_handling(char *message) 
 { 
      fputs(message, stderr); 
      fputc('\n', stderr); 
      exit(1); 
 }
