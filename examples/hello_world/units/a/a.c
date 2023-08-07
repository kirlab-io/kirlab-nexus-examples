/*
=========================================================================
* Copyright (C) 2023 Kirlab
* All rights reserved.
*
* This file is part of KirLab Nexus.
*
* This file is distributed under the terms of KirLab Nexus license.
* Please see the EULA.txt file for the full license text.
=========================================================================
*/
#include "nexus.h"
#include <stdio.h>

#define PROCESS_SLOT (0)

double t;
double period = 10e-6;

double a_signal_0 = 1000.0;
double a_signal_1 = 2000.0;
double b_signal_0;
double b_signal_1;

#ifdef __cplusplus
extern "C" {
#endif
void nexus_write_shared_memory(void){
	nexus_pt->a.signal_0 = a_signal_0;
	nexus_pt->a.signal_1 = a_signal_1;
}

void nexus_read_shared_memory(int argc, char *argv[]){
	b_signal_0 = nexus_pt->b.signal_0;
	b_signal_1 = nexus_pt->b.signal_1;
}
#ifdef __cplusplus
}
#endif

int main(int argc, char *argv[]) {
    
    int result = nexus_init(PROCESS_SLOT,
                            nexus_shared_id); 
    if(result != 0) return result;
    
    printf("Read from other process: \nb.signal_0: %f\nb.signal_1:  %f\n", b_signal_0, b_signal_1);
    printf("Local time: %f\n", t);
    printf("\n\n");
    
    while(1){
        t = t+period;
        nexus_sync(t);
        
        printf("Read from other process: \nb.signal_0: %f\nb.signal_1:  %f\n", b_signal_0, b_signal_1);
        printf("Local time: %f\n", t);
        printf("\n\n");
        
        a_signal_0 += 1.0;
        a_signal_1 += 1.0;
    }
    
    return 0;
}