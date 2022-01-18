/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:22:37 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/18 19:47:04 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**export_malloc(t_env *tmp, int i, t_node *data)
{
	tmp = data->env_lst;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return ((char **)malloc(sizeof(char *) * (i + 1)));
}
