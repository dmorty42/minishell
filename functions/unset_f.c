/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:25:18 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/14 03:05:38 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int check_unset(t_node *data, int i)
{
	int j;

	j = 1;
	if (!ft_isalpha(data->cmd[i][0]) && data->cmd[i][0] != '_')
		return (i);
	while (data->cmd[i][j] != '=' && data->cmd[i][j] != '+'
		&& data->cmd[i][j])
	{
		if (!ft_isalnum(data->cmd[i][j]) && data->cmd[i][j] != '_')
			return (i);
		++j;
	}
	if (data->cmd[i][j] == '+' && data->cmd[i][j + 1] != '_')
		return (i);
	return (0);
}

// static void unset_f2_next(t_env *tmp1, t_env *tmp2, t_node *data, char *ctmp)
// {
// 	while (tmp1)
// 	{
// 		if (ft_strcmp(tmp1->key, ctmp) == 0)
// 			break ;
// 		tmp2 = tmp1;
// 		tmp1 = tmp1->next;
// 	}
// 	if (tmp1)
// 	{
// 		// if (tmp1 != data->)
// 		data->env_lst = data->env_lst->next;
// 		free(tmp1->key);
// 		free(tmp1->value);
// 		free(tmp1);
// 	}
// }

void	find_unset(t_node *data, int i)
{
	t_env	*temp1;
	t_env	*temp2;

	temp1 = data->env_lst;
	while (temp1->next)
	{
		if (!strcmp(data->cmd[i], temp1->next->key))
		{
			temp2 = temp1->next->next;
			free(temp1->next->key);
			free(temp1->next->value);
			free(temp1->next);
			temp1->next = temp2;
		}
		temp1 = temp1->next;
	}
}

void	unset_f(t_node *data)
{
	int		i;

	i = 0;
	while (data->cmd[++i])
	{
		if (check_unset(data, i))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(data->cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			continue ;
		}
		find_unset(data, i);
	}
}
