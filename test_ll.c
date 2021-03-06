#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include "papi.h"

#define INDEX 100
#define NUM_EVENTS 2

static long long *do_work(int EventSet);

int main(int argc, char **argv) {
	int Events[NUM_EVENTS]={PAPI_FP_INS, PAPI_FP_OPS},
	int EventSet;
        long long values[NUM_EVENTS];
	
	/* Initialize the Library */
	retval = PAPI_library_init(PAPI_VER_CURRENT);
	/* Allocate space for the new eventset and do setup */
	retval = PAPI_create_eventset(&EventSet);
	/* Add Flops and total cycles to the eventset */
	retval = PAPI_add_events(&EventSet, Events, NUM_EVENTS);
	/* What we want to monitor*/
	values = do_work(EventSet);

 	printf("Total flpins:\t%lld\nTotal flpops:\t%lld\n",values[0], values[1]);
	printf("%s\tPASSED\n", __FILE__);
	PAPI_shutdown();
	exit(0);
	
}

static long long *do_work(EventSet){
  float matrixa[INDEX][INDEX], matrixb[INDEX][INDEX], mresult[INDEX][INDEX];
  int i,j,k;
  long long values[NUM_EVENTS];

  /* Initialize the Matrix arrays */
  for ( i=0; i<INDEX*INDEX; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1; }

  /* Start the counters */
  retval = PAPI_start(EventSet);

  /* Matrix-Matrix multiply */
  for (i=0;i<INDEX;i++)
   for(j=0;j<INDEX;j++)
    for(k=0;k<INDEX;k++)
      mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];

  /*Stop counters and store results in values */
  retval = PAPI_stop(EventSet,values);

  return values;


}

