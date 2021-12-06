/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:29:07 by dmorty            #+#    #+#             */
/*   Updated: 2021/11/26 19:28:31 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			while (line[++i] != '\'' && line[i])
				if (line[i] == '\\')
					i++;
			if (!line[i])
				return (-1);
		}
		if (line[i] == '\"')
		{
			while (line[++i] != '\"' && line[i])
				if (line[i] == '\\')
					i++;
			if (!line[i])
				return (-1);
		}
	}
	return (0);
}

char	check_pipe_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == ';')
		return (';');
	if (line[i] == '|')
		return ('|');
	return ('O');
}

void	check_syntax(char *line)
{
	char	err;

	if (check_quotes(line) == -1)
	{
		printf("error: unclosed quotes\n");
		exit(EXIT_FAILURE);
	}
	err = check_pipe_syntax(line);
	if (err != 'O')
	{
		printf("syntax error near unexpected token '%c'\n", err);
		exit(EXIT_FAILURE);
	}
}
