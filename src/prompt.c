#include "../minishell.h"
# define GREEN "\033[0;32m"
# define DEFAULT "\033[0m"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
}

void	execution(char **path, char **cmd_tab, char **envp)
{
	int	id;

	id = fork();
	if (id == 0)
		execve(*path, cmd_tab, envp);
	else
		free (*path);
	wait(&id);
	return ;
}

int	find_path(char *cmd, char **envp)
{
	char	**paths;
	char	**cmd_tab;
	char	*env;
	int		i;

	i = 0;
	env = getenv("PATH");
	paths = ft_split(env, ':');
	cmd_tab = ft_split(cmd, ' ');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd_tab[0]);
		if (access(paths[i], 0) == 0)
		{
			execution(&paths[i], cmd_tab, envp);
			return (0);
		}
		free (paths[i]);
		i++;
	}
	ft_putstr_fd("zsh: command not found: ", 2);
	ft_putendl_fd(cmd_tab[0], 2);
	free_tab (cmd_tab);
	return (1);
}

// int	search_type_token(*tk);

void	loop_prompt(int ac, char **av, char **envp)
{
	char		*input;
	t_env		*liste;
	t_token	*tk;
	
	if (!ac || !av || !envp)
		return ;
	liste = NULL;
 	create_env_list(&liste, envp);
	while (1)
	{
		write(1, GREEN, ft_strlen(GREEN));
		input = readline("Minishell > ");
		write(1, DEFAULT, ft_strlen(DEFAULT));
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			tk = NULL;
			lexer(input, liste, tk);// obtiene los token
			// search_type_token(*tk);
			// redirection
			// find_path(input, envp);
		}
	}
}
