/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:17:41 by mpons             #+#    #+#             */
/*   Updated: 2022/03/31 15:51:25 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;

	if (!s)
		return (0);
	ch = (char)c;
	str = (char *)s;
	i = 0;
	while (str[i] != ch)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i+1);
}	
