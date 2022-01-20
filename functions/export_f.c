/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:00:49 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/20 05:20:56 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_export(t_node *data, int i)
{
	int	y;

	y = 1;
	if (!ft_isalpha(data->cmd[i][0]) && data->cmd[i][0] != '-')
		return (i);
	while (data->cmd[i][y] != '=' && data->cmd[i][y] != '+' && data->cmd[i][y])
	{
		if (!ft_isalnum(data->cmd[i][y]) && data->cmd[i][y] != '_')
			return (i);
		++y;
	}
	if (data->cmd[i][y] == '+' && data->cmd[i][y + 1] != '=')
		return (i);
	return (0);
}

static void	export_equals(t_node *data, int j, int i, int e)
{
	t_env	*tmp;
	int		x;

	tmp = (t_env *)malloc(sizeof(t_env));
	tmp->key = ft_substr(data->cmd[i], 0, j);
	tmp->flag = ft_env_size(data->env_lst) + 1;
	tmp->next = NULL;
	tmp->eq = e;
	j += 1;
	x = j;
	if (data->cmd[i][j])
	{
		while (data->cmd[i][j])
			j++;
		tmp->value = ft_substr(data->cmd[i], x, j - x);
	}
	else
		tmp->value = NULL;
	ft_lstadd_back_env(&data->env_lst, tmp);
}

int	rewrite_env(t_node *data, t_env *env, int i)
{
	int		j;
	char	*temp;

	j = 0;
	while (data->cmd[i][j] && data->cmd[i][j] != '=' && data->cmd[i][j] != '+')
		j++;
	if (data->cmd[i][j] == '=' && data->cmd[i][j + 1])
	{
		free(env->value);
		env->value = ft_substr(data->cmd[i], j + 1, \
			ft_strlen(data->cmd[i]) - j + 1);
	}
	else if (data->cmd[i][j] == '+' && data->cmd[i][j + 2])
	{
		temp = ft_substr(data->cmd[i], j + 2, ft_strlen(data->cmd[i]) - j + 1);
		env->value = ft_strjoin_free(env->value, temp);
		free(temp);
	}
	else
	{
		free(env->value);
		env->value = NULL;
	}
	env->eq = 1;
	return (0);
}

int	overwrite_env(t_node *data, int i)
{
	t_env	*temp;
	char	*str;
	int		j;

	j = 0;
	while (data->cmd[i][j] && data->cmd[i][j] != '=' && data->cmd[i][j] != '+')
		j++;
	temp = data->env_lst;
	str = ft_substr(data->cmd[i], 0, j);
	while (temp)
	{
		if (!ft_strcmp(str, temp->key))
		{
			free(str);
			return (rewrite_env(data, temp, i));
		}
		temp = temp->next;
	}
	free(str);
	return (1);
}

void	export_f(t_node *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmd[++i])
	{
		j = 0;
		if (check_export(data, i) != 0)
		{
			export_err(data->cmd[i]);
			g_exit_status = 1;
			continue ;
		}
		if (overwrite_env(data, i))
		{
			while (data->cmd[i][j] && data->cmd[i][j] != '=')
				++j;
			if (data->cmd[i][j])
				export_equals(data, j, i, 1);
			else
				export_equals(data, j, i, 0);
		}
		g_exit_status = 0;
	}
}
