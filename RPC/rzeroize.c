#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vote.h"


void
vote_prog_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char *zeroize_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = zeroize_1((void*)&zeroize_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	
	if (*result_1 == 1)
	printf("INITIAL STATE\n");
	else
	printf("ERROR STATE\n");
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
