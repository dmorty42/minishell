/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 00:33:10 by dmorty            #+#    #+#             */
/*   Updated: 2022/01/13 19:53:56 by dmorty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int sig)
{
	(void)sig;
	// g_parms.gexit = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_work(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
