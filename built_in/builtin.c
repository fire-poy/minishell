#include "../minishell.h"

int	ft_builtin(t_token *token, t_env *liste)
{
	t_token	*cmd;

	cmd = token;
	cmd->tab_cmd = ft_split(cmd->content, ' ');
	if (!ft_strncmp(cmd->content, "exit", 5))
	{
		// I can't get error message to print in Minishell ????
		return (ft_exit(cmd));
	}
	if (!ft_strncmp(cmd->content, "pwd", 4))
		return(current_dir());
	/*if (!ft_strncmp(cmd->content, "cd", 3))
		exit(0);*/
	if (!ft_strncmp(cmd->content, "echo", 5))
	{
		return(ft_echo(cmd->tab_cmd));
	}
	if (!ft_strncmp(cmd->content, "env", 4))
		return(my_env(liste));
	/*if (!ft_strncmp(cmd->content, "unset", 6))
		exit(0);*/
	if (!ft_strncmp(cmd->content, "export", 7))
		return(ft_export(cmd->tab_cmd, liste));
	return (1);
}