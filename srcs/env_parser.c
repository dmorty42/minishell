/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:04:54 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/20 18:05:37 by dmorty           ###   ########.fr       */
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

void	ft_parse_lvl(t_env *temp, char **str, int i, int j)
{
	char	*val;

	val = NULL;
	val = ft_strdup(str[i] + 1 + j);
	temp->value = ft_itoa(ft_atoi(val) + 1);
	free (val);
}

t_env	*find_next(t_env *env, t_env *back)
{
	t_env	*temp;
	t_env	*max;

	temp = env;
	max = find_min(temp, X_MAX);
	while (temp)
	{
		if (ft_strcmp(temp->key, max->key) < 0 \
			&& ft_strcmp(temp->key, back->key) > 0)
			max = temp;
		temp = temp->next;
	}
	return (max);
}

void	sort_env(t_node *data)
{
	t_env	*min;
	t_env	*next;
	int		i;

	i = 2;
	min = find_min(data->env_lst, X_MIN);
	min->flag = 1;
	while (i < ft_env_size(data->env_lst) + 1)
	{
		next = find_next(data->env_lst, min);
		next->flag = i;
		i++;
		min = next;
	}
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
		if (!ft_strcmp("SHLVL", temp->key))
			ft_parse_lvl(temp, str, i, j);
		else
			temp->value = ft_strdup(str[i] + 1 + j);
		temp->flag = 0;
		temp->eq = 1;
		if (!ft_strncmp("HOME", temp->key, ft_strlen(temp->key)))
			data->home = ft_strdup(temp->value);
		temp->next = data->env_lst;
		data->env_lst = temp;
	}
	sort_env(data);
	return (data->env_lst);
}
