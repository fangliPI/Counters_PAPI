 #include "papi.h”
#define NUM_EVENTS 2
int Events[NUM_EVENTS]={PAPI_FP_OPS,PAPI_TOT_CYC},
int EventSet;
long long values[NUM_EVENTS];
/* Initialize the Library */
retval =
PAPI_library_init
(PAPI_VER_CURRENT);
/* Allocate space for the new eventset and do setup */
retval =
PAPI_create_eventset
(&EventSet);
/* Add Flops and total cycles to the eventset */
retval =
PAPI_add_events
(&EventSet,Events,NUM_EVENTS);
/* Start the counters */
retval =
PAPI_start
(EventSet);
do_work();
/* What we want to monitor*/
/*Stop counters and store results in values */
retval =
PAPI_stop
(EventSet,values);
