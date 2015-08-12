 /*
 * A simple example of the use of the high level PAPI_flops call.
 * PAPI_flops measures elapsed time, process time, floating point
 * instructions and MFLOP/s for code bracketted by calls to this routine.
 * For the following matrix multiply you should get 2*(INDEX^3) flpins 
 * on Intel Pentium processors.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <memory.h>
#include <malloc.h>
#include "papi.h"

#define INDEX 100

static void test_fail(char *file, int line, char *call, int retval);

int main(int argc, char **argv) {
  extern void dummy(void *);
  float matrixa[INDEX][INDEX], matrixb[INDEX][INDEX], mresult[INDEX][INDEX];
  float real_time_begin, real_time_end, proc_time_begin, proc_time_end, mflips_begin, mflips_end, mflops_begin, mflops_end, real_time, proc_time, mflips, mflops;
  long long flpins_begin, flpins_end, flpins, flpops_begin, flpops_end, flpops;
  int retval;
  int i,j,k;

  /* Initialize the Matrix arrays */
  for ( i=0; i<INDEX*INDEX; i++ ){
    mresult[0][i] = 0.0;
    matrixa[0][i] = matrixb[0][i] = rand()*(float)1.1; }

  /* Setup PAPI library and begin collecting data from the counters */
  if((retval=PAPI_flips( &real_time_begin, &proc_time_begin, &flpins_begin, &mflips_begin))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flips", retval);

  if((retval=PAPI_flops( &real_time_begin, &proc_time_begin, &flpops_begin, &mflops_begin))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flops", retval);

  /* Matrix-Matrix multiply */
  for (i=0;i<INDEX;i++)
   for(j=0;j<INDEX;j++)
    for(k=0;k<INDEX;k++)
      mresult[i][j]=mresult[i][j] + matrixa[i][k]*matrixb[k][j];

  /* Collect the data into the variables passed in */
  if((retval=PAPI_flips( &real_time_end, &proc_time_end, &flpins_end, &mflips_end))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flips", retval);
  if((retval=PAPI_flops( &real_time_end, &proc_time_end, &flpops_end, &mflops_end))<PAPI_OK)
    test_fail(__FILE__, __LINE__, "PAPI_flops", retval);

  real_time = real_time_end - real_time_begin;
  proc_time = proc_time_end - proc_time_begin;
  flpins = flpins_end - flpins_begin; 
  flpops = flpops_end - flpops_begin;
  mflips = mflips_end - mflips_begin; 
  mflops = mflops_end - mflops_begin;

  printf("Real_time:\t%f\nProc_time:\t%f\nTotal flpins:\t%lld\nTotal flpops:\t%lld\nMFLIPS:\t\t%f\nMFLOPS:\t\t%f\n",
  real_time, proc_time, flpins, flpops, mflips, mflops);
  printf("%s\tPASSED\n", __FILE__);
  PAPI_shutdown();
  exit(0);
}

static void test_fail(char *file, int line, char *call, int retval){
    printf("%s\tFAILED\nLine # %d\n", file, line);
    if ( retval == PAPI_ESYS ) {
        char buf[128];
        memset( buf, '\0', sizeof(buf) );
        sprintf(buf, "System error in %s:", call );
        perror(buf);
    }
    else if ( retval > 0 ) {
        printf("Error calculating: %s\n", call );
    }
    else {
        printf("Error in %s: %s\n", call, PAPI_strerror(retval) );
    }
    printf("\n");
    exit(1);
}
