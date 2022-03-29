#include "../minishell.h"
#include "../libft/libft.h"

// char *trim(char *input)
// {
// 	char	trim[2];

// 	trim[0] = ' ';
// 	trim[1] = '\t';
// 	return (ft_strtrim(input, trim));
// }

int	search_quotes_closed(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] != '\'' || str[i] != '\"' )	
			i++;
		if (str[i] == '\'') 
		{
			s_quote++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '\"') 
		{
			d_quote++;
			while (str[i] != '\"')
				i++;
		}
	}
}

int	search_quotes_closed(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && str[i]) 
		{
			s_quote++;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		if (str[i] == '\"' && str[i]) 
		{
			d_quote++;
			while (str[i] != '\"' && str[i])
				i++;
		}
		if (s_quote % 2 == 1 || d_quote % 2 == 1)
		{
			exit_status == 3;
			err_msg("quotes pas bien fermés")
			break;
		}
	}
}

// if(str[i] == '$')

int	lexer(char *input)
{
	// char *str_trim;
	// char *z;
	// str_trim = trim(input);
	search_single_quotes(input)
	