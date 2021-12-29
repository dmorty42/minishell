/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bprovolo <bprovolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:00:18 by dmorty            #+#    #+#             */
/*   Updated: 2021/12/28 22:42:35 by bprovolo         ###   ########.fr       */
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
# define LEFT 1
# define RIGHT 2
# define X_RIGHT 3

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				flag;
}	t_env;

typedef struct s_red
{
	int	r_num;
	int	r_fd;
	int	l_num;
	int	l_fd;
	int	x_num;
	int	x_fd;
}	t_red;

typedef struct s_her
{
	int	is_heredoc;
	int	fd[2];
}	t_her;

typedef struct s_node
{
	t_env			*env_lst;
	t_red			r;
	char			**arg;
	char			**path;
	char			**cmd;
	char			**temp;
	int				cmd_num;
	int				pipe_num;
	int				is_pipe;
	int				**fd;
	char			**env_exp;
	char			*declare_exp;
	struct s_node	*next;
	t_env			*temp_env;
	t_her			her;
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
void	cycle_clean(t_node *data, int flag);
void	execute_cmd(t_node *data, char **env);
//redirect
char	*ft_redirect(char *line, int *i, t_node *data);
int		check_red(char *line, int j);
void	add_redir(t_red *temp, t_node *data);
void	opening_file(char *file, t_node *data, int flag);
char	*parser_redir(char *line, t_node *data);
char	*ft_heredoc(char *line, int i, t_node *data);
//pipes
void	check_pipe(t_node *data, int i);
void	execute_pipe(t_node *data, char **env);
void	pipe_dup(t_node *data);
//ilnurjan
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
void	pwd_f(void);
int		buildin_1(t_node *data);
void	cmd_cd(t_node *data);
t_node	*ft_lstnew_i(int content);
t_env	*ft_lstnew_env(void);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	unset_f(t_node *data);
void	export_f(t_node *data);
void	export_f2(t_node *data);
void	ft_declare(t_node *data);
void	env_f(t_node *data);
void	exit_f(t_node *data);
unsigned long long	ft_atoi_long(const char *str);
//ilnurjan
#endif