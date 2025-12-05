#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/un.h>
#include <errno.h>
#define SOCKET_PATH "/tmp/mysocket"
int main(){
 
    int sock,newfd;
    struct sockaddr_un local,remote;
    socklen_t len;
    
    sock= socket(AF_UNIX,SOCK_STREAM,0);
    if(sock == -1){
        perror("socket");
        exit(1);
    }

    //yerel adres ayarlama
   local.sun_family=AF_UNIX;
   strcpy(local.sun_path,SOCKET_PATH);
   unlink(SOCKET_PATH);

   //BİND
   if(bind(sock,(struct sockaddr*)&local,sizeof(local))==-1){
    perror("bind");
    close(sock);
    exit(1);
   }

   //LISTEN
   if(listen(sock,5)==-1){
    perror("listen");
    close(sock);
    exit(1);
   }
  printf("server is listening....\n");


 //İSTEMCİ BAĞLANTILARINI KABUL ET.
 while(1){
  len=sizeof(remote);
  newfd=accept(sock,(struct sockaddr*)&remote,&len);
  if(newfd<0){
    perror("accept");
     if(errno == EINTR){
        continue;
     }else{
        break;
     }
  }
  printf("connected new client..\n");
  //burda istemci ile iletişim kurulacak örbeğin veri alıp gönderme
  close(newfd);//istemci socketini kapat.
 }
 close(sock);
 unlink(SOCKET_PATH);
 return 0;

}