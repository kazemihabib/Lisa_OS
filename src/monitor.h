// monitor.h -- Defines the interface for monitor.h
//              From JamesM's kernel development tutorials.

#ifndef MONITOR_H
#define MONITOR_H

#include "common.h"

// Write a single character out to the screen.
void monitor_put(char c);
// Write a single character out to the screen support colour
void monitor_put_clr(char c, u8int backColour, u8int foreColour);

// Clear the screen to all black.
void monitor_clear();

// Output a null-terminated ASCII string to the monitor.
void monitor_write(char *c);

//change the background color
void chng_back_clr(u8int backColour);

//change the text color
void chng_fore_clr(u8int foreColour);
//move cursor forward
void move_forward(void);

//scroll up 
void scroll_up();

//scroll down
void scroll_down();

//reset scroll
void reset_scroll();

//change ws
void chng_ws();

//init page
void init_second_ws();
#endif // MONITOR_H
