void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			printf("tab[i] = %s\n", tab[i]);
			i++;
		}
	}
}

void	print_tab_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			j = 0;
			while (tab[i][j])
			{
				printf("tab[i][j] = %s\n", tab[i][j]);
				j++;
			}
			printf("tab[i]++\n");
			i++;
		}
	}
}
