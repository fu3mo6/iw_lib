#ifndef _IW_UTIL_H_
#define _IW_UTIL_H_

#include <string>
#include <list>
#include <string.h>

extern "C" {

#include "iw_src/iw.h"
extern int lib_main(int argc, char **argv,
								int (*user_handler)(struct nl_msg *, void *),
								void *user_data);	

}

/* Function: exec_iw
 * Change "cmd" to argc and argv
 * execute lib_main using input user_handler and user_data
 */
int exec_iw(const std::string iwcmd, 
		int (*user_handler)(struct nl_msg *, void *)=NULL, void* user_data=NULL);

#endif /* _IW_UTIL_H_ */


