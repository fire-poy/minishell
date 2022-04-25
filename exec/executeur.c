#include "../minishell.h"

//compter   INPUT
			// OUTPUT
			// CMD
			// PIPE
// dernier input va etre celui de la redirection entrée
// dernier output va etre celui de la redirection sortie avant un pipe
// si il y a plusieurs inputs on ouvre en mode read et ferme jusq'au dernier
// si il y a plusieurs inputs on ouvre en mode write et ferme

// on met stdin au fichier d'entre si besoin
// on fork 1 fois pour chaque commande a executter
//pour exec la premier commande et change stdout si besoin

	// pipe pipe_i fois
	// compter BUILT_IN cmd from full_cmd
	// fork cmd_i fois + 1  - B_in cmd
	// faire redirection par raport au cmd_i
	// executer cmd_i
// void	restart_redirection();
// {
// 	if (dup2(fd[0][0], STDIN_FILENO) == -1)
//         err_msg("dup child2 STDIN");
//     if (dup2(fd[1][1], STDOUT_FILENO) == -1)
//         err_msg("dup child2 STDIN");
// }

void	execution_main(t_info *info)
{
	int	id;

	if (info->cmd_i == 0)
	{
		if (info->full_cmd[0][0] == '\0')
		{
			id = fork();
			if (id == 0)
			{	
				redirect_in_out(info, 0);
				exit(0);
			}
			else
				wait(&id);
		}
		else
			exec_single_cmd(info);
	}
	else
		return ;
}

/*
void	execution(char **path, char **cmd_tab, char **envp, t_env *liste)
{
	int	id;

	// if (is_builtin(cmd_tab[0]))
	// {
	// 	exec_builtin(cmd_tab, *liste);
	// 	free (*path);
	// 	return ;
	// }
	id = fork();
	if (id == 0)
		execve(*path, cmd_tab, envp);
	else
		free (*path);
	wait(&id);
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

// 
// @brief execute toutes les commandes se trouvant dans shell->cmds
// @param shell 
void	exec_commands(t_shell *shell)
{
	int		i;
	t_cmd	*cmd;exo

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