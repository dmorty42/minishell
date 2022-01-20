/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:05:27 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/20 05:03:22 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_dollar(char *line, int *i, t_env *env)
{
	int		j;
	char	*key;
	char	*temp;
	char	*temp2;
	char	*temp3;

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
	temp3 = ft_strjoin_free(temp, key);
	temp = ft_strjoin_free(temp3, temp2);
	if (ft_strlen(temp) < ft_strlen(line))
		*i = j + 1;
	free(line);
	free(temp2);
	*i -= 1;
	return (temp);
}

char	*ft_slash(char *line, int *i)
{
	char	*temp;
	char	*temp2;
	char	*temp3;

	temp = ft_substr(line, 0, *i);
	temp2 = ft_strdup(line + *i + 1);
	temp3 = ft_strjoin(temp, temp2);
	*i += 1;
	free(line);
	free(temp2);
	free(temp);
	return (temp3);
}

char	*minipars(char *line, int *i, t_env *env)
{
	while (line[++(*i)])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"' \
			|| line[*i + 1] == '$' || line[*i + 1] == '\\'))
			line = ft_slash(line, i);
		if (line[*i] == '$' && line[*i + 1] == '?')
			line = ft_exsts(line, i);
		if (line[*i] == '$')
			line = ft_dollar(line, i, env);
		if (line[*i] == '\"')
			break ;
	}
	return (line);
}

char	*ft_gap2(char *line, int *i, t_env *env)
{
	int		j;
	char	*temp[4];

	j = *i;
	line = minipars(line, i, env);
	temp[0] = ft_substr(line, 0, j);
	temp[1] = ft_substr(line, j + 1, *i - j - 1);
	temp[2] = ft_strdup(line + *i + 1);
	temp[3] = ft_strjoin_free(temp[0], temp[1]);
	temp[0] = ft_strjoin_free(temp[3], temp[2]);
	*i -= 2;
	free(line);
	free(temp[1]);
	free(temp[2]);
	return (temp[0]);
}

char	*ft_gap(char *line, int *i)
{
	int		x;
	char	*temp[4];

	x = *i;
	while (line[++(*i)])
		if (line[*i] == '\'')
			break ;
	temp[0] = ft_substr(line, 0, x);
	temp[1] = ft_substr(line, x + 1, *i - x - 1);
	temp[2] = ft_strdup(line + *i + 1);
	temp[3] = ft_strjoin_free(temp[0], temp[1]);
	temp[0] = ft_strjoin_free(temp[3], temp[2]);
	*i -= 2;
	free(line);
	free(temp[1]);
	free(temp[2]);
	return (temp[0]);
}
