#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

int	exec_builtin(char **tab_cmd, t_env *liste)
{
	// if (!ft_strcmp(tab_cmd[0], "exit"))
	// 	ft_exit(tab_cmd);
	// if (!ft_strcmp(tab_cmd[0], "pwd"))
	// 	return(current_dir());
	// if (!ft_strcmp(tab_cmd[0], "cd"))
	// 	ft_cd(tab_cmd, env);
	// if (!ft_strcmp(tab_cmd[0], "echo"))
	// 	ft_echo(tab_cmd);
	// if (!ft_strcmp(tab_cmd[0], "env"))
	// 	return(my_env(liste));
	// if (!ft_strcmp(tab_cmd[0], "unset"))
	// 	ft_unset(&liste, tab_cmd);
	// if (!ft_strcmp(tab_cmd[0], "export"))
	// 	liste = ft_export(tab_cmd, env, token);
	(void)tab_cmd;
	(void)liste;
	return (1);
}