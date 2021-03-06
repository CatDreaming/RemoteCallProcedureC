#include<stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include<rpc/rpc.h>/* standard RPC include file */
#include"date.h"/* this file is generated by rpcgen */

#define MAX_LEN 100
long get_response(void);

long get_response(){
    long choice;
    printf("===========================================\n");
    printf("                   Menu: \n");
    printf("-------------------------------------------\n");
    printf("                1. Date\n");
    printf("                2. Time\n");
    printf("                3. Both\n");
    printf("                4. CPU Usage\n");
    printf("                5. Memory Usage\n");
    printf("                6. Load Averages\n");
    printf("                7. Quit\n");
    printf("-------------------------------------------\n");
    printf("               Choice (1-7):");
    scanf("%ld",&choice);
    printf("===========================================\n");
    return(choice);
}

main(int argc, char **argv){
    CLIENT  *cl;        /* RPC handle */
    char    *server;
    char    **sresult;  /* return value from date_1()      */
    char    **sresult2; /* return value from cpu_usage()     */
    char    **sresult3; /* return value from memory_usage()  */
    char    **sresult4; /* return value from load_proc_per_minute()  */
    char    s[MAX_LEN];    /* character array to hold output */
    long    response;  /* user response                           */
    long    *lresult;    /* pointer to user response          */
    if (argc != 2) {
	fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }
    server = argv[1];
    lresult = (&response);    /*     * Create the client "handle."     */
    if ( (cl = clnt_create(server, DATE_PROG, DATE_VERS, "udp")) == NULL) {
	clnt_pcreateerror(server);
        exit(2);
    }
    response = get_response();
    while(response != 7) {
	if(response<4){
	    if ((sresult = date_1(lresult, cl)) == NULL) {
                clnt_perror(cl, server);
                exit(3);
	    } else {
		printf("  %s\n", *sresult);
	    }
	} else if(response==4){
	    if ((sresult2 = cpu_usage_1(lresult, cl)) == NULL){
		clnt_perror(cl, server);
		exit(3);
	    } else {
		printf("  %s\n", *sresult2);
	    }
	} else if(response==5){
	    if ((sresult3 = memory_usage_1(lresult, cl)) == NULL){
		clnt_perror(cl, server);
		exit(3);
	    } else {
		printf("  %s\n", *sresult3);
	    }
	} else if(response==6){
	    if ((sresult4 = load_proc_per_minute_1(lresult, cl)) == NULL){
		clnt_perror(cl, server);
		exit(3);
	    } else {
		printf("  %s\n", *sresult4);
	    }
	}
	response = get_response();
    }
    clnt_destroy(cl);/* done with the handle */
    exit(0);
}
