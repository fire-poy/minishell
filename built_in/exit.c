/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:51:16 by jhermon-          #+#    #+#             */
/*   Updated: 2022/05/11 16:13:22 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char	*arg)
{
	char	*message;
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			message = ft_strjoin(arg, ": numeric argument required");
			err_exit("minishell: exit: ", message, 255);
			return (0);
		}
		i++;
	}
	return (1);
}

int	exit_arg(char *arg)
{
	int	estatus;

	if (check_arg(arg) == 0)
		return (0);
	estatus = ft_atoi(arg);
	return (estatus);
}

void	ft_exit(char **tab_cmd, t_info *info)
{
	int	i;

	if (tab_cmd[1] == NULL)
	{
		printf("exit\n");
		ft_free_list(&info->liste);
		free_all(info);
		exit(0);
	}
	if (tab_cmd[2] != NULL)
	{
		printf("Minishell: exit :too many arguments\n");
		info->exit_status = 1;
		return ;
	}
	i = exit_arg(tab_cmd[1]);
	printf("exit\n");
	ft_free_list(&info->liste);
	free_all(info);
	exit(i);
}

// char	*str_joins(char *str1, char *str2, char *sep)
// {
// 	char	*str;
// 	char	*tmp;

// 	if (!str1 || !str2)
// 		return (0);
// 	tmp = ft_strjoin(str1, sep);
// 	if (!tmp)
// 		return (0);
// 	str = ft_strjoin(tmp, str2);
// 	free(tmp);
// 	if (!str)
// 		return (0);
// 	return (str);
// }

// int	contain_env(char *str, char *name)
// {
// 	char	*tmp;

// 	if (!str || !name)
// 		return (0);
// 	tmp = ft_strjoin(name, "=");
// 	if (!tmp)
// 		return (0);
// 	if (ft_strncmp(str, tmp, ft_strlen(tmp)) == 0)
// 	{
// 		free(tmp);
// 		return (1);
// 	}
// 	free(tmp);
// 	return (0);
// }

// char	*get_the_env(t_info *shell, char *name)
// {
// 	int	i;

// 	i = -1;
// 	if (!name)
// 		return (0);
// 	printf("shell[i] = %s\n", shell->envp[0]);
// 	while (shell->envp[++i])
// 		if (contain_env(shell->envp[i], name))
// 			return (shell->envp[i] + ft_strlen(name) + 1);
// 	return (0);
// }

// int	set_env(t_info *shell, char *name, char *value)
// {
// 	int	i;

// 	i = -1;
// 	if (!name || !value)
// 		return (0);
// 	while (shell->envp[++i])
// 	{
// 		if (contain_env(shell->envp[i], name))
// 		{
// 			free(shell->envp[i]);
// 			shell->envp[i] = str_joins(name, value, "=");
// 		}
// 	}
// 	free(name);
// 	free(value);
// 	return (1);
// }

// int	add_env(t_info *shell, char *name, char *value)
// {
// 	int		i;
// 	char	**envs;

// 	if (!name || !value)
// 		return (0);
// 	i = array_length(shell->envp);
// 	envs = ft_calloc(sizeof(*envs), i + 2);
// 	if (!envs)
// 		return (0);
// 	envs[i] = str_joins(name, value, "=");
// 	while (i--)
// 		envs[i] = shell->envp[i];
// 	free(name);
// 	free(value);
// 	free(shell->envp);
// 	shell->envp = envs;
// 	return (1);
// }

// void	save_exit_status(t_info *shell)
// {
// 	if (get_the_env(shell, "?"))
// 		set_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
// 	else
// 		add_env(shell, ft_strdup("?"), ft_itoa(shell->exit_status));
// 	shell->exit_status = 0;
// }
