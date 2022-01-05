/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 22:23:15 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/05 14:52:59 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*parser_redir(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			line = ft_heredoc(line, i, data);
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			line = ft_redirect(line, &i, data);
		}
	}
	return (line);
}
