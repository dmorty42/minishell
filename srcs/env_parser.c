/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:04:54 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/28 03:58:57 by dmorty           ###   ########.fr       */
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
		temp->flag = 1;
		if (!ft_strncmp("PATH", temp->key, j))
			data->path = ft_split(temp->value, ':');
		temp->next = data->env_lst;
		data->env_lst = temp;
	}
	return (data->env_lst);
}

char	**lst_to_array(t_node *data)
{
	char	**temp;
	t_env	*env;
	int		i;
	int		j;

	env = data->env_lst;
	i = 0;
	j = -1;
	while (env)
	{
		env = env->next;
		i++;
	}
	env = data->env_lst;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	while (++j < i)
	{
		temp[j] = (char *)malloc(ft_strlen(env->key) + ft_strlen(env->value));
		temp[j] = ft_strjoin(env->key, "=");
		temp[j] = ft_strjoin(temp[j], env->value);
		env = env->next;
	}
	temp[j] = NULL;
	return (temp);
}
