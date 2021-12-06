/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:52:44 by dmorty            #+#    #+#             */
/*   Updated: 2021/04/21 14:48:30 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n > 0)
	{
		*(char *)dest = *(char *)src;
		if (*(char *)dest == (char)c)
		{
			dest++;
			return (&*dest);
		}
		dest++;
		src++;
		n--;
	}
	return (NULL);
}
