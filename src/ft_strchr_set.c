#include "../minishell.h"

int	ft_c_vs_charset(char c, const char *cs)
{
	int	i;

	i = 0;
	while (c != cs[i] && cs[i] && cs[i + 1] != '\0')
		i++;
	if (c == cs[i])
		return (1);
	else
		return (0);
}

//return i in position of char from charset
int	ft_strchr_set(const char *s, char *set)
{
	int	i;

	i = 0;
	while (s[i] && !ft_c_vs_charset(s[i], set))//while I dont find charset I advance
		i++;
	return (i);
}