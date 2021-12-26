/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:50:02 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/23 21:08:44 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*ft_lstnew_i(int content)
{
	t_node	*the_new;

	the_new = (t_node *)malloc(sizeof(t_node));
	if (!the_new)
		return (NULL);
	the_new->cmd_num = content;
	the_new->next = NULL;
	return (the_new);
}
