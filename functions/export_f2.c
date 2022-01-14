/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/14 05:35:28 by dmorty           ###   ########.fr       */
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

// int	lst_size(t_node *data)
// {
// 	int	i;

// 	i = 0;
// 	data->temp_env = data->env_lst;
// 	while (data->temp_env)
// 	{
// 		data->temp_env = data->temp_env->next;
// 		i++;
// 	}
// 	return (i);
// }

// void	export_f2(t_node *data)
// {
// 	int		diff;
// 	int		last;
// 	t_env	*temp1;
// 	t_env	*temp2;
// 	int		len;

// 	diff = 0;
// 	last = 0;
// 	temp2 = data->env_lst;
// 	temp1 = data->env_lst->next;
// 	len = lst_size(data);
// 	while (len)
// 	{
// 		diff = ft_strcmp(temp1->key, temp2->key);
// 		if (temp1->flag == 0 && diff > last)
// 		{
// 			last = diff;
// 			temp2 = temp1;
// 		}
// 		else if (temp1->flag == 0 && diff == 0)
// 		{
// 			temp2->flag = len;
// 			temp2 = data->env_lst;
// 			last = -100;
// 			len--;
// 		}
// 		temp1 = temp1->next;
// 		if (!temp1)
// 			temp1 = data->env_lst;
// 	}
// 	temp1 = data->env_lst;
// 	len = 1;
// 	while (len <= lst_size(data))
// 	{
// 		if (len == temp1->flag)
// 		{
// 			printf("%s%s%s\n", temp1->key, "=", temp1->value);
// 			len++;
// 		}
// 		temp1 = temp1->next;
// 		if (!temp1)
// 			temp1 = data->env_lst;
// 	}
// }
