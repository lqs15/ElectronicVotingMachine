#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vote.h"


void
vote_prog_1(char *host)
{
	CLIENT *clnt;
	char * *result_4;
	char *listcandidates_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_4 = listcandidates_1((void*)&listcandidates_1_arg, clnt);
	if (result_4 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	printf("%s\n",*result_4);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	
	if(strcmp(argv[1],"localhost")==0)
    host = "127.0.0.1";
    else
	host = argv[1];
	
	vote_prog_1 (host);
exit (0);
}
