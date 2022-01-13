/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:12:31 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/13 20:01:36 by dmorty           ###   ########.fr       */
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

char	*right_redir(char *line, int i, t_node *data, int flag)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*file_name;
	int		j;

	temp = NULL;
	temp1 = NULL;
	temp2 = NULL;
	if (i > 0)
		temp = ft_substr(line, 0, i - 1);
	else
		temp = ft_strdup("");
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
	{
		if (i < ft_strlen(line))
			temp1 = ft_strdup(line + i);
		else
			temp1 = ft_strdup("");
		temp2 = ft_strjoin(temp, " ");
		free(temp);
		temp = ft_strjoin(temp2, temp1);
	}
	free(temp2);
	free(temp1);
	free(line);
	temp = space_prepare(temp);
	return (temp);
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
