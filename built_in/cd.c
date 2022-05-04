#include "../minishell.h"

char	*get_env(t_env *env, char *name)
{
	if (!name)
		return ("$");
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	cd_check(char *args, t_info *liste)
{
	if (chdir(args) <= -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		print_join(args, ": ", 2);
		if (open(args, O_RDONLY) > 0)
		{
			ft_putstr_fd("Not a directory\n", 2);
			liste->exit_status = show_command_error(liste, args, MSG_IS_DIRECTORY, 126);
			return (1);
		}
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	ft_cd(char **argv, t_info *info)
{
	char	*dir;
	char	cwd[PATH_MAX];
	char	*pwd;

	if (!argv[1] || !ft_strcmp(argv[1], "~") || !ft_strcmp(argv[1], "-"))
	{
		argv[1] = get_env(info->liste, "HOME");
		if (!argv[1])
		{
			ft_putstr_fd("minishell: cd : HOME not set\n", 2);
			return ;
		}
	}
	if (!ft_strcmp(argv[1], "\"\"") || !ft_strcmp(argv[1], "\'\'"))
		return ;
	if (cd_check(argv[1], info))
		return ;
	dir = getcwd(cwd, sizeof(cwd));
	printf("dir = %s\n", dir);
	printf("dir cwd= %s\n", getcwd(cwd, sizeof(cwd)));
	pwd = get_env(info->liste, "PWD");
	printf("pwd= %s\n", pwd);
	ft_env_set_content(info->liste, "OLDPWD", pwd);
	ft_env_set_content(info->liste, "PWD", dir);
	argv[1] = NULL;
}
