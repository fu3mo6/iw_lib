
#include <string>
#include "iw_util.h"
								
#define MAX_ARGV_SIZE 32
#define MAX_IWCMD_SIZE 256

int main(int argc, char *argv[]) {
	std::string test_cmd = "iw dev";
	exec_iw(test_cmd);
	return 0;
}