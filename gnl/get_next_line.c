/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpons <mpons@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:25:34 by mpons             #+#    #+#             */
/*   Updated: 2022/05/03 09:29:17 by mpons            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "./get_next_line.h"
#include "../minishell.h"

char	*ft_read_save(int fd, char *str)
{
	char	*buf;
	int		char_lu;
	int		i;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	while (!ft_strchr(str, '\n'))
	{
		char_lu = read(fd, buf, BUFFER_SIZE);
		if (char_lu == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[char_lu] = '\0';
		if (!str)
			str = ft_strdup("");
		str = ft_strjoin_free(str, buf);
		if (char_lu == 0)
			break ;
	}
	free (buf);
	return (str);
}

char	*ft_get_line_gnl(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = ft_substr(s, 0, i);
	return (line);
}

char	*ft_reste(char *s)
{
	char	*new_s;
	int		i;

	i = 0;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	new_s = ft_substr(s, i, ft_strlen(s) - i + 1);
	free(s);
	return (new_s);
}

char	*get_next_line(int fd)
{
	char		*r_line;
	static char	*bkp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bkp = ft_read_save(fd, bkp);
	if (!bkp)
		return (NULL);
	r_line = ft_get_line_gnl(bkp);
	bkp = ft_reste(bkp);
	return (r_line);
}
