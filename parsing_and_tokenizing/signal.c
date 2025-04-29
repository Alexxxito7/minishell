/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:26:58 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:57 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_handler(int sig)
{
	if (sig == SIGINT && g_signal_main)
    {
        write(1, "\n", 1);
        rl_on_new_line(); // Save/Update cursor position (blinking symbol when you write text)
        rl_replace_line("", 0); //Empty current user input
        rl_redisplay(); //Draw new line on the terminal
    }
    else if (sig == SIGQUIT)
		return ;
	else if (sig == SIGINT && !g_signal_main)
		_exit(130);
}

void	signal_setup()
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL); // Ctrl+C
	sigaction(SIGQUIT, &sa, NULL); // Ctrl+
}