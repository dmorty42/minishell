/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/28 22:39:33 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void back_slash2(t_node *data, int i, int j)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(data->env_exp[i], 0, j + 1);
	temp2 = data->env_exp[i];
	data->env_exp[i] = ft_strdup(temp2 + j + 1);
	free(temp2);
	temp2 = data->env_exp[i];
	data->env_exp[i] = ft_strjoin("\"", temp2);
	data->env_exp[i] = ft_strjoin_free(data->env_exp[i], "\"");
	free(temp2);
	temp2 = data->env_exp[i];
	data->env_exp[i] = ft_strjoin_free(temp1, temp2);
	free(temp2);
}

static void back_slash(t_node *data)
{
	int i;
	int j;

	j = 0;
	i = -1;
	while (data->env_exp[++i])
	{
		j = 0;
		while (data->env_exp[i][j] != '=' && data->env_exp[i][j])
			++j;
		if (!data->env_exp[i][j])
			continue ;
		 back_slash2(data, i, j);
	}
}

static int export_f4(t_node *data, int i, int j)
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

static	void export_f3(t_node *data)
{
	int	i;
	int	j;
	char	*ctmp;

	i = 0;
	while (data->env_exp[i + 1])
	{
		j = 0;
		if (data->env_exp[i][j] > data->env_exp[i + 1][j])
		{
			ctmp = data->env_exp[i];
			data->env_exp[i] = data->env_exp[i + 1];
			data->env_exp[i + 1] = ctmp;
			i = 0;
		}
		else if (data->env_exp[i][j] == data->env_exp[i + 1][j])
			i = export_f4(data, i, j);
		else
			++i;
	}
	back_slash(data);
	ft_declare(data);
}

void	export_f2(t_node *data)
{
	int	i;
	t_env	*tmp;
	
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
		if (tmp->flag)
			data->env_exp[i++] = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	data->env_exp[i] = NULL;
	export_f3(data);
}