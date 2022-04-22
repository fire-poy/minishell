#include "../minishell.h"

/*
bash-3.2$ cd he
bash: cd: he: No such file or directory
bash-3.2$ cd ../help
bash: cd: ../help: No such file or directory
*/
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
			ft_putstr_fd("Not a directory\n", 2);
			return (1);
		}
		ft_putstr_fd("No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

void	ft_cd(char **argv, t_env *env)
{
	char	*dir;
	char  cwd[PATH_MAX];
	char	*pwd;

	dir = NULL;
	if (!argv[1])
	{
		argv[1] = get_env(env, "HOME");
		//printf("path = %s\n", argv[1]);
		if (!argv[1])
		{
			ft_putstr_fd("minishell: cd : HOME not set", 2);
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
	//free_cd(dir, NULL, pwd, 0);
}

/*int	main(int argc, char **argv, char **envp)
{   
	t_env *head;

	head = (t_env *)malloc(sizeof(t_env));
 	create_env_list(&head, envp);
	printlist(head);
	// printing current working directory
	ft_cd(argv[1], head);
	//printlist(head);
	//current_dir();
	// the regular shell does show all available directory ???
	//if (chdir(argv[1]) == -1)
		//perror(argv[1]);
	//printf("cd: no such file or directory: %s\n", argv[1]);
	// printing current working directory
	//current_dir();
	// after chdir is executed
	//}
	//printf("getpid = %d\n", getpid());
	return (0); 
}*/
