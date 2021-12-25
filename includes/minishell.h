/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:00:18 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/25 17:13:05 by bprovolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
//ilnurjan
# include <dirent.h>
# include <errno.h>
//ilnurjan

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				flag;
}	t_env;

typedef struct s_red
{
	int				dup_num;
	int				fd;
	struct s_red	*next;
}	t_red;

typedef struct s_node
{
	t_env			*env_lst;
	t_red			*red;
	char			**arg;
	char			**path;
	char			**cmd;
	int				cmd_num;
	struct s_node	*next;
	t_env			*temp_env;
	int				redir_num;
}	t_node;

t_env	*parse_env(t_node *data, char **str);
int		ft_bigstr_len(char **str);
void	check_syntax(char *line);
char	*space_prepare(char *line);
void	parser(char *line, t_env *env, t_node *data);
char	*ft_gap(char *line, int *i);
char	*ft_gap2(char *line, int *i, t_env *env);
char	*ft_slash(char *line, int *i);
char	*ft_dollar(char *line, int *i, t_env *env);
char	*ft_del_space(char *line, int *i);
int		ft_bigstr_len(char **str);
int		ifkey(char c);
char	*find_value(char *key, t_env *env);
char	**two_dim_work(char **array, char *str, int *j);
void	check_semicolon(char *line, t_node *data);
//redirect
char	*ft_redirect(char *line, int *i, t_node *data);
int		check_red(char *line, int j);
void	add_redir(t_red *temp, t_node *data);
void	opening_file(char *file, t_node *data, int flag);
//ilnurjan
int		ft_strcmp(const char *s1, const char *s2);
void	pwd_f(void);
int		buildin_1(t_node *data);
void	cmd_cd(t_node *data);
t_node	*ft_lstnew_i(int content);
void	unset_f(t_node *data);
void	env_f(t_node *data);
//ilnurjan
#endif