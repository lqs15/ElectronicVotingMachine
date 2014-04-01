#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h> /* for close() for socket */ 
#include <stdlib.h>

#define NO_OF_CANDIDATES 10
#define NO_OF_VOTERS 100

struct candidatelist
{
  char name[50];
  int vote;
};

int getwords(char *line, char *words[], int maxwords)
{
char *p = line;
int nwords = 0;

while(1)
	{
	while(isspace(*p))
		p++;

	if(*p == '\0')
		return nwords;

	words[nwords++] = p;

	while(!isspace(*p) && *p != '\0')
		p++;

	if(*p == '\0')
		return nwords;

	*p++ = '\0';

	if(nwords >= maxwords)
		return nwords;
	}
}

 
int main(void)
{
  int vid[NO_OF_VOTERS];
  int voted[NO_OF_VOTERS];
  struct candidatelist candidate[NO_OF_CANDIDATES];
  char *words[10];
  int nwords;
  int i,j,k,flag;
  
  int option;
  int reset;
  int voterid;
  char name[50];
  int list_candi;
  char vote_count[50];
  int tail;
  int vid_count;
  int voted_count;
  int c_count;
  
  vid_count = 0;
  voted_count = 0;
  c_count = 0;
  flag = 0;
  
  int sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in sa; 
  int bytes_sent;
  char buffer[1024];
  char str[1024];
  char str1[1024];
  ssize_t recsize;
  socklen_t fromlen;
 
  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  sa.sin_port = htons(7654);
  fromlen = sizeof(sa);
 
  if (-1 == bind(sock,(struct sockaddr *)&sa, sizeof(sa)))
  {
    perror("error bind failed");
    close(sock);
    exit(EXIT_FAILURE);
  }
 
  for (;;) 
  {
    printf ("\n RECEIVING... PORT NUMBER 7654\n");
    recsize = recvfrom(sock, (void *)buffer, sizeof(buffer), 0, (struct sockaddr *)&sa, &fromlen);
    if (recsize < 0) {
      fprintf(stderr, "%s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
    //printf("recsize: %d\n ", recsize);
    //sleep(1);
    printf("MESSAGE CONTENTS: %.*s\n", (int)recsize, buffer);
	
	nwords = getwords(buffer, words, 10);
	
	//for(i = 0; i < nwords; i++)
	//printf("%s\n", words[i]);
	
	
	
	option = atoi(words[0]);
    reset = atoi(words[1]);
    voterid = atoi(words[2]);
    
    strcpy(name,words[3]);
    list_candi = atoi(words[4]);
    
    strcpy(vote_count,words[5]);
	
	tail = atoi(words[6]);
	
	
	
	memset(words,0,sizeof(words));
	
	
	
	//printf("%d\t%d\t%d\t%s\t%d\t%s\t%d\n",option,reset,voterid,name,list_candi,vote_count,tail);
	
	switch(option)
	{
	//zeroize the system
	case 1:
	
	memset(candidate,0,sizeof(candidate));
	memset(vid,0,sizeof(vid));
	memset(voted,0,sizeof(voted));
	vid_count = 0;
	voted_count = 0;
	c_count = 0;
	
	sprintf(buffer, "INITIAL STATE");
	bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
    if (bytes_sent < 0) 
	{
    printf("Error sending packet: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
    }
	
	break;
	
	//Add voter ID
	case 2:
	
	for(j=0;j<vid_count;j++)
	{
	
	//printf("%d\t",vid[j]);
	
	  if(voterid == vid[j])  //Exists condition
	  {
	   sprintf(buffer,"EXISTS");
	   
	   bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
       if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
		
	   flag = 1;
	  }
	}
	
	// Valid voter if voterid is in between 1 to 100
	if(flag!=1)
	{	
	  if(voterid>0 && voterid<=100)
	  {
	  vid[vid_count]=voterid;
	  vid_count++;
	  
      sprintf(buffer,"OK");
	  
	  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
      if (bytes_sent < 0) 
	   {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
       }
	   
	  }
	  else
	  {
	  sprintf(buffer,"ERROR");	
	  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
      if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	  }
	}
		
		
	flag = 0;
	
	break;
	
	//Votefor
	case 3:
	
	for(j=0;j<vid_count;j++)
	{
	  if(voterid == vid[j])  //Exists condition valid voter
	  {
	   flag = 1;
	  }
	}
	
	if(flag==1)  // Valid voter
	{
	  for(j=0;j<voted_count;j++)
	  {
	   if(voterid == voted[j])  // Already voted
	   {
	   sprintf(buffer,"ALREADYVOTED");
	   
	   bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
       if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	   
	   flag = 0;
	   }
	  }
	  
	  if(flag==1)  // Not voted yet
	  {
	    for(j=0;j<c_count;j++)
		{
		
		//printf("%s\n",candidate[j].name);
		//printf("%d\n",candidate[j].vote);
		
		  if(strcmp(candidate[j].name,name)==0)
		  {
		  sprintf(buffer,"EXISTS");
		  
		  bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
          if (bytes_sent < 0) 
	      {
            printf("Error sending packet: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
          }
		  
		  candidate[j].vote = candidate[j].vote + 1;
		  voted[voted_count]=voterid;
		  voted_count++;
		  flag = 0;
		  }
		}
	  
	    if(flag==1)  // Candidate does not exist
	    {
		 sprintf(buffer,"NEW");
		 
		 bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
         if (bytes_sent < 0) 
	      {
            printf("Error sending packet: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
          }
		 
		 strcpy(candidate[c_count].name,name);
		 candidate[c_count].vote = 0;
		 candidate[c_count].vote = candidate[c_count].vote + 1;
		 voted[voted_count]=voterid;
		 voted_count++;
		 c_count++;
		}
	  }
	}
	else
	{
	sprintf(buffer, "NOTAVOTER");
	
	bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
    if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	}
	
	flag = 0;	
	break;
	
	//List of candidates
	case 4:
	strcpy(buffer,str1);
	for(j=0;j<c_count;j++)
	{
	sprintf(str,"%s\t",candidate[j].name);
	strcat(buffer,str);
	
	flag = 1;
	}
	
	if(flag!=1)
	{
	sprintf(buffer,"NO CANDIDATES");
	}
	
    bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
      if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	
	flag = 0;
	
	break;
	
	//Display no. of votes of a candidate
	case 5:
	
	for(j=0;j<c_count;j++)
	{
	if(strcmp(candidate[j].name,vote_count)==0)
	{
	sprintf(buffer,"%s HAS %d VOTES",candidate[j].name,candidate[j].vote);
	bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
      if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	flag = 1;
	}
	}
	
	if(flag!=1)
	{
	sprintf(buffer,"%s IS NOT A CANDIDATE",vote_count);
	bytes_sent = sendto(sock, buffer, strlen(buffer), 0,(struct sockaddr*)&sa, sizeof sa);
      if (bytes_sent < 0) 
	    {
       printf("Error sending packet: %s\n", strerror(errno));
       exit(EXIT_FAILURE);
        }
	
	}
	
	flag = 0;
	break;
	default:
	printf("ERROR!");
	}
	
  }
}