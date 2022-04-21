#include "../minishell.h"

int	ft_builtin(t_token *token, t_env *liste)
{
	t_token	*cmd;
	t_env		*env;

	cmd = token;
	env = liste;
	cmd->export_content = ft_split(cmd->content, ' ');
	// printf("cmd->content = %s\n", cmd->content);
	// printf("cmd->tab_cmd[0] = %s\n", cmd->tab_cmd[0]);
	if (!ft_strcmp(cmd->content, "exit"))
		ft_exit(cmd);
	if (!ft_strcmp(cmd->content, "pwd"))
		return(current_dir());
	if (!ft_strcmp(cmd->content, "cd"))
		ft_cd(cmd->content, env);
	if (!ft_strcmp(cmd->content, "echo"))
		ft_echo(cmd->content);
	if (!ft_strcmp(cmd->content, "env"))
		return(my_env(liste));
	if (!ft_strcmp(cmd->content, "unset"))
		ft_unset(&liste, cmd->content);
	if (!ft_strcmp(cmd->content, "export"))
		liste = ft_export(cmd->content, env, token);
	return (1);
}