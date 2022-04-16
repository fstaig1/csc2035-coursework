/*
 * Replace the following string of 0s with your student number
 * 200799272
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new function.
 */
job_t* job_new(pid_t pid, unsigned int id, const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, label);
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look for other functions in this file that you can use to implement 
 *      this function
 */
job_t* job_copy(job_t* dst, job_t* src) {
	if (!src) {return NULL;}
	
	if (!dst) {dst = (job_t*) malloc(sizeof(job_t));}
	
	if (job_is_equal(src, dst)) {return dst;}
	
	job_set(dst, src->pid, src->id, src->label);
    /*
    dst->pid = src->pid;
    dst->id = src->id;
    strncpy(dst->label, src->label, MAX_NAME_SIZE);
    */
    
    return dst;
}

/* 
 * TODO: you must complete the implementation of this function, which 
 * currently only sets the pid and id fields of a job to zero.
 */
void job_init(job_t* job) {
	if (job) {
		job->pid = 0;
		job->id = 0;
		memset(job->label, 0, MAX_NAME_SIZE);
		
	}
}

/* 
 * TODO: you must complete the implementation of this function, which 
 * currently only compares the pid and id fields of a job.
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    if (j1 && j2) {
        int r = strncmp(j1->label, j2->label, MAX_NAME_SIZE);
        return j1->pid == j2->pid && j1->id == j2->id && r == 0;
    }
    else if (!j1 && !j2) {return true;}
    
    return false;
    
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, const char* label) {
    if (!job) {return NULL;}
    else {
        if (label == NULL) {label = "";}
        job->pid = pid;
        job->id = id;
        
        snprintf(job->label, MAX_NAME_SIZE, "%s%s", label, "*******************************");
        
        job->label[MAX_NAME_SIZE - 1] = '\0';
        
    }
    return job;
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
    free(job);
    return;
}
