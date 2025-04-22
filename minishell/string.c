/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:06 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/14 12:43:07 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_found_command(char *str)
{
	(void)str;
	// char	**commands;
	// //int		i;
	
	// commands = (char *[]){"echo","cd","pwd","export",
	// 	"unset", "env", "exit", "<", ">", ">>", "<<", NULL};
	//i = 0;
	
	return (0);
}

char	*m_trim(char *input)
{
	char	*temp;
	int		length;
	int		start;
	int		end;

	start = 0;
	end = 0;
	lenght = ft_strlen(input);
	while (input[start] == ' ')
		start++;
	while (input[length - end - 1] == ' ')
		end++;
	temp = ft_substr(input, start, length - end);
	free(input);
	return (temp);
}

int	m_count_qoute(char *input)
{
	bool	val;
	int		i;
	int		count;
	char	c;

	i = 0;
	val = true;
	count = 0;
	while (input[i])
	{
		if (val && (input[i] == '\'' || input[i] == '\"'))
		{
			count++;
			val = !val;
			c = input[i];
		}
		else if (!val && input[i] == c)
			count++;
		i++;
	}
	return (count % 2);
}
