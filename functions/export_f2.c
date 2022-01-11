/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/11 21:10:16 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	export_f2_nn(t_node *data, int i, int j)
{
	char	*tmp;

	while (data->env_exp[i][j] == data->env_exp[i + 1][j])
		++j;
	if (data->env_exp[i][j] > data->env_exp[i + 1][j]
		&& data->env_exp[i][j] != '=' && data->env_exp[i + 1][j] != '='
		&& data->env_exp[i][j] && data->env_exp[i + 1][j])
	{
		tmp = data->env_exp[i];
		data->env_exp[i] = data->env_exp[i + 1];
		data->env_exp[i + 1] = tmp;
		i = 0;
	}
	else if (data->env_exp[i + 1][j] == '=' || !data->env_exp[i + 1][j])
	{
		tmp = data->env_exp[i];
		data->env_exp[i] = data->env_exp[i + 1];
		data->env_exp[i + 1] = tmp;
		i = 0;
	}
	else
		i++;
	return (i);
}

static void	export_f2_next(t_node	*data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (data->env_exp[i + 1])
	{
		j = 0;
		if (data->env_exp[i][j] > data->env_exp[i + 1][j])
		{
			tmp = data->env_exp[i];
			data->env_exp[i] = data->env_exp[i + 1];
			data->env_exp[i + 1] = tmp;
			i = 0;
		}
		else if (data->env_exp[i][j] == data->env_exp[i + 1][j])
			i = export_f2_nn(data, i, j);
		else
			++i;
	}
}

void	export_f2(t_node *data)
{
	int		i;
	t_env	*tmp;
	char	*ctmp;

	ctmp = 0;	
	i = 0;
	tmp = data->env_lst;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	data->env_exp = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	tmp = data->env_lst;
	
	while (tmp)
	{
		ctmp = ft_strjoin(tmp->key, "=\"");
		data->env_exp[i] = ft_strjoin(ctmp, tmp->value);
		tmp = tmp->next;
		i++;
	}
	data->env_exp[i] = NULL;
	export_f2_next(data);
}
