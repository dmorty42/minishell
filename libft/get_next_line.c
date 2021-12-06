/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 13:22:24 by dmorty            #+#    #+#             */
/*   Updated: 2021/09/09 20:03:30 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	up_remainder(char **remainder, char *buf)
{
	char	*temp;

	temp = ft_strjoin(*remainder, buf);
	free(*remainder);
	*remainder = temp;
}

static int	final_function(char **remainder, char **line)
{
	int		len;
	char	*temp;

	len = 0;
	while ((*remainder)[len] != '\n' && (*remainder)[len] != '\0')
		len++;
	if ((*remainder)[len] == '\n')
	{
		*line = ft_substr(*remainder, 0, len);
		temp = ft_strdup(&((*remainder)[len + 1]));
		if (!*line || !temp)
			return (READ_ERROR);
		free(*remainder);
		*remainder = temp;
	}
	else
	{
		*line = ft_strdup(*remainder);
		if (!*line)
			return (READ_ERROR);
		free(*remainder);
		*remainder = NULL;
		return (READ_EOF);
	}
	return (READ);
}

static int	output(char **remainder, char **line, int bytes)
{
	if (bytes < 0)
		return (READ_ERROR);
	else if (bytes == 0 && *remainder == NULL)
	{
		*line = ft_strdup("");
		if (!*line)
			return (READ_ERROR);
		return (READ_EOF);
	}
	else
		return (final_function(&*remainder, line));
}

int	get_next_line(const int fd, char **line)
{
	int			bytes;
	static char	*remainder;
	char		buf[BUFFER_SIZE + 1];

	bytes = 1;
	if (fd < 0)
		return (READ_ERROR);
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes >= 0)
			buf[bytes] = '\0';
		if (bytes <= 0)
			break ;
		if (remainder == NULL)
			remainder = ft_strdup(buf);
		else
			up_remainder(&remainder, buf);
		if (!remainder)
			return (READ_ERROR);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	return (output(&remainder, line, bytes));
}
