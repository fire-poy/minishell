#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <stdlib.h>

typedef struct s_tokens t_tokens;

struct s_tokens
{
	char	*token;
	char	**tab_cmd;
	char	*env;
	int		token;
}
// 0 == cmd
// 1 == env
// 2 == 
void	loop_prompt(int ac, char **av, char **envp);
void	my_env(char **envp);
void	current_dir(void);

#endif