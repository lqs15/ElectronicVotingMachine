/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _VOTE_H_RPCGEN
#define _VOTE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define VOTE_PROG 0x21111111
#define VOTE_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define ZEROIZE 1
extern  int * zeroize_1(void *, CLIENT *);
extern  int * zeroize_1_svc(void *, struct svc_req *);
#define ADDVOTER 2
extern  int * addvoter_1(int *, CLIENT *);
extern  int * addvoter_1_svc(int *, struct svc_req *);
#define VOTEFOR 3
extern  int * votefor_1(char **, CLIENT *);
extern  int * votefor_1_svc(char **, struct svc_req *);
#define LISTCANDIDATES 4
extern  char ** listcandidates_1(void *, CLIENT *);
extern  char ** listcandidates_1_svc(void *, struct svc_req *);
#define VOTECOUNT 5
extern  int * votecount_1(char **, CLIENT *);
extern  int * votecount_1_svc(char **, struct svc_req *);
extern int vote_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ZEROIZE 1
extern  int * zeroize_1();
extern  int * zeroize_1_svc();
#define ADDVOTER 2
extern  int * addvoter_1();
extern  int * addvoter_1_svc();
#define VOTEFOR 3
extern  int * votefor_1();
extern  int * votefor_1_svc();
#define LISTCANDIDATES 4
extern  char ** listcandidates_1();
extern  char ** listcandidates_1_svc();
#define VOTECOUNT 5
extern  int * votecount_1();
extern  int * votecount_1_svc();
extern int vote_prog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_VOTE_H_RPCGEN */
