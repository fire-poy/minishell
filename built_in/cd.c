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

int	free_cd(char *dir, char *arg, char *pwd, int ret)
{
	if (dir)
		free(dir);
	if (arg)
		free(arg);
	if (pwd)
		free(pwd);
	return (ret);
}

int	cd_check(char *args)
{
	if (chdir(args) <= -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		print_join(args, ": ", 2);
		if (open(args, O_RDONLY) > 0)
		{
			// ft_putstr_fd("Not a directory\n", 2);
			// info->exit_status = cmd_err(info, cmd_name, MSG_IS_DIRECTORY, 126);
			return (1);
		}
		ft_putstr_fd("No such file orA directory\n", 2);
		return (1);
	}
	return (0);
}

void	ft_cd(char **argv, t_env *env)
{
	char	*dir;
	char	cwd[PATH_MAX];
	char	*pwd;

	dir = NULL;
	if (!argv[1])
	{
		argv[1] = get_env(env, "HOME");
		//printf("path = %s\n", argv[1]);
		if (!argv[1])
		{
			ft_putstr_fd("minishell: cd : HOME not set\n", 2);
			return ;
		}
	}
	if (!ft_strcmp(argv[1], "\"\"") || !ft_strcmp(argv[1], "\'\'"))
		return ;
	if (cd_check(argv[1]))
		return ;
	dir = getcwd(cwd, sizeof(cwd));
	//printf("dir = %s\n", dir);
	pwd = get_env(env, "PWD");
	//printf("pwd = %s\n", pwd);
	ft_env_set_content(env, "OLDPWD", pwd);
	ft_env_set_content(env, "PWD", dir);
	// free (argv[1]);
	argv[1] = NULL;
	//free_cd(dir, NULL, pwd, 0);
}
