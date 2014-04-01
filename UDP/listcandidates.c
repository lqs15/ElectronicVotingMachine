#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
 
 
int main(int argc, char *argv[])
{
  if (argc != 3)
  {
   printf("Invalid command line argument, Needs 2 arguments ServerIP and Port Address\n");
  }
 
  int sock;
  struct sockaddr_in sa;
  int bytes_sent;
  char buffer[1024]="";
  char str[50];

  int i = 0;
  ssize_t recsize;
  socklen_t fromlen;
  
  int option = 4;
  int reset = 0;
  int voterid = 0;
  char name[50] = "0";
  int list_candi = 1;
  char vote_count[50] = "0";
  int tail = 0;
  
  sprintf(str, "%d ", option);
  strcat(buffer,str);
  
  sprintf(str, "%d ", reset);
  strcat(buffer,str);
  
  sprintf(str, "%d ", voterid);
  strcat(buffer,str);
  
  strcat(buffer,name);
  
  sprintf(str, " %d ", list_candi);
  strcat(buffer,str);
  
  strcat(buffer,vote_count);
  
  sprintf(str, " %d ", tail);
  strcat(buffer,str);
 
  //create an internet, datagram, socket using UDP
  sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sock) /* if socket failed to initialize, exit */
    {
      printf("Error Creating Socket");
      exit(EXIT_FAILURE);
    }
 
  //Zero out socket address
  memset(&sa, 0, sizeof sa);
 
  //The address is ipv4
  sa.sin_family = AF_INET;
 
   //ip_v4 adresses is a uint32_t, convert a string representation of the octets to the appropriate value
  if(strcmp(argv[1],"localhost")==0)
  sa.sin_addr.s_addr = inet_addr("127.0.0.1");
  else
  sa.sin_addr.s_addr = inet_addr(argv[1]);
  
 
  //sockets are unsigned shorts, htons(x) ensures x is in network byte order, set the port to 7654
  sa.sin_port = htons(atoi(argv[2]));
 
  //sendto(int socket, char data, int dataLength, flags, destinationAddress, int destinationStructureLength)
  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
  if (bytes_sent < 0) {
    printf("Error sending packet: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  
   while(i<1)
  {
  recsize = recvfrom(sock, (void *)buffer, sizeof(buffer), 0, (struct sockaddr *)&sa, &fromlen);
    if (recsize < 0) 
	{
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  printf("%.*s\n", (int)recsize, buffer);
  i++;
  }
 
  close(sock); /* close the socket */
  return 0;
  
}
