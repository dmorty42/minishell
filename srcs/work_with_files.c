/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:20:26 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/21 20:33:20 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	opening_file(char *file, t_node *data, int flag)
{
	t_red	*temp;

	temp = (t_red *)malloc(sizeof(t_red));
	if (flag == 1)
	{
		temp->dup_num = 0;
		temp->fd = open(file, O_RDONLY, 0644);
	}
	if (flag == 2)
	{
		temp->dup_num = 1;
		temp->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (flag == 3)
	{
		temp->dup_num = 1;
		temp->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	add_redir(temp, data);
}
