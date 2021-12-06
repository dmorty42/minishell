/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 16:40:16 by dmorty            #+#    #+#             */
/*   Updated: 2021/09/09 20:03:30 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static int	ft_words_len(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static void	*ft_leak(char **temp, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (NULL);
}

static char	**ft_fill(char const *s, int words, char c, char **temp)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < words)
	{
		while (*s == c)
			s++;
		len = ft_words_len(s, c);
		temp[i] = (char *)malloc(len + 1);
		if (!temp[i])
			return (ft_leak(temp, i));
		j = 0;
		while (j < len)
			temp[i][j++] = *s++;
		temp[i][j] = '\0';
	}
	temp[i] = NULL;
	return (temp);
}

char	**ft_split(char const *s, char c)
{
	char	**temp;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	temp = (char **)malloc(sizeof(char *) * (words + 1));
	if (!temp)
		return (NULL);
	temp = ft_fill(s, words, c, temp);
	return (temp);
}
