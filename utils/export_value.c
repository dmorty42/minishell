/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:54:32 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/18 20:09:32 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*export_value(t_env *tmp, t_node *data, int i, int j)
{
	char	*ctmp;

	ctmp = ft_strdup(&data->cmd[i][j + 1]);
	if (tmp->value)
		tmp->value = ft_strjoin_free(tmp->value, ctmp);
	else
		tmp->value = ft_strdup(&data->cmd[i][j + 1]);
	free(ctmp);
	return (tmp->value);
}
