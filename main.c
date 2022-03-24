#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strlen(char *s)
{
	

int	main(void)
{
	char *in;
	
	while (1)
	{
		in = readline("Minishell >");
		if (ft_strlen(in) > 0)
			add_history(in);
		/*
		if (!strcmp(string, "wc"))
		{
			foijtjefjooifasoij
		}
		if (cd -> )
*/
	}
	return (0);
}
