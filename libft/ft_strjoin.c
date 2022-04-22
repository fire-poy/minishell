/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhermon- <jhermon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:25:18 by mpons             #+#    #+#             */
/*   Updated: 2022/04/22 16:01:41 by jhermon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*dst;
	size_t	len;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	if (!s2)
		return (s1);
	i = -1;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = malloc(len * sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free (s1);
	return (dst);
}
