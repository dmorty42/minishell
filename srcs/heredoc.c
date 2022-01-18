/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:10:55 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/18 18:42:48 by dmorty           ###   ########.fr       */
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

char	*more_lines(char *stop, t_node *data)
{
	char	*temp;

	temp = NULL;
	temp = readline("> ");
	if (!temp || ft_strcmp(temp, stop) == 0)
	{
		free(temp);
		return (NULL);
	}
	temp = here_parse(temp, data);
	write(data->her.fd[1], temp, ft_strlen(temp));
	write(data->her.fd[1], "\n", 1);
	return (temp);
}

char	*trim_her(char *line)
{
	int		i;
	char	*temp[2];

	i = 0;
	while (line[i] != '<')
		i++;
	if (i > 0)
		temp[0] = ft_substr(line, 0, i - 1);
	else
		temp[0] = ft_strdup("");
	while (line[i] == '<' || line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	if (line[i])
		temp[1] = ft_strdup(line + i);
	else
		temp[1] = ft_strdup("");
	temp[0] = ft_strjoin_free(temp[0], temp[1]);
	free(temp[1]);
	free(line);
	return (temp[0]);
}

char	*ft_heredoc(char *line, int i, t_node *data)
{
	char	*temp;
	int		j;
	char	*stop;
	char	*temp1;

	data->her.is_heredoc = 1;
	temp1 = ft_strdup(" ");
	pipe(data->her.fd);
	while (line[i] && (line[i] == '<' || line[i] == ' '))
		i++;
	j = i;
	while (line[i] && line[i] != ' ' && line[j] != '\t')
		i++;
	stop = ft_substr(line, j, i - j);
	while (temp1 && ft_strcmp(temp1, stop))
	{
		free(temp1);
		temp1 = more_lines(stop, data);
	}
	close(data->her.fd[1]);
	temp = trim_her(line);
	free(temp1);
	temp1 = ft_strjoin_free(temp, " ");
	free(stop);
	return (temp1);
}
