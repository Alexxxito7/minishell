/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:39:56 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/14 12:39:58 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	m_free(char **str)
{
	int	i;

	i = 0;
	if (!str )
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

void	m_print_status(int status)
{
	if (status == 1)
		write(2, "Error: General \n", 17);
	if (status == 2)
		write(2, "Error: Memory allocation fail \n", 31);
	if (status == 3)
		write(2, "Error: Syntax \n", 15);
	if (status == 4)
		write(2, "Error: Permission denied \n", 26);
	if (status == 5)
		write(2, "Error: Command not found \n", 26);
	if (status == 6)
		write(2, "Error: No such file/dir \n", 25);
	if (status == 7)
		write(2, "Error: Pipe/Fork \n", 18);
	if (status == 128)
		write(2, "Error: Invalid argument \n", 25);
	/*
		Signal Termination	128 + N	Command killed by signal N (e.g., SIGINT → 130, SIGSEGV → 139).
		Builtin Command Error	126	Builtin command failed (e.g., invalid export syntax).
		Executable Not Runnable	126	File isn’t executable (e.g., ./text_file without +x).
		Invalid Exit Argument	128	exit called with a non-integer argument (e.g., exit abc).
		Out-of-Range Exit	255	exit argument > 255 (e.g., exit 300).
	*/
}

void	m_exit_error(t_data *data, int status)
{
	m_print_status(status);
	if (data)
		m_free_data(data);
	rl_clear_history();
	exit(status);
}
