/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 02:10:55 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/22 02:39:36 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_heredoc(char *line, int i)
{
	char	*cmd;
	char	*stop;
	char	*temp;
	int		j;

	cmd = ft_substr(line, 0, i - 1);
	j = i + 3;
	temp = ft_strdup(" ");
	while (line[j] && line[j] != ' ' && line[j] != '\t')
		j++;
	while (line[i + 2] == ' ')
		i++;
	stop = ft_substr(line, i + 2, j - i);
	stop = ft_strjoin(stop, "\n");
	while (ft_strcmp(temp, stop))
	{
		cmd = ft_strjoin(cmd, temp);
		temp = readline(">");
		temp = ft_strjoin(temp, "\n");
	}
	return (cmd);
}
