#include "../minishell.h"

int	main(int argc, char **argv)
{   
	//printf("Hello\n");
	// printing current working directory
	current_dir();
	// the regular shell does show all available directory ???
	if (chdir(argv[1]) == -1)
		//perror(argv[1]);
		printf("cd: no such file or directory: %s\n", argv[1]);
	// printing current working directory
	current_dir();
	// after chdir is executed
	//}
	return (0);
}
