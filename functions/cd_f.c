/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_f.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 14:38:14 by bprovolo          #+#    #+#             */
/*   Updated: 2021/12/25 15:56:52 by bprovolo         ###   ########.fr       */
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
		// data->ff_exit = 1;
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
	// else if (data->cmd[1][0] == '-' && !data->cmd[1][1])
	// {
	// 	if (OldDir(data, mini))
	// 		return (1);
	// }
	// // 	 else if(ft_strcmp(data->cmd[1], "~"))

	// 	|| !data->cmd[1][1]))
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		// data->ff_exit = 1;
		return (1);
	}
	// 	else if (!data->cmd[1])
	// 		printf("flag %d  int\n", *flag);
	// printf("%s\n", data->cmd[1]);
	
	return (0);
}

static void	change_dir(t_node *data, int flag, int i)
{
	char	*buf;
	t_node	*new;

	buf = cmd_cd2("OLDPWD=");
	new = ft_lstnew_i(1);
	new->cmd = malloc(sizeof(char *) * 3);
	new->cmd[0] = ft_strdup("1");
	new->cmd[1] = buf;
	new->cmd[2] = NULL;
	// export_f(mini, new, 1);
	if (flag)
	{
		if (chdir(data->cmd[1]) == -1)
			ft_putstr_fd(strerror (errno), 2);
	}
	else
		if (chdir(data->env_lst->value + 5) == -1)
			ft_putstr_fd(strerror (errno), 2);
	buf = cmd_cd2("PWD=");
// printf("%s\n",  data->env_lst->value + 5);
	free(new->cmd[1]);
	new->cmd[1] = buf;
	// export_f(mini, new, 1);
	while (new->cmd[i])
		free(new->cmd[i++]);
	free(new->cmd);
	free(new);
}

void	cmd_cd(t_node *data)
{
	DIR		*Dir;
	int		flag;

	flag = 1;
	// data->ff_exit = 0;
	if (cd_flag(data, &flag))
		return ;
	if (flag)
		Dir = opendir(data->cmd[1]);
	else
		Dir = opendir(data->env_lst->value);
	if ((Dir) == NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		if (flag)
			ft_putstr_fd(data->cmd[1], 2);
		else
			ft_putstr_fd(data->env_lst->value, 2);
		write(2, " : ", 3);
		ft_putstr_fd(strerror (errno), 2);
		write(2, "\n", 1);
		//  data->ff_exit = 1;
		return ;
	}
	change_dir(data, flag, 0);
	closedir(Dir);
}