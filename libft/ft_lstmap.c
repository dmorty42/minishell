/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:28:21 by dmorty            #+#    #+#             */
/*   Updated: 2021/09/09 20:03:30 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp_lst;
	t_list	*temp_elem;

	if (!del || !f)
		return (NULL);
	temp_lst = NULL;
	while (lst)
	{
		temp_elem = ft_lstnew(f(lst->content));
		if (!temp_elem)
		{
			while (temp_lst)
			{
				temp_elem = temp_lst->next;
				(*del)(temp_lst->content);
				free(temp_lst);
				temp_lst = temp_elem;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&temp_lst, temp_elem);
		lst = lst->next;
	}
	return (temp_lst);
}
