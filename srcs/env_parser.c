/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:04:54 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/25 14:35:45 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	key_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

void	ft_parse_path(t_env *temp, t_node *data)
{
	data->path = ft_split(temp->value, ':');
}

t_env	*parse_env(t_node *data, char **str)
{
	int		i;
	int		j;
	t_env	*temp;

	data->env_lst = NULL;
	i = ft_bigstr_len(str);
	while (i--)
	{
		temp = (t_env *)malloc(sizeof(t_env));
		j = key_len(str[i]);
		temp->key = ft_substr(str[i], 0, j);
		temp->value = ft_strdup(str[i] + 1 + j);
		temp->flag = 1;
		if (!ft_strncmp("PATH", temp->key, j))
			ft_parse_path(temp, data);
		temp->next = data->env_lst;
		data->env_lst = temp;
	}
	return (data->env_lst);
}
