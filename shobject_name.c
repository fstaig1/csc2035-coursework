/*
 * Replace the following string of 0s with your student number
 * 200799272
 */

#include <stdlib.h>
#include <stdio.h>
#include "sim_config.h"
#include "shobject_name.h"

const char* SHOBJ_NAME_FORMAT = "/csc2035.%.9s.%.12s";

/* 
 * TODO you must implement this function.
 *
 * Hints:
 * - from its specification in shobject_name.h this function may seem 
 *      complicated, in fact almost everything will be covered in C 
 *      programming module materials
 * - there is a library function for getting the current user from the 
 *      environment (use "anon" if the function returns NULL)
 */
char* shobject_name(char* name_buf, const char* label) {

    char* result;
    char* user = getenv("USER");

    if (!user) {user = "anon";}

    if (!label || !label[0]) {label = "none";}

    if(name_buf) {
        int r = snprintf(name_buf,  // buffer
                        MAX_NAME_SIZE,  // size of buffer
                        SHOBJ_NAME_FORMAT,  // format string
                        user,  // user
                        label  // application label
                        );
        result = r < 0? NULL : name_buf;
    } 
    else{
        (void) asprintf(&result,  // address of buffer
                        SHOBJ_NAME_FORMAT,
                        user,
                        label);
        free(name_buf);
    }
    return result;
}
