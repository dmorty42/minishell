/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:13:00 by dmorty            #+#    #+#             */
/*   Updated: 2021/11/09 18:08:26 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count(char *line)
{
	int	i;
	int	num;

	i = -1;
	num = 0;
	while (line[++i])
	{
		if (line[i] != ' ' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			num += 1;
	}
	return (num);
}

int	before_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	return (i);
}

char	**super_split(char *line)
{
	int		i;
	int		j;
	int		x;
	char	**temp;

	i = 0;
	j = 0;
	temp = (char **)malloc(sizeof(char *) * (ft_count(line) + 1));
	// printf("count [%d]\nline [%s]\n", ft_count(line), line);
	while (line[j])
	{
		x = -1;
		while (line[j] == ' ')
			j++;
		temp[i] = (char *)malloc(before_space(line + j) + 1);
		while (line[j] != ' ' && line[j])
		{
			temp[i][++x] = line[j];
			j++;
		}
		temp[i][++x] = 0;
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

char	**parse(char *line)
{
	char	**temp;
	int		i;
	int		first;

	first = 0;
	i = 0;
	temp = super_split(line);
	// printf("%s\n", line);
	return (temp);
}

void	ft_execute(char *com, char **exec, char **envp)
{

	printf("%s + 1\n", com);
	// for (int i = 0; exec[i] != 0; i++)
	// 	printf("%s\n", exec[i]);
	// pid = fork();
	// if (pid == 0)
		execve(com, exec, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		i;
	char	*com;
	char	**exec;

	i = -1;
	argc = 0;
	// execve("/bin/cat", argv + 1, envp);
	// perror("execve");
	while (1)
	{
		line = readline(ft_strjoin(argv[0], " "));
		add_history(line);
		// printf("line [%s]\n", line);
		exec = parse(line);
		printf("first [%s]\nsecond [%s]\nthird [%s]\n", exec[0], exec[1], exec[2]);
		com = ft_strjoin("/bin/", exec[0]);
		// printf("com [%s]\n", com);
		execve(com, exec, envp);
		perror("execve");

	}
	// com = (char **)malloc(sizeof(char *) * 10);
	// com[0] = "-n";
	// com[1] = "-n hello world";
	// com[2] = NULL;
}
