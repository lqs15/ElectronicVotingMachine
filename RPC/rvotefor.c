#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vote.h"

char dummy[100]="";


void
vote_prog_1(char *host)
{
	CLIENT *clnt;

	int  *result_3;
	char * votefor_1_arg;
	
	strcpy(votefor_1_arg,dummy);
	

#ifndef	DEBUG
	clnt = clnt_create (host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */


	result_3 = votefor_1(&votefor_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	switch(*result_3)
	{
	case 1:
	printf("ALREADYVOTED\n");
	break;
	
	case 2:
	printf("EXISTS\n");
	break;
	
	case 3:
	printf("NEW\n");
	break;
	
	case 4:
	printf("NOTAVOTER\n");
	break;
	
	default:
	printf("ERROR!");
	}
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	char du[100]="";

	if (argc < 4) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	
	if(strcmp(argv[1],"localhost")==0)
    host = "127.0.0.1";
    else
	host = argv[1];
	
	sprintf(du,"%s ",argv[2]);
	strcpy(dummy,du);
	
	sprintf(du,"%s",argv[3]);
	strcat(dummy,du);
	
	vote_prog_1 (host);
exit (0);
}
