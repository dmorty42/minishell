/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:38:14 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/14 03:11:04 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_cd2(void)
{
	char	*buf;

	buf = malloc(sizeof(char) * 1000);
	getcwd(buf, 1000);
	return (buf);
}

void	change_pwd(char *str, t_node *data, char *path)
{
	t_env	*temp;

	temp = data->env_lst;
	while (temp)
	{
		if (!strcmp(str, temp->key))
		{
			free(temp->value);
			temp->value = NULL;
			temp->value = ft_strdup(path);
		}
		temp = temp->next;
	}
}

static void	change_dir(t_node *data, char *path)
{
	char	*buf;

	buf = cmd_cd2();
	change_pwd("OLDPWD", data, buf);
	free(buf);
	if (path)
	{
		if (chdir(path) == -1)
			ft_putstr_fd(strerror (errno), 2);
	}
	buf = cmd_cd2();
	change_pwd("PWD", data, buf);
	free(buf);
}

char	*find_old_pwd(t_node *data)
{
	char	*temp;

	temp = NULL;
	data->temp_env = data->env_lst;
	while (data->temp_env)
	{
		if (!ft_strcmp("OLDPWD", data->temp_env->key))
			temp = ft_strdup(data->temp_env->value);
		data->temp_env = data->temp_env->next;
	}
	if (!temp)
	{
		write(2, "OLDPWD not set\n", 15);
		data->is_err += 1;
	}
	return (temp);
}

void	cmd_cd(t_node *data)
{
	DIR		*dir;
	char	*path;

	path = NULL;
	dir = NULL;
	if (!data->cmd[1])
	{
		path = ft_strjoin(data->home, "/");
	}
	else if (!ft_strcmp(data->cmd[1], "-"))
	{
		path = find_old_pwd(data);
		if (path)
		{
			write(2, path, ft_strlen(path));
			write(2, "\n", 1);
		}
	}
	else if (data->cmd[1])
		path = ft_strdup(data->cmd[1]);
	if (path)
		dir = opendir(path);
	if (data->is_err)
	{
		free(path);
		return ;
	}
	if ((dir) == NULL)
	{
		ft_putstr_fd(strerror (errno), 2);
		write(2, "\n", 1);
		free(path);
		return ;
	}
	change_dir(data, path);
	closedir(dir);
	free(path);
}
