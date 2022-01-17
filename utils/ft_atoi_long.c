/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 21:37:48 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/16 17:36:49 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned long long	ft_atoi_s(char *viv, int k)
{
	unsigned long long	res;
	unsigned long long	c;

	c = 1;
	res = 0;
	while (k > 0)
	{
		res = res + (viv[k - 1] - 48) * c;
		c = c * 10;
		k--;
		if (res >= 9223372036854775807)
			break ;
	}
	return (res);
}

static void	ft_atoi_check(const char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if ((str[j] < '0' || str[j] > '9') && str[j] != '\0')
		{
			write(2, "minishell: exit: ", 17);
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", 29);
		}	
		j++;
	}
}

unsigned long long	ft_atoi_long(const char *str)
{
	int		m;
	int		s;
	char	cifr[27];

	m = 1;
	s = 0;
	while (((*str > 8) && (*str < 14)) || (*str == 32))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			m = m * -1;
		str++;
	}
	ft_atoi_check(str);
	while ((*str >= '0') && (*str <= '9'))
	{
		cifr[s] = *str;
		str++;
		s++;
	}
	return ((ft_atoi_s(cifr, s) * m));
}
