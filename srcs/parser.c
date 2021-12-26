/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:58:46 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/24 04:03:34 by dmorty           ###   ########.fr       */
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

char	*ft_tilde(char *line, int *i, t_node *data)
{
	int		j;
	char	*temp;
	char	*temp1;

	j = *i;
	temp = ft_substr(line, 0, j);
	while (ft_strncmp(data->env_lst->key, "HOME", ft_strlen(data->env_lst->key)))
		data->env_lst = data->env_lst->next;
	temp1 = ft_strdup(line + j + 1);
	temp = ft_strjoin(temp, data->env_lst->value);
	temp = ft_strjoin(temp, temp1);
	*i += ft_strlen(data->env_lst->value);
	return (temp);
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
	line = parser_redir(line, data);
	while (line[++i])
	{
		if (line[i] == '~')
			line = ft_tilde(line, &i, data);
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
