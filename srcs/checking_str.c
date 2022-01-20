/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:19:11 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/20 05:26:43 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_bigstr_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*find_value(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strcmp(key, temp->key))
		{
			free(key);
			return (temp->value);
		}
		temp = temp->next;
	}
	free(key);
	return ("");
}

char	*ft_del_space(char *line, int *i)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(line, 0, *i);
	temp2 = ft_strdup(line + *i + 1);
	temp = ft_strjoin_free(temp, temp2);
	free(line);
	free(temp2);
	return (temp);
}

int	check_path(t_node *data)
{
	if (!data->path)
	{
		g_exit_status = 127;
		printf("minishell: %s: No such file or directory\n", data->cmd[0]);
		exit(127);
	}
	return (1);
}
