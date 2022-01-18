/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:12:31 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/18 19:03:03 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_red(char *line, int j)
{
	if (line[j] == '<')
		return (1);
	if (line[j] == '>' && (!line[j + 1] || line[j + 1] != '>'))
		return (2);
	else
		return (3);
}

char	*del_redir(char *line, int i, char *str)
{
	char	*temp[3];

	if (i < ft_strlen(line))
		temp[1] = ft_strdup(line + i);
	else
		temp[1] = ft_strdup("");
	temp[2] = ft_strjoin_free(str, " ");
	temp[0] = ft_strjoin_free(temp[2], temp[1]);
	free(temp[1]);
	return (temp[0]);
}

char	*right_redir(char *line, int i, t_node *data, int flag)
{
	char	*temp[3];
	char	*file_name;
	int		j;

	if (i > 0)
		temp[0] = ft_substr(line, 0, i - 1);
	else
		temp[0] = ft_strdup("");
	while (line[i] && (line[i] == ' ' || line[i] == '>' || line[i] == '<'))
		i++;
	j = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, flag);
	while (line[i] == ' ')
		i++;
	if (data->is_err == 0)
		temp[0] = del_redir(line, i, temp[0]);
	free(line);
	temp[0] = space_prepare(temp[0]);
	return (temp[0]);
}

char	*ft_redirect(char *line, int *i, t_node *data)
{
	int	flag;
	int	j;

	j = *i;
	flag = 0;
	if (*i > 0)
		*i -= 1;
	flag = check_red(line, j);
	if (flag > 0)
		return (right_redir(line, j, data, flag));
	return (line);
}
