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
		// how to collect a var even without export?
	}
	return (0);
}

int	ft_varlen(char *var)
{
	int	i;

	i = 0;
	while(var[i])
	{
		if (var[i] == '=')
		{
			//printf("varlen = %d\n", i);	
			return (i+1);
		}
		i++;
	}
	//printf("varlen = %d\n", i);
	return (i);
}
