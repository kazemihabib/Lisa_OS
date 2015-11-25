// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

//used in the delay function
int wait_loop0 = 500;  //10000
int wait_loop1 = 800;	//6000

#include "timer.h"
#include "isr.h"
#include "monitor.h"

u32int tick = 0;




// for platform without timer, if it has a timer refer to vendor documentation and use it instead.
void delay( int seconds )
{   // this function needs to be finetuned for the specific processor
    int i, j, k;
    for(i = 0; i < seconds; i++)
    {
        for(j = 0; j < wait_loop0; j++)
        {
            for(k = 0; k < wait_loop1; k++)
            {   // waste function, volatile makes sure it is not being optimized out by compiler
               // int volatile t = 120 * j * i + k;
                //t = t + 5;
		
            }
        }
    }
}



static void timer_callback(registers_t regs)
{
    tick++;
    //monitor_write("Tick: ");
    //monitor_write_dec(tick);
    //monitor_write("\n");
}

void init_timer(u32int frequency)
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ0, &timer_callback);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}
