#include "debug.h"
#include "monitor.h"
// Work of Ahmad

void fs_dump(int show_content)
{
	int i = 0;
    struct dirent *node = 0;
    while ( (node = readdir_fs(fs_root, i)) != 0)
    {
        monitor_write("[Entity] ");
        monitor_write(node->name);
        fs_node_t *fsnode = finddir_fs(fs_root, node->name);

        if ((fsnode->flags&0x7) == FS_DIRECTORY)
        {
            monitor_write("[Dir]\n");
        }
        else
        {
        	monitor_write("[File]\n");
            if(show_content)
            {
		        monitor_write("\n\t Contents: \"");
		        char buf[256];
		        u32int sz = read_fs(fsnode, 0, 256, buf);
		        int j;
		        for (j = 0; j < sz; j++)
		            putch(buf[j]);
		        
		        monitor_write("\n");
        	}
        }
        i++;
    }
    monitor_write("\n");
}
