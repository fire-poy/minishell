#include "../minishell.h"

int	main(int argc, char **argv)
{   
		// printing current working directory
		current_dir();
		// the regular shell does show all available directory ???
		chdir(argv[1]);
		// printing current working directory
		current_dir();
		// after chdir is executed
	//}
}
