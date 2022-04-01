#include "../minishell.h"

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

void	loop_prompt(int ac, char **av, char **envp)
{
	char	*input;
	t_env	*liste;
	
	if (!ac || !av || !envp)
		return ;
	while (1)
	{
		input = readline("Minishell >");
		if (ft_strlen(input) > 0)
		{
			add_history(input);
			liste = get_env_chaine(envp);//fun teorique qui returne a partir de envp la liste chaine t_env
			lexer(input, liste);
			find_path(input, envp);
		}
	}
}
