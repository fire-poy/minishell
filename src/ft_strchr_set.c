#include "../minishell.h"

int	ft_strchr_char(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	ft_c_vs_charset(char c, const char *cs)
{
	int	i;

	i = 0;
	while (c != cs[i] && cs[i] && cs[i + 1] != '\0')// je pourrais enlever apres dernier &&
		i++;
	if (c == cs[i])
		return (1);
	else
		return (0);
}

//return i in position of char from charset
//return strlen if set not found
int	ft_strchr_set(const char *s, char *set)
{
	int	i;

	i = 0;
	while (s[i] && !ft_c_vs_charset(s[i], set))//while I dont find charset I advance
		i++;
	return (i);
}

//search charset a partir du start, avance l'address si trouve le chset;
//return 0 si ne trouve pas, 1 en succes
int	ft_charset_found(const char *s, int* start, char *set)
{
	int	i;

	i = *start;
	while (s[i] && !ft_c_vs_charset(s[i], set))//while I dont find charset I advance
		i++;
	if (s[i] == 0)		
		return (0);
	else
		*start = i;
	return (1);
}
