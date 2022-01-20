/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 18:50:02 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/20 05:18:04 by dmorty           ###   ########.fr       */
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

t_env	*ft_lstnew_env(void)
{
	t_env	*the_new;

	the_new = (t_env *)malloc(sizeof(t_env));
	if (!the_new)
		return (NULL);
	the_new->next = NULL;
	return (the_new);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (new == NULL)
		return ;
	else if (*lst == NULL || lst == NULL)
		*lst = new;
	else
	{
		ptr = ft_lstlast_env(*lst);
		ptr->next = new;
	}
}

int	ft_env_size(t_env *env)
{
	t_env	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
