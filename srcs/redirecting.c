/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:23:15 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/19 01:26:15 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parser_redir(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (data->is_err == 0 && line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			i++;
			while (line[i] && (line[i] != '\'' || line[i] != '\"'))
				i++;
		}
		if (line[i] == '<' && line[i + 1] == '<')
		{
			line = ft_heredoc(line, i, data);
			i = -1;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			line = ft_redirect(line, &i, data);
			i = -1;
		}
	}
	return (line);
}
