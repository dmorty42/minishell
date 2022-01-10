/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:58:46 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/11 02:19:51 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_space(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if ((line[i + 1] && line[i] != ' ' ) || line[i + 1] != ' ')
			j++;
		i++;
	}
	return (j);
}

char	*space_prepare(char *line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	temp = (char *)malloc(count_space(line) + 1);
	while (line[i])
	{
		if ((line[i + 1] && line[i] != ' ' ) || line[i + 1] != ' ')
		{
			temp[j] = line[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	if (temp[0] == ' ')
		temp = ft_strdup(temp + 1);
	free(line);
	return (temp);
}

char	*ft_tilde(char *line, int *i, t_node *data)
{
	int		j;
	char	*temp;
	char	*temp1;

	j = *i;
	temp = ft_substr(line, 0, j);
	while (ft_strncmp(data->env_lst->key, \
			"HOME", ft_strlen(data->env_lst->key)))
		data->env_lst = data->env_lst->next;
	temp1 = ft_strdup(line + j + 1);
	temp = ft_strjoin(temp, data->env_lst->value);
	temp = ft_strjoin(temp, temp1);
	*i += ft_strlen(data->env_lst->value);
	return (temp);
}

char	*trick(char *line, int *i, t_node *data, t_env *env)
{
	if (line[*i] == '~')
		return (ft_tilde(line, i, data));
	if (line[*i] == '\'')
		return (ft_gap(line, i));
	if (line[*i] == '\\')
		return (ft_slash(line, i));
	if (line[*i] == '\"')
		return (ft_gap2(line, i, env));
	if (line[*i] == '$')
		return (ft_dollar(line, i, env));
	return (line);
}

void	parser(char *line, t_env *env, t_node *data)
{
	int		i;
	int		t;
	int		j;

	i = -1;
	j = 0;
	t = 0;
	line = parser_redir(line, data);
	while (line[++i])
	{
		line = trick(line, &i, data, env);
		if (line[i] == ' ')
		{
			data->cmd = two_dim_work(data->cmd, ft_substr(line, t, i - t), &j);
			t = i + 1;
		}
	}
	if (t != ft_strlen(line))
		data->cmd = two_dim_work(data->cmd, \
					ft_substr(line, t, ft_strlen(line) - t), &j);
	parse_path(data);
	free(line);
}
