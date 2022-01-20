/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:00:18 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/20 05:08:55 by dmorty           ###   ########.fr       */
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
# include "signal.h"
# include <dirent.h>
# include <errno.h>
# define LEFT 1
# define RIGHT 2
# define X_RIGHT 3
# define X_MAX 0	
# define X_MIN 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				flag;
	int				eq;
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
	char			*home;
	int				exit_status;
	int				cmd_num;
	int				pipe_num;
	int				is_pipe;
	int				is_err;
	int				**fd;
	char			**env_exp;
	char			*declare_exp;
	struct s_node	*next;
	t_env			*temp_env;
	t_her			her;
}	t_node;

int	g_exit_status;

void				rl_replace_line(const char *a, int b);
t_env				*parse_env(t_node *data, char **str);
int					ft_bigstr_len(char **str);
void				check_syntax(char *line, t_node *data);
char				*space_prepare(char *line);
void				parser(char *line, t_node *data);
char				*ft_gap(char *line, int *i);
char				*ft_gap2(char *line, int *i, t_env *env);
char				*ft_slash(char *line, int *i);
char				*ft_dollar(char *line, int *i, t_env *env);
char				*ft_exsts(char *line, int *i);
char				*ft_del_space(char *line, int *i);
int					ft_bigstr_len(char **str);
int					ifkey(char c);
char				*find_value(char *key, t_env *env);
char				**two_dim_work(char **array, char *str, int *j);
void				check_semicolon(char *line, t_node *data);
void				cycle_clean(t_node *data, int flag);
void				execute_cmd(t_node *data, char **env);
char				**lst_to_array(t_node *data);
void				signal_work(void);
void				signal_work2(void);
void				sig_handler(int sig);
void				parse_path(t_node *data);
char				*ft_redirect(char *line, int *i, t_node *data);
int					check_red(char *line, int j);
void				add_redir(t_red *temp, t_node *data);
void				opening_file(char *file, t_node *data, int flag);
char				*parser_redir(char *line, t_node *data);
char				*ft_heredoc(char *line, int i, t_node *data);
void				opening_file(char *file, t_node *data, int flag);
void				change_out(t_node *data, int *fd);
void				check_pipe(t_node *data, int i);
void				execute_pipe(t_node *data, char **env);
void				pipe_dup(t_node *data);
void				close_fd(t_node *data);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin_free(char *s1, char *s2);
void				pwd_f(t_node *data);
int					buildin_1(t_node *data);
void				cmd_cd(t_node *data);
t_node				*ft_lstnew_i(int content);
t_env				*ft_lstnew_env(void);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				unset_f(t_node *data, int i);
void				export_f(t_node *data);
void				export_f2(t_node *data);
void				export_add(t_node *data, int j, int i);
void				ft_declare(t_node *data);
void				env_f(t_node *data);
void				exit_f(t_node *data);
void				find_direct(t_node *data, char **path);
char				*find_old_pwd(t_node *data);
unsigned long long	ft_atoi_long(const char *str);
char				**export_malloc(t_env *tmp, int i, t_node *data);
char				*export_value(t_env *tmp, t_node *data, int i, int j);
void				again_check_quotes(char *line, int *i);
int					check_path(t_node *data);
t_env				*find_min(t_env *env, int flag);
int					ft_env_size(t_env *env);
void				export_err(char *str);
#endif