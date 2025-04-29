/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:43:06 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:50 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*m_trim(char *input)
{
	char	*temp;
	int		length;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!input)
		return (NULL);
	length = ft_strlen(input);
	while (input[start] == ' ' || input[start] == '\t')
		start++;
	while (input[length - end - 1] == ' ' || input[start] == '\t')
		end++;
	temp = ft_substr(input, start, length - end);
	free(input);
	return (input = NULL, temp);
}

char	*m_cut_until_end(char *str, int start)
{
	char	*temp;

	if (str == NULL)
		return (NULL);
	temp = ft_substr(str, start, ft_strlen(str));
	free(str);
	if (!temp)
		return (NULL);
	return (str = NULL, temp);
}

char	*m_str_concat(char *str1, char *str2)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str1 || !str2)
	{
		if (str2)
			return (free(str2), str2 = NULL, NULL);
		else if (str1)
			return (free(str1), str1 = NULL, NULL);
		else
			return (NULL);
	}
	temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!temp)
		return (free(str1), free(str2), str1 = NULL, str2 = NULL, NULL);
	while (str1[++i])
		temp[i] = str1[i];
	while (str2[j])
		temp[i++] = str2[j++];
	temp[i] = '\0';
	(free(str1), free(str2));
	return (str1 = NULL, str2 = NULL, temp);
}
