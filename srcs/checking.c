/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:29:07 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/09 15:17:45 by dmorty           ###   ########.fr       */
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

void	check_double_semi(char *line, t_node *data)
{
	int	i;

	i = -1;
	while (line[++i + 1])
	{
		if (line[i] == ';' && line[i + 1] == ';')
		{
			printf("minishell: syntax error near unexpected token ';;'\n");
			data->is_err += 1;
		}
	}
}

void	check_syntax(char *line, t_node *data)
{
	char	err;

	if (check_quotes(line) == -1)
	{
		printf("error: unclosed quotes\n");
		data->is_err += 1;
	}
	err = check_pipe_syntax(line);
	if (err != 'O')
	{
		printf("syntax error near unexpected token '%c'\n", err);
		data->is_err += 1;
	}
	check_double_semi(line, data);
}
