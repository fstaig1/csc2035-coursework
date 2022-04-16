/*
 * Replace the following string of 0s with your student number
 * 200799272
 */
#include <errno.h>
#include "mutex_peterson.h"


/* mutex.h contains the specification of functions in this file */

/* 
 * TODO: you must implement this function
 * Hints:
 * - see mutex_lockvar.c for how mutex_new is implemented there but remember
 *      that the underlying mutex type allocated in shared memory and 
 *      encapsulated by the IPC type will be different
 * - the shared object label should be mux_peters
 * - also see: mutex_peterson.h, mutex_lockvar.c and ipc.h
 */
mutex_t* mutex_new(proc_t* proc) {
	if (!proc) {
		errno = EINVAL;
		return NULL;
	}
    return ipc_new(proc, "mux_peters", sizeof(mutex_t));
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - see the section on the Peterson's busy waiting solution in 
 *     the CSC2035 lecture material on IPC
 * - process ids must be normalised to either a 0 or 1 for indexing 
 *      into the interested array (there is an arithmetic operator to do this)
 * - remember a mutex_t object is basically an ipc object and the specific
 *      implementation of a mutex (Peterson's in this case) in
 *      shared memory is at the addr field (see ipc.h)
 * - also see: mutex_lockvar.c
 */
void mutex_enter(mutex_t* mux) {
    if (!mux) {return;}
    
    mutex_peterson_t* mp = (mutex_peterson_t*) mux->addr;
    int mid = mux->proc->id;
    
    int oid = 1 - (mid % 2);
    
    mp->interested[mid % 2] = 1;
    mp->turn = mid;
    
    while (mp->turn == mid && mp->interested[oid] == 1) {;} 
}

/* 
 * TODO: you must implement this function.
 * Hints: see hints for mutex_enter
 */
void mutex_leave(mutex_t* mux) {
    if (!mux) {return;}
    mutex_peterson_t* mp = (mutex_peterson_t*) mux->addr;
	
    mp->interested[mux->proc->id % 2] = 0;
}

/* 
 * TODO: you must implement this function.
 * Hint:
 * - deallocate what you allocate in mutex_new
 */
void mutex_delete(mutex_t* mux) {
    if (mux) {ipc_delete(mux);}
}
