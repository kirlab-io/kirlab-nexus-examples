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

#ifndef APPLICATION_H_
#define APPLICATION_H_

/*Buffers for shared data*/
extern double period;
extern double duty_cycle;

extern double v_in;
extern double v_out;
extern double i_in;
extern double i_out;



void application_init(void);

void application_background_loop(void);

void application_timer_isr(void);

#endif /* APPLICATION_H_ */
