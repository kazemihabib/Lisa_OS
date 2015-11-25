// main.c -- Defines the C-code kernel entry point, calls initialisation routines.

#include "monitor.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "keyboard.h"
#include "startmain.h"
#include "multiboot.h"
#include "fs.h"

int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();
    
    asm volatile("int $0x3");
    asm volatile("int $0x4");

    asm volatile("sti");
    init_timer(50);
  	// Find the location of our initial ramdisk.
  	u32int initrd_location = *((u32int*)mboot_ptr->mods_addr);
    // Initialise the initial ramdisk, and set it as the filesystem root.
    fs_root = initialise_initrd(initrd_location);

  	
    // call real main :D
    start_main();

    return 0;
}
