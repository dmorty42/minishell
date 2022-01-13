/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 17:00:49 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/12 21:29:44 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*cmd_tmp(t_node *data, int j, int i)
{
	t_env	*tmp;
	char	*ctmp;

	tmp = data->env_lst;
	if (j - 1 >= 0 && data->cmd[i][j - 1] == '+')
		--j;
	while (tmp)
	{
		if (tmp->key[j] == '\0')
		{
			ctmp = ft_substr(data->cmd[i], 0, j);
			if (!ft_strcmp(tmp->key, ctmp))
			{
				free (ctmp);
				break ;
			}
			free(ctmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

static void	export_sub(int j, t_node *data, t_env *tmp, int i)
{
	char	*ctmp;

	if (j - 1 >= 0 && data->cmd[i][j - 1] == '+')
	{
		ctmp = ft_strdup(data->cmd[i] + j + 1);
		tmp->value = ft_strjoin(tmp->value, ctmp);
		free(ctmp);
		return ;
	}
	// if (!tmp->vision)
	// 	if (!ft_strcmp(data->cmd[0], "export"))
	// 		tmp->vision = 1;
	free(tmp->value);
	// tmp->value = ft_strdup(data->cmd[i]);
		// printf("cmd = {%s}", data->cmd[i]);
	return ;
}

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

static void export_equals(t_node *data, int j, int i)
{
	t_env	*tmp = NULL;
	char	*ctmp;
	
	tmp = cmd_tmp(data, j, i);
	if (tmp)
	{
		export_sub(j, data, tmp, i);
		 return ;
	}
	tmp = ft_lstnew_env();
	if (data->cmd[i][j - 1] == '+' && data->cmd[i][j] == '=')
	{
		tmp->key = ft_substr(data->cmd[i], 0, j - 1);
		ctmp = ft_strdup(&data->cmd[i][j + 1]);
		printf("ctmp= %s\n", ctmp);
		printf("tmp1= %s\n", tmp->value);
		if (tmp->value)
			tmp->value = ft_strjoin(tmp->value, ctmp);
		else
			tmp->value = ft_strdup(&data->cmd[i][j + 1]);
		printf("tmp2= %s\n", tmp->value);
		free(ctmp);
	}
	else
	{
		tmp->key = ft_substr(data->cmd[i], 0, j);
		tmp->value = ft_strdup(&data->cmd[i][j + 1]);
	}
	printf("i=%d, key= %s value= %s\n", i, tmp->key, tmp->value);
	tmp->flag = 0;
	if (!ft_strcmp(data->cmd[0], "export"))
		tmp->flag = 1;
	ft_lstadd_back_env(&data->env_lst, tmp);
}

void export_f(t_node *data)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (data->cmd[++i])
	{
		if (check_export(data, i) != 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(data->cmd[i], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
			++i;
			continue ;
		}
		while (data->cmd[i][j] != '=' && data->cmd[i][j])
			++j;
		if (data->cmd[i][j])
			export_equals(data, j, i);
		else
			export_add(data, j, i);
		// i++;
	}
}