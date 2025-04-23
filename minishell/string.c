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
/*
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
	*/

char	*m_trim(char *input)
{
	char	*temp;
	int		length;
	int		start;
	int		end;

	start = 0;
	end = 0;
	length = ft_strlen(input);
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

char	*m_str_cut_to_end(char *str, int start)
{
	char	*temp;
	
	temp = ft_strdup(str + start);
	if (!temp)
		return (NULL);
	free(str);
	return (temp);
}
char	*m_str_concat(char *str1, char *str2)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str1 || !str2)
		return (NULL);
	temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!temp)
		return (free(str1), free(str2), NULL);
	while (str1[++i])
		temp[i] = str1[i];
	while (str2[j])
		temp[i++] = str2[j++];
	temp[i] = '\0';
	return (free(str1), free(str2), temp);
}