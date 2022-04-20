#include "../minishell.h"

// on met stdin au fichier d'entre si besoin
// on fork 1 fois pour chaque commande a executter
//pour exec la premier commande et change stdout si besoin
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

// env = getenv("PATH");
int	find_path(char *cmd, char **envp, t_env *liste)
{
	char	**paths;
	char	**cmd_tab;
	char	*env;
	int		i;

	i = 0;
	env = chercher_env(liste, "PATH");
	paths = ft_split(env, ':');
	cmd_tab = ft_split(cmd, ' ');
	//cmd[0] = ls
	//cmd[1] = -a
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

/*
static bool	is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", NULL};

	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd))
			return (true);
	}
	return (false);
}

static void	exec_built_in(char **built_in)
{
	if (!strcmp(built_in[0], "pwd"))
		built_in_pwd();
	else if (!strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
}

int	is_builtin_command( t_cmd *cmd)
{
	if (str_compare(cmd->name, "cd") == 0)
		return (1);
	else if (str_compare(cmd->name, "echo") == 0)
		return (1);
	else if (str_compare(cmd->name, "env") == 0)
		return (1);
	else if (str_compare(cmd->name, "exit") == 0)
		return (1);
	else if (str_compare(cmd->name, "export") == 0)
		return (1);
	else if (str_compare(cmd->name, "pwd") == 0)
		return (1);
	else if (str_compare(cmd->name, "unset") == 0)
		return (1);
	else
		return (0);
}
////////


// @brief execute toutes les commandes se trouvant dans shell->cmds
// @param shell 
void	exec_commands(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	prepare_here_doc_cmd(shell);
	cmd = shell->cmds;
	if (shell->num_cmds == 1)
		exec_single_command(shell, cmd);
	else
	{
		create_pids(shell);
		create_pipes(shell);
		while (cmd)
		{
			exec_child_command(shell, cmd, ++i);
			cmd = cmd->next;
		}
		close_pipes(shell);
		wait_pids(shell);
	}
	save_exit_status(shell);
}

int	exec_single_command(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	if (is_builtin_command(cmd))
		exec_builtin_command(shell, cmd);
	else if (is_invalid_command(shell, cmd) == 0)
	{
		pid = fork();
		if (pid == -1)
			perror("Error: fork() failed\n");
		else if (pid == 0)
		{
			handle_redirect_file(shell, cmd);
			if (execve(cmd->name, cmd->args, shell->envs))
				show_command_error(shell, cmd->name, strerror(errno), errno);
			exit(shell->exit_status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
	return (0);
}

void	exec_child_command(t_shell *shell, t_cmd *cmd, int num)
{
	shell->pids[num] = fork();
	if (shell->pids[num] < 0)
		perror("Error: fork() failed");
	else if (shell->pids[num] == 0)
	{
		redirect_input(shell, cmd, num);
		redirect_output(shell, cmd, num);
		close_pipes(shell);
		if (is_builtin_command(cmd))
			exec_builtin_command(shell, cmd);
		else if (is_invalid_command(shell, cmd) == 0)
		{
			if (execve(cmd->name, cmd->args, shell->envs))
				show_command_error(shell, cmd->name, strerror(errno), errno);
		}
		exit(shell->exit_status);
	}
}
*/