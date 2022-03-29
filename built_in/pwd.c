#include "../minishell.h"
#include <limits.h>

void	current_dir(void)
{
	char cwd[PATH_MAX];

  if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
  	printf("Current working dir: %s\n", cwd);
  } 
	else 
	{
  	perror("getcwd() error");
  }
}