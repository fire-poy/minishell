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
	else if (!ft_strcmp(cmd->tab_cmd[0], "pwd") || !ft_strcmp(cmd->tab_cmd[0], "PWD"))
		return(current_dir());
	else if (!ft_strcmp(cmd->tab_cmd[0], "cd"))
		ft_cd(cmd->tab_cmd, env);
	else if (!ft_strcmp(cmd->tab_cmd[0], "echo") || !ft_strcmp(cmd->tab_cmd[0], "ECHO"))
		ft_echo(cmd->tab_cmd);
	else if (!ft_strcmp(cmd->tab_cmd[0], "env") || !ft_strcmp(cmd->tab_cmd[0], "ENV"))
		return(my_env(liste));
	else if (!ft_strcmp(cmd->tab_cmd[0], "unset"))
		ft_unset(&liste, cmd->tab_cmd);
	else if (!ft_strcmp(cmd->tab_cmd[0], "export"))
		liste = ft_export(cmd->tab_cmd, env, token);
	else 
		ft_check_path(token->content, &env->initial_env);
	return (1);
}