/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:54:32 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/20 05:19:22 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*export_value(t_env *tmp, t_node *data, int i, int j)
{
	char	*ctmp;

	ctmp = ft_strdup(&data->cmd[i][j + 1]);
	if (tmp->value)
		tmp->value = ft_strjoin_free(tmp->value, ctmp);
	else
		tmp->value = ft_strdup(&data->cmd[i][j + 1]);
	free(ctmp);
	return (tmp->value);
}

t_env	*find_min(t_env *env, int flag)
{
	t_env	*temp;
	t_env	*min;
	int		diff;

	temp = env;
	min = env;
	diff = 0;
	while (temp)
	{
		if (flag == X_MIN && ft_strcmp(temp->key, min->key) < diff)
			min = temp;
		if (flag == X_MAX && ft_strcmp(temp->key, min->key) > diff)
			min = temp;
		temp = temp->next;
	}
	return (min);
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
