/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 07:12:31 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/21 20:46:33 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_redir(t_red *temp, t_node *data)
{
	if (data->red == NULL)
		data->red = temp;
	else
	{
		while (data->red->next != NULL)
			data->red = data->red->next;
		data->red->next = temp;
	}
}

char	*left_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i);
	i++;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, 1);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

int	check_red(char *line, int j)
{
	if (line[j] == '<')
		return (1);
	if (line[j] == '>' && (!line[j + 1] || line[j + 1] != '>'))
		return (2);
	else
		return (3);
}

char	*right_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i);
	i++;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, 2);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

char	*double_redir(char *line, int i, t_node *data)
{
	char	*temp;
	char	*temp1;
	char	*file_name;
	int		j;

	temp = ft_substr(line, 0, i);
	i += 2;
	while (line[i] == ' ')
		i++;
	j = i;
	while (line[i] != ' ' && line[i] != '\t' && line[i])
		i++;
	file_name = ft_substr(line, j, i - j);
	opening_file(file_name, data, 3);
	temp1 = ft_strdup(line + i + 1);
	temp = ft_strjoin(temp, temp1);
	return (temp);
}

char	*ft_redirect(char *line, int *i, t_node *data)
{
	int	flag;
	int	j;

	j = *i;
	*i -= 1;
	flag = check_red(line, j);
	data->redir_num += 1;
	if (flag == 1)
		return (left_redir(line, *i + 1, data));
	if (flag == 2)
		return (right_redir(line, *i + 1, data));
	if (flag == 3)
		return (double_redir(line, *i + 1, data));
	return (line);
}
