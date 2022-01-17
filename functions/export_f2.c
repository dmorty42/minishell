/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/17 20:51:52 by bprovolo         ###   ########.fr       */
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
