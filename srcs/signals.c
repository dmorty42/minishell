/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:33:10 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/19 19:56:18 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_for(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	sig_for2(int sig)
{
	(void)sig;
	g_exit_status = 131;
	printf("Quit: 3\n");
}

void	signal_work(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_work2(void)
{
	signal(SIGINT, sig_for);
	signal(SIGQUIT, sig_for2);
}
