/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:10:55 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/24 00:32:21 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*here_parse(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\\')
			line = ft_slash(line, &i);
		if (line[i] == '$')
			line = ft_dollar(line, &i, data->env_lst);
	}
	return (line);
}

char	*ft_heredoc(char *line, int i, t_node *data)
{
	char	*temp;
	int		j;
	char	*stop;
	char	*temp1;

	j = i + 3;
	temp1 = ft_strdup(" ");
	temp = ft_substr(line, 0, i - 1);
	data->her.is_heredoc = 1;
	pipe(data->her.fd);
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	while (line[i + 2] == ' ')
		i++;
	stop = ft_substr(line, i + 2, j - i);
	while (ft_strcmp(temp1, stop))
	{
		temp1 = readline("> ");
		if (ft_strcmp(temp1, stop) == 0)
			break ;
		temp1 = here_parse(temp1, data);
		write(data->her.fd[1], temp1, ft_strlen(temp1));
		write(data->her.fd[1], "\n", 1);
	}
	close(data->her.fd[1]);
	return (temp);
}
