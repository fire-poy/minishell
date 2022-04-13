#include "../minishell.h"

int	ft_builtin(t_token *token, t_env *liste)
{
	t_token	*cmd;
	t_env		*env;

	cmd = token;
	env = liste;
	cmd->tab_cmd = ft_split(cmd->content, ' ');
	// printf("cmd->content = %s\n", cmd->content);
	// printf("cmd->tab_cmd[0] = %s\n", cmd->tab_cmd[0]);
	if (!ft_strcmp(cmd->tab_cmd[0], "exit"))
		ft_exit(cmd);
	if (!ft_strcmp(cmd->tab_cmd[0], "pwd"))
		return(current_dir());
	if (!ft_strcmp(cmd->tab_cmd[0], "cd"))
		ft_cd(cmd->tab_cmd, env);
	if (!ft_strcmp(cmd->tab_cmd[0], "echo"))
		ft_echo(cmd->tab_cmd);
	if (!ft_strcmp(cmd->tab_cmd[0], "env"))
		return(my_env(liste));
	if (!ft_strcmp(cmd->tab_cmd[0], "unset"))
		ft_unset(&liste, cmd->tab_cmd);
	if (!ft_strcmp(cmd->tab_cmd[0], "export"))
		liste = ft_export(cmd->tab_cmd, env, token);
	return (1);
}