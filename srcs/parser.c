/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:58:46 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/18 18:10:28 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*space_prepare(char *line)
{
	int	i;

	i = 0;
	check_syntax(line);
	while (line[i] == ' ')
		line = ft_del_space(line, &i);
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i++;
			while ((line[i] != '\'' || line[i] != '\"') && line[i])
				i++;
		}
		if (line[i] == ' ' && line[i + 1] == ' ')
			line = ft_del_space(line, &i);
		i++;
	}
	return (line);
}

void	parser(char *line, t_env *env, t_node *data)
{
	int		i;
	int		t;
	int		j;
	char	*str;

	i = -1;
	j = 0;
	t = 0;
	while (line[++i])
	{
		if (line[i] == '\'')
			line = ft_gap(line, &i);
		if (line[i] == '\\')
			line = ft_slash(line, &i);
		if (line[i] == '\"')
			line = ft_gap2(line, &i, env);
		if (line[i] == '$')
			line = ft_dollar(line, &i, env);
		if (line[i] == ' ')
		{
			str = ft_substr(line, t, i - t);
			data->cmd = two_dim_work(data->cmd, str, &j);
			t = i + 1;
		}
	}
	if (t != ft_strlen(line))
	{
		str = ft_substr(line, t, ft_strlen(line) - t);
		data->cmd = two_dim_work(data->cmd, str, &j);
	}
}
