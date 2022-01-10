/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:38:14 by bprovolo          #+#    #+#             */
/*   Updated: 2022/01/10 23:35:48 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	no_params(t_node *data)
{
	data->temp_env = data->env_lst;
	while (data->temp_env && ft_strcmp(data->temp_env->key, "HOME"))
		data->temp_env = data->temp_env->next;
	if (!data->temp_env)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

char	*cmd_cd2(char *cmd)
{
	char	*buf;
	char	*tmp;

	buf = malloc(sizeof(char) * 1000);
	getcwd(buf, 1000);
	tmp = buf;
	buf = ft_strjoin(cmd, tmp);
	free(tmp);
	return (buf);
}

static int	cd_flag(t_node *data, int *flag)
{
	if (!data->cmd[1])
	{
		*flag = no_params(data);
		if (*flag)
			return (1);
	}
	else if (!ft_strcmp(data->cmd[1], "~"))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
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
			temp->value = ft_strdup(path + ft_strlen(str) + 1);
		}
		temp = temp->next;
	}
}

static void	change_dir(t_node *data, int flag, int i)
{
	char	*buf;
	t_node	*new;

	buf = cmd_cd2("OLDPWD=");
	change_pwd("OLDPWD", data, buf);
	new = ft_lstnew_i(1);
	new->cmd = malloc(sizeof(char *) * 3);
	new->cmd[0] = ft_strdup("1");
	new->cmd[1] = buf;
	new->cmd[2] = NULL;
	if (flag)
	{
		if (chdir(data->cmd[1]) == -1)
			ft_putstr_fd(strerror (errno), 2);
	}
	else
		if (chdir(data->env_lst->value + 5) == -1)
			ft_putstr_fd(strerror (errno), 2);
	buf = cmd_cd2("PWD=");
	change_pwd("PWD", data, buf);
	free(new->cmd[1]);
	new->cmd[1] = buf;
	while (new->cmd[i])
		free(new->cmd[i++]);
	free(new->cmd);
	free(new);
}

void	cmd_cd(t_node *data)
{
	DIR		*dir;
	int		flag;

	flag = 1;
	if (cd_flag(data, &flag))
		return ;
	if (flag)
		dir = opendir(data->cmd[1]);
	else
		dir = opendir(data->env_lst->value);
	if ((dir) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (flag)
			ft_putstr_fd(data->cmd[1], 2);
		else
			ft_putstr_fd(data->env_lst->value, 2);
		write(2, " : ", 3);
		ft_putstr_fd(strerror (errno), 2);
		write(2, "\n", 1);
		return ;
	}
	change_dir(data, flag, 0);
	closedir(dir);
}
