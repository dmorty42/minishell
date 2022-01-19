/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:58:46 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/19 19:53:58 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*space_prepare(char *line)
{
	int	i;

	i = 0;
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
		if (line[i + 1] && line[i] == ' ' && line[i + 1] == ' ')
		{
			line = ft_del_space(line, &i);
			i = 0;
		}
		i++;
	}
	return (line);
}

char	*ft_tilde(char *line, int *i, t_node *data)
{
	int		j;
	char	*temp;
	char	*temp1;
	char	*temp2;

	j = *i;
	temp = ft_substr(line, 0, j);
	temp1 = ft_strdup(line + j + 1);
	temp2 = ft_strjoin(temp, data->home);
	free(temp);
	temp = ft_strjoin(temp2, temp1);
	free(temp2);
	free(temp1);
	free(line);
	return (temp);
}

char	*ft_exsts(char *line, int *i)
{
	char	*temp;
	char	*temp1;

	temp = ft_substr(line, 0, *i);
	temp1 = ft_itoa(g_exit_status);
	temp = ft_strjoin_free(temp, temp1);
	free(temp1);
	temp1 = ft_strdup(line + *i + 2);
	temp = ft_strjoin_free(temp, temp1);
	free(temp1);
	free(line);
	return (temp);
}

char	*trick(char *line, int *i, t_node *data)
{
	if (line[*i] == '~')
		return (ft_tilde(line, i, data));
	if (line[*i] == '\'')
		return (ft_gap(line, i));
	if (line[*i] == '\\')
		return (ft_slash(line, i));
	if (line[*i] == '\"')
		return (ft_gap2(line, i, data->env_lst));
	if (line[*i] == '$' && line[*i + 1] == '?')
		return (ft_exsts(line, i));
	if (line[*i] == '$')
		return (ft_dollar(line, i, data->env_lst));
	return (line);
}

void	parser(char *line, t_node *data)
{
	int		i;
	int		t;
	int		j;

	i = -1;
	j = 0;
	t = 0;
	line = parser_redir(line, data);
	while (data->is_err == 0 && line[++i])
	{
		line = trick(line, &i, data);
		if (line[i] == ' ')
		{
			data->cmd = two_dim_work(data->cmd, ft_substr(line, t, i - t), &j);
			t = i + 1;
		}
	}
	if (data->is_err == 0 && t != ft_strlen(line))
	{
		data->cmd = two_dim_work(data->cmd, \
					ft_substr(line, t, ft_strlen(line) - t), &j);
	}
	parse_path(data);
	free(line);
}
