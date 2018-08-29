
#include <string>
#include <list>
#include <string.h>

#include "iw_util.h"

using namespace std;

#define MAX_ARGV_SIZE 32
#define MAX_IWCMD_SIZE 256

int exec_iw(const std::string iwcmd, 
		int (*user_handler)(struct nl_msg *, void *), void* user_data)
{
		int argc = 0;
		char *argv[MAX_ARGV_SIZE];
		char buffer[MAX_IWCMD_SIZE];		
		
		strcpy(buffer, iwcmd.c_str());		
		char *p = strtok(buffer, " ");
		while (p && argc < MAX_ARGV_SIZE-1) {
			argv[argc++] = p;
			p = strtok(0, " ");
		}
		argv[argc] = 0;

		return lib_main(argc, argv, user_handler, user_data);
}
