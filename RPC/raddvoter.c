#include "vote.h"


void
vote_prog_1(int dummy,char *host)
{
	CLIENT *clnt;

	int  *result_2;
	int  addvoter_1_arg;
	
	addvoter_1_arg = dummy;
	

#ifndef	DEBUG
	clnt = clnt_create (host, VOTE_PROG, VOTE_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */


	result_2 = addvoter_1(&addvoter_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	
	switch(*result_2)
	{
	case 1:
	printf("EXISTS\n");
	break;
	
	case 2:
	printf("OK\n");
	break;
	
	case 3:
	printf("ERROR\n");
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
    int dummy;

	if (argc < 3) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	if(strcmp(argv[1],"localhost")==0)
    host = "127.0.0.1";
    else
	host = argv[1];
	
	dummy = atoi(argv[2]);
	vote_prog_1 (dummy,host);
	
exit (0);
}
