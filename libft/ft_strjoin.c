/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 21:28:07 by dmorty            #+#    #+#             */
/*   Updated: 2021/11/08 22:18:09 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*temp;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (len1 + len2));
	if (temp == NULL)
		return (NULL);
	while (i < len1)
	{
		temp[i] = s1[i];
		i++;
	}
	i = 0;
	while (i <= len2)
	{
		temp[len1 + i] = s2[i];
		i++;
	}
	return (temp);
}
