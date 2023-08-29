/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _MOTD_H_RPCGEN
#define _MOTD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define MOTD_PROG 0x5f0000bc
#define MOTD_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define COUNT 1
extern  int * count_1(void *, CLIENT *);
extern  int * count_1_svc(void *, struct svc_req *);
#define GET 2
extern  char ** get_1(int *, CLIENT *);
extern  char ** get_1_svc(int *, struct svc_req *);
#define ADD 3
extern  void * add_1(char **, CLIENT *);
extern  void * add_1_svc(char **, struct svc_req *);
extern int motd_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define COUNT 1
extern  int * count_1();
extern  int * count_1_svc();
#define GET 2
extern  char ** get_1();
extern  char ** get_1_svc();
#define ADD 3
extern  void * add_1();
extern  void * add_1_svc();
extern int motd_prog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_MOTD_H_RPCGEN */