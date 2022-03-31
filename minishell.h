#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
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
	//int		token;
};
// 0 == cmd
// 1 == env
// 2 == 

// chained list to extract env
typedef struct s_env t_env;

struct s_env
{
	char	*initial_env;
	char	*name;
	char	*content;
	t_env	*next;
};

void	loop_prompt(int ac, char **av, char **envp);
void	my_env(char **envp);
void	current_dir(void);
void	create_node(t_env **head, char *data);
void	printlist(t_env *node);
void	create_env_list(t_env **head, char **envp);
t_env	*ft_search_in_list(t_env **head, char *name);
t_env	*ft_create_node(char *name, char *value);
void	ft_add_to_list(t_env **head, t_env *newnode);
int		ft_delete_first_node(t_env **head, t_env *temp, char *name);
void	ft_delete_from_list(t_env **head, char *name);
int		ft_count_list(t_env **head);
char	*ft_get_line(char *line);
char	*ft_get_name(char *line);

#endif