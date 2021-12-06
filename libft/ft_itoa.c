/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:27:51 by dmorty            #+#    #+#             */
/*   Updated: 2021/04/24 21:44:57 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int c)
{
	int	len;

	len = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		c = -c;
		len++;
	}
	while (c)
	{
		c /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*temp;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	if (n < 0)
	{
		temp[0] = '-';
		n = -n;
	}
	if (n == 0)
	{
		temp[len - 1] = '0';
	}
	temp[len] = '\0';
	while (n)
	{
		temp[--len] = n % 10 + '0';
		n /= 10;
	}
	return (temp);
}
