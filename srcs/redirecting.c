/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:23:15 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/21 07:09:57 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_file_name(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	temp = ft_substr(line, 0, i);
	free(line);
	return (temp);
}

int	check_red(char *line, int j)
{
	if (line[j] == '<')
		return (1);
	if (line[j] == '>' && line[j + 1] != '>')
		return (2);
	else
		return (3);
}

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

char	*just_redir(char *line, t_node *data, int flag)
{
	char	*temp;
	t_red	*tmp_red;

	tmp_red = (t_red *)malloc(sizeof(t_red));
	if (flag == 1)
		temp = left_redir(line, tmp_red)
// 	if (flag == 2)
// 	else
// 	temp = ft_strdup(line + *j);
// 	if (flag == 1)
// 	{
// 		tmp_red->dup_num = 0;
// 		tmp_red->fd = open(ft_file_name(temp), O_RDONLY, 0644);
// 	}
// 	if (flag == 2)
// 	{
// 		tmp_red->dup_num = 1;
// 		tmp_red->fd = open(ft_file_name(temp), O_WRONLY | \
// 							O_CREAT | O_TRUNC, 0644);
// 	}
// 	if (flag == 3)
// 	{
// 		tmp_red->dup_num = 1;
// 		tmp_red->fd = open(ft_file_name(temp), O_WRONLY | \
// 							O_CREAT | O_APPEND, 0644);
// 	}
// 	tmp_red->next = NULL;
// 	add_redir(tmp_red, data);
	return (temp);
}

char	*ft_redirect(char *line, int *i, t_node *data)
{
	char	*temp;
	char	*temp1;
	int		j;
	int		flag;

	j = *i;
	data->redir_num += 1;
	flag = check_red(line, j);
	temp = ft_substr(line, 0, j);
	temp1 = ft_strdup(line + *i + 1);
	printf("%s\n", temp1);
	temp1 = just_redir(temp1, data, flag);
	// // while (line[j] != ' ' && line[j])
	// // 	j++;
	// temp1 = ft_strdup(temp1 + j - *i);
	// temp = ft_strjoin(temp, temp1);
	// *i += 1;
	// printf("[%c]+[%c]+[%c]\n", temp[*i - 1], temp[*i], temp[*i+1]);
	// printf("line = [%s]\n", temp);
	return (temp);
}

// char *ft_redirect(char *line, int *i, t_node *data)
// {
// 	if (line[*i] == '>' && line[*i + 1] != '>')
// 		return ()
// }