/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_f2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 20:11:51 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/20 18:03:47 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export_put_msg(t_env *temp, int fd_out, int *i)
{
	if (temp->flag == *i)
	{
		write(fd_out, "declare -x ", 11);
		ft_putstr_fd(temp->key, fd_out);
		if (temp->eq == 1)
			write(fd_out, "=\"", 2);
		if (temp->value)
			ft_putstr_fd(temp->value, fd_out);
		if (temp->eq == 1)
			write(fd_out, "\"", 1);
		write(fd_out, "\n", 1);
		*i += 1;
	}
}

void	export_f2(t_node *data)
{
	int		i;
	int		x;
	t_env	*temp;
	int		fd_out;

	temp = data->env_lst;
	i = 1;
	fd_out = 1;
	x = 0;
	change_out(data, &fd_out);
	while (i < ft_env_size(data->env_lst) + 1)
	{
		if (x > 1000)
		{
			i++;
			x = 0;
		}
		export_put_msg(temp, fd_out, &i);
		temp = temp->next;
		if (!temp)
			temp = data->env_lst;
		x++;
	}
}

void	export_err(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}
