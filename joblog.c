/*
 * Replace the following string of 0s with your student number
 * 200799272
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "joblog.h"

// DO NOT EDIT the following definitions of log string constant values */
const char* JOBLOG_PATH = "./out";
const char* JOBLOG_NAME_FMT = "%s/%s%07d.txt";
const char* JOBLOG_ENTRY_FMT = "pid:%07d,id:%05d,label:%s\n";
  // "pid:0000005,id:00010,label:newjob************************\n" 59chars (\n is 1 char)

/* 
 * DO NOT EDIT the new_log_name function. It is a private helper 
 * function provided for you to create a log name from a process 
 * descriptor for use when reading, writing and deleting a log file.
 * 
 * You must work out what the function does in order to use it properly
 * and to clean up after use.
 *
 * See JOBLOG_NAME_FMT above for the form of log names.
 */
static char* new_log_name(proc_t* proc) {
    if (!proc)
        return NULL;

    char* log_name;
            
    asprintf(&log_name, JOBLOG_NAME_FMT, JOBLOG_PATH, proc->type_label,
        proc->id);

    return log_name;
}

/* 
 * DO NOT EDIT the joblog_init function.
 */
int joblog_init(proc_t* proc) {
    if (!proc) {
        errno = EINVAL;
        return -1;
    }
        
    int r = 0;
    if (proc->is_init) {
        struct stat sb;
    
        if (stat(JOBLOG_PATH, &sb) != 0) {
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }  else if (!S_ISDIR(sb.st_mode)) {
            unlink(JOBLOG_PATH);
            errno = 0;
            r = mkdir(JOBLOG_PATH, 0777);
        }
    }

    joblog_delete(proc);    // in case log exists for proc
    
    return r;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - you have to go to the beginning of the line represented
 *      by entry_num to read the required entry
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in joblog.h for when to do dynamic allocation
 */
char* joblog_read_entry(proc_t* proc, int entry_num, char* buf) {
    int init_errno = errno;
        
    char* result = NULL;
    
    if (proc && entry_num >= 0) {
        char* fname = new_log_name(proc);
        if (fname) {
            FILE* f = fopen(fname, "r");
        
            if (f) {
            
                if (!buf) {buf = (char*) malloc(JOBLOG_ENTRY_SIZE);}
                
                if (fseek(f, entry_num * (JOBLOG_ENTRY_SIZE) , SEEK_SET) == 0) {

                    char* r = fgets(buf, JOBLOG_ENTRY_SIZE, f); 
                    
                    if (r != NULL) {buf[JOBLOG_ENTRY_SIZE - 1] = '\0';} 
                    else {buf = NULL;}
                    
                    result = buf;
                }
            fclose(f);
            free(fname);
            }
        }
        
    } 
    errno = init_errno;
    return result;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - look at the documentation of the format of a log entry in joblog.h
 * - remember new entries are appended to a log file
 */
void joblog_write_entry(proc_t* proc, job_t* job) {

    if (job && proc) {
        char* log = new_log_name(proc);
        FILE* f = fopen(log, "a");

        fprintf(f, JOBLOG_ENTRY_FMT, job->pid, job->id, job->label);
    
        fclose(f);
    }
    return;
}

/* 
 * TODO: you must implement this function.
 */
void joblog_delete(proc_t* proc) {
    (void) remove(new_log_name(proc));
    return;
}
