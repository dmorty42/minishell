/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 21:25:18 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/17 21:20:42 by bprovolo         ###   ########.fr       */
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

void	find_unset(t_node *data, char *ctmp, t_env *tmp, t_env *tmp2)
{
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->key, ctmp))
			break;
		tmp2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (tmp != data->env_lst)
			tmp2->next = tmp->next;
		else
			data->env_lst = data->env_lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

void	unset_f(t_node *data)
{
	int		i;
	int		j;
	char	*ctmp;
	t_env	*tmp;
	t_env	*tmp2;

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
		j = 0;
		tmp = data->env_lst;
		j = ft_strlen(data->cmd[i]);
		ctmp = ft_substr(data->cmd[i], 0, j);
		tmp2 = tmp;
		find_unset(data, ctmp, tmp, tmp2);
		free(ctmp);
	}
}
