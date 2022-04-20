#include "../minishell.h"

// fstat(int fd, struct stat *buf) -- Where fd is the file descriptor 
// and the structure 'buf' is returned by the API. This structure 
// object contains all the information. The function returns 0 
// on success and -1 on failure. 

int fstat(int fd, struct stat *buf);

// void	ft_execve(char *cmd, char **args, char **list)
// {
// 	//char	*error;

// 	if (execve(cmd, args, list) == -1)
// 	{
// 		// error = ft_strjoin(": ", strerror(errno));
// 		// ft_put_err(cmd->command, error, errno);
// 		// free(error);
// 		exit(errno);
// 	}
// }

// int	ft_exec(char *cmd, char **env)
// {
// 	int		pid;
// 	int		status;
// 	int		f_status;

// 	pid = fork();
// 	f_status = 0;
// 	if (!pid)
// 		ft_execve(cmd, ft_args_to_arr(cmd), ft_list_to_arr(env));
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			f_status = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 		{
// 			f_status = 128 + WTERMSIG(status);
// 			if (WTERMSIG(status) == SIGQUIT)
// 				write(1, "Quit: 3\n", 8);
// 		}
// 	}
// 	return (f_status);
// }

char	*ft_get_last_arg(char *src)
{
	int	i;
	int j;
	int	dst_len;
	char *dst;

	i = ft_strlen(src) - 1;
	dst_len = 0;
	printf("get last src = %s\n", src);
	printf("i = %d\n", i);
	while (src[i] != '/')
	{
		dst_len++;
		i--;
	}
	printf("dst_len = %d\n", dst_len);
	j = 0;
	//i = ft_strlen(src) - 1;
	i++;
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	while (src[i])
	{
		dst[j++] = src[i++];
		//i--;
	}
	dst[j] = '\0';
	printf("dst = %s\n", dst);
	return (dst);
}

int	ft_path_fstat(char *cmd, char **env)
{
	int	f_d;
	struct stat st;
	(void)env;

	f_d = open(cmd, O_RDONLY);
	if (-1 == f_d)
	{
		err_exit(cmd, " No such file or directory\n", errno);
		return (0);
	}
	errno = 0;
	if (fstat(f_d, &st))
	{
		err_exit(cmd, "\nfstat error: [%s]\n", errno); 
    close(f_d); 
		return (-1); 
	}
	if (S_ISREG(st.st_mode))
	{
		err_exit(cmd, " Is not a directory\n", errno);
		return(1);
	}
	else if (S_ISDIR(st.st_mode))
	{
		err_exit(cmd, " File is a directory\n", errno);
		return (2);
	}
	close(f_d);
	return (3);
	//return (ft_exec(cmd, env));
}

void	ft_check_path(char *cmd, char **env)
{
	char	**path_cmd;

	path_cmd = NULL;
	if (!cmd)
	{
		printf("fuck\n");
		return ;
	}
	else
		printf("cmd = %s\n", cmd);
	//printf("cmd->argv[2] = %s\n", cmd->argv[3]);
	if (ft_strchr(cmd, '/'))
	{
		if (ft_path_fstat(cmd, env) == 3)
		{
			printf("has a /\n");
			//path_cmd = malloc(sizeof(char) * ft_strlen(cmd) + 1);

			if (access(cmd, F_OK) == 0)
			{
				printf("access = 0\n");
				path_cmd = malloc(sizeof(char) * 100 + 1);
				path_cmd[0] = malloc(sizeof(char) * 100 + 1);
				path_cmd[0] = ft_get_last_arg(cmd);
				printf("path_cmd[0] = %s\n", path_cmd[0]);
				path_cmd[1] = malloc(sizeof(char) * 100 + 1);
				path_cmd[1] = NULL;
				printf("path_cmd[1] = %s\n", path_cmd[1]);
				printf("path_cmd = %s\n", path_cmd[0]);
				//ft_exec(cmd, env);
				// ***** should send path to execution here but doesn't work ******
			}
		}
			printf("did not execve\n");
	}
	else
	{
		free(path_cmd);
		return ;
	}
}
// void	ft_init_args(int argc, char **argv, char **envp)
// {
// 	t_arg	args;

// 	args.argc = argc;
// 	args.argv = argv;
// 	args.env = envp;
// }

// char	**ft_split(char *cmd, char sep)
// {
// 	char	**ret;
// 	int		i;
// 	int		j;
// 	int		count;

// 	count = ft_linecount(cmd, sep);
// 	ret = malloc(sizeof(char *) * (count + 2));
// 	if (!ret)
// 		return (NULL);
// 	ret[count + 1] = NULL;
// 	j = 0;
// 	while (j < count + 1)
// 	{
// 		i = 0;
// 		while (cmd[i] && cmd[i] != sep)
// 			i++;
// 		ret[j] = ft_dup(cmd, i);
// 		j++;
// 		cmd = cmd + i + 1;
// 	}
// 	return (ret);
// }

// int	ft_strcmp(char *str, int len, char *env)
// {
// 	while (--len > 0 && *str && *env && *env == *str)
// 	{
// 		env++;
// 		str++;
// 	}
// 	return (*env - *str);
// }

// char	*ft_join(char *s1, char *s2)
// {
// 	char	*dest;
// 	int		i;
// 	int		j;

// 	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
// 	if (!dest)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		dest[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		dest[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	dest[i++] = '\0';
// 	return (dest);
// }

// void	ft_run_path(char *cmd, char **env)
// {
// 	// char	*bin;
// 	// char	*dir;
// 	// int		i;
// 	// int		j;
// 	//t_arg	*liste;

// 	//liste = cmd;
// 	if (cmd)
// 		printf("cmd = %s\n", cmd);
// 	else
// 		printf("fuck\n");
// 	//printf("cmd->argv[2] = %s\n", cmd->argv[3]);
// 	if (ft_strchr(cmd, '/'))
// 	{
// 		printf("has a /\n");
// 		if (access(cmd, F_OK) == 0)
// 			execve(cmd, &cmd, env);
// 		printf("did not execve\n");
// 	}
	// {
	// 	// while (cmd->env && ft_strcmp("PATH=", 5, cmd->env) != 0)
	// 	// 	cmd->env++;
	// 	// struc->getpath = *env + 5;
	// 	// i = 0;
	// 	// while (struc->getpath[i])
	// 	// {
	// 	// 	bin = malloc(sizeof(char) * ft_strlen(struc->getpath));
	// 	// 	j = 0;
	// 	// 	i = 0;
	// 	// 	while (struc->getpath[i] && struc->getpath[i] != ':')
	// 	// 		bin[j++] = struc->getpath[i++];
	// 	// 	bin[j++] = '/';
	// 	// 	dir = ft_join(bin, cmd);
	// 		if (access(*cmd->argv, F_OK) == 0)
	// 			execve(*cmd->argv, cmd->argv, cmd->env);
	// 		//free(bin);
	// 		//dir = NULL;
	// 		//struc->getpath += i + 1;
	// }
//}
