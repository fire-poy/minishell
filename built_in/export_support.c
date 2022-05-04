#include "../minishell.h"
#include "../libft/libft.h"

int	ft_equal(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!var)
		return (1);
	while (var[i])
	{
		if (var[i] == '=')
		{
			equal = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_export_var(char *var)
{
	int	i;
	int	equal;

	i = 0;
	equal = ft_equal(var);
	if (equal == 0)
	{
		while (var[i])
		{
			if (!ft_isalpha(var[i]))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			return (i + 1);
		}
		i++;
	}
	return (i);
}

void	ft_replace_var(t_env **head, char *name, char *content, char *var)
{
	int	flag;

	flag = 0;
	free((*head)->content);
	(*head)->content = ft_strdup(content);
	if ((*head)->initial_env)
		flag = 1;
	if (flag == 1)
		free((*head)->initial_env);
	(*head)->initial_env = ft_strdup(var);
	free((*head)->name);
	(*head)->name = ft_strdup(name);
}
