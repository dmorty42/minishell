/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/18 16:56:45 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	quotes_add_2(t_node *data, int i, int j)
{
	char	*tmp;
	char	*tmp2;

	if (data->env_lst->key && data->env_lst->value)
	{
		tmp = ft_substr(data->env_exp[i], 0, j + 1);
		tmp2 = data->env_exp[i];
		data->env_exp[i] = ft_strdup(tmp2 + j + 1);
		free(tmp2);
		tmp2 = data->env_exp[i];
		data->env_exp[i] = ft_strjoin("\"", tmp2);
		data->env_exp[i] = ft_strjoin_free(data->env_exp[i], "\"");
		free(tmp2);
		tmp2 = data->env_exp[i];
		data->env_exp[i] = ft_strjoin_free(tmp, tmp2);
		free(tmp2);
	}
}

static void	quotes_add(t_node *data)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (data->env_exp[++i])
	{
		j = 0;
		while (data->env_exp[i][j] != '=' && data->env_exp[i][j])
			++j;
		if (!data->env_exp[i][j])
			continue ;
		quotes_add_2(data, i, j);
	}
}

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
	quotes_add(data);
	ft_declare(data);
}

void	export_f2(t_node *data)
{
	int		i;
	t_env	*tmp;
	char	*ctmp;

	ctmp = NULL;
	i = 0;
	tmp = data->env_lst;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	data->env_exp = (char **)malloc(sizeof(char *) * (i + 1));
	tmp = data->env_lst;
	i = 0;
	while (tmp)
	{
		if (tmp->flag == 0)
		{
			if (tmp->key && tmp->value)
			{
				ctmp = ft_strjoin(tmp->key, "=");
				data->env_exp[i] = ft_strjoin_free(ctmp, tmp->value);
			}
			else
				data->env_exp[i] = ft_strdup(tmp->key);
			i++;
			tmp = tmp->next;
		}
	}
	data->env_exp[i] = NULL;
	export_f2_next(data);
	data->exit_status = 0;
}
