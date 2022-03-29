#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <stdlib.h>

typedef struct s_the_env
{
	char	*name;
	char	*content;
	struct s_the_env	*next;
}	t_the_env;


void	loop_prompt(int ac, char **av, char **envp);
void	my_env(char **envp);
void	current_dir(void);

#endif