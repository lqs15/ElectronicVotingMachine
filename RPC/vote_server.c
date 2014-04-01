#include "vote.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  int vid[NO_OF_VOTERS];
  int voted[NO_OF_VOTERS];
  struct candidatelist candidate[NO_OF_CANDIDATES];
  char *words[10];
  int nwords;
  int i,j,k;
  
  int vid_count = 0;
  int voted_count = 0;
  int c_count = 0;
  int flag = 0;

int *
zeroize_1_svc(void *argp, struct svc_req *rqstp)
{
	static int  result;

	memset(candidate,0,sizeof(candidate));
	memset(vid,0,sizeof(vid));
	memset(voted,0,sizeof(voted));
	vid_count = 0;
	voted_count = 0;
	c_count = 0;
    result = 1;

	return &result;
}

int *
addvoter_1_svc(int *argp, struct svc_req *rqstp)
{
    static int  result;
	
	int voterid;
	voterid = *argp;
	

	for(j=0;j<vid_count;j++)
	{
	  if(voterid == vid[j])  //Exists condition
	  {
	   result = 1;
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
	  
      result = 2;
	   
	  }
	  else
	  {
	  result = 3;
	  }
	}
	
	flag = 0;

	return &result;
}

int *
votefor_1_svc(char **argp, struct svc_req *rqstp)
{
	char sent[100];
	char name[100];
	int nwords;
	static int result;
	
   sprintf(sent,"%s",*argp);
   
   nwords = getwords(sent,words,10);
   
   //for(i = 0; i < nwords; i++)
   //printf("%s\n", words[i]);
   
   strcpy(name,words[0]);
   int voterid;
   voterid = atoi(words[1]);
   
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
	   result = 1;	   
	   flag = 0;
	   }
	  }
	  
	  if(flag==1)  // Not voted yet
	  {
	    for(j=0;j<c_count;j++)
		{
		
		  if(strcmp(candidate[j].name,name)==0)
		  {
		  result = 2;		  
		  candidate[j].vote = candidate[j].vote + 1;
		  voted[voted_count]=voterid;
		  voted_count++;
		  flag = 0;
		  }
		}
	  
	    if(flag==1)  // Candidate does not exist
	    {
		 result = 3;		 
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
	result = 4;
	}
	
	flag = 0;

	return &result;
}

char **
listcandidates_1_svc(void *argp, struct svc_req *rqstp)
{
    
	static char * result;
	
	result = (char*)malloc(100*sizeof(char));

	char buffer[1024]="";
    char str[1024];

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
	
	
	strcpy(result,buffer);
	flag = 0;
	
	

	return (char **)&result;
}

int *
votecount_1_svc(char **argp, struct svc_req *rqstp)
{
	static int result;
	
	//result = (int*)malloc(sizeof(int));

	char vote_count[100];
	
	sprintf(vote_count,"%s",*argp);

	for(j=0;j<c_count;j++)
	{
	if(strcmp(candidate[j].name,vote_count)==0)
	{
	result = candidate[j].vote;
	flag = 1;
	}
	}
	
	if(flag!=1)
	{
	result = 0;
	}
	
	flag = 0;

	return &result;
}
