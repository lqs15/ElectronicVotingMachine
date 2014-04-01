#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vote.h"

char dummy[100]="";



void
vote_prog_1(char *host)
{
	CLIENT *clnt;

	int  *result_5;
	char * votecount_1_arg;
	
	strcpy(votecount_1_arg,dummy);

#ifndef	DEBUG
	clnt = clnt_create (host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_5 = votecount_1(&votecount_1_arg, clnt);
	if (result_5 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	int p1;
	p1 = *result_5;
	
	if(*result_5 == 0)
	printf("%s IS NOT A CANDIDATE\n",dummy);
	else
	printf("%s HAS %d VOTES\n",dummy,p1);
	
	
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
    char *host;
	char du[100]="";

	if (argc < 3) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	if(strcmp(argv[1],"localhost")==0)
    host = "127.0.0.1";
    else
	host = argv[1];
	
	sprintf(du,"%s",argv[2]);
	strcpy(dummy,du);
	
	vote_prog_1 (host);
exit (0);
}
