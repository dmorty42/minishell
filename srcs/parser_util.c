/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:05:27 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/28 03:26:57 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_dollar(char *line, int *i, t_env *env)
{
	int		j;
	char	*key;
	char	*temp;
	char	*temp2;

	j = *i;
	while (line[++(*i)])
		if (!ifkey(line[*i]))
			break ;
	if (*i == j + 1)
		return (line);
	temp = ft_substr(line, 0, j);
	key = ft_substr(line, j + 1, *i - j - 1);
	key = find_value(key, env);
	temp2 = ft_strdup(line + *i);
	temp = ft_strjoin(temp, key);
	temp = ft_strjoin(temp, temp2);
	free(line);
	*i -= 1;
	return (temp);
}

char	*ft_slash(char *line, int *i)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(line, 0, *i);
	temp2 = ft_strdup(line + *i + 1);
	temp = ft_strjoin(temp, temp2);
	*i += 1;
	free(line);
	return (temp);
}

char	*ft_gap2(char *line, int *i, t_env *env)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = *i;
	while (line[++(*i)])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"' \
			|| line[*i + 1] == '$' || line[*i + 1] == '\\'))
			line = ft_slash(line, i);
		if (line[*i] == '$')
			line = ft_dollar(line, i, env);
		if (line[*i] == '\"')
			break ;
	}
	temp = ft_substr(line, 0, j);
	temp2 = ft_substr(line, j + 1, *i - j - 1);
	temp3 = ft_strdup(line + *i + 1);
	temp = ft_strjoin(temp, temp2);
	temp = ft_strjoin(temp, temp3);
	*i -= 2;
	free(line);
	return (temp);
}

char	*ft_gap(char *line, int *i)
{
	int		j;
	char	*temp;
	char	*temp2;
	char	*temp3;

	j = *i;
	while (line[++(*i)])
		if (line[*i] == '\'')
			break ;
	temp = ft_substr(line, 0, j);
	temp2 = ft_substr(line, j + 1, *i - j - 1);
	temp3 = ft_strdup(line + *i + 1);
	temp = ft_strjoin(temp, temp2);
	temp = ft_strjoin(temp, temp3);
	*i -= 1;
	free(line);
	return (temp);
}
