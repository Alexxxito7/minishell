/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:26:58 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:57 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_add_token_list_back(t_token **list, t_token *new_node)
{
	t_token	*pnt;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	pnt = *list;
	while (pnt->next)
		pnt = pnt->next;
	pnt->next = new_node;
}

t_token	*m_new_token(t_token **list, char *str)
{
	t_token	*new_node;

	str = m_trim(str);
	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_token));
	if (new_node == NULL)
		return (free(str), NULL);
	new_node->next = NULL;
	new_node->i_list = NULL;
	new_node->token = ft_strdup(str);
	if (!new_node->token)
		return (free(str), free(new_node), new_node = NULL, NULL);
	m_add_token_list_back(list, new_node);
	return (free(str), new_node);
}

int	m_create_tokens(t_data *data)
{
	char	c;
	int		i;

	i = -1;
	while (data->input[++i])
	{
		if (data->input[i] == '\"' || data->input[i] == '\'')
		{
			c = data->input[i++];
			while (data->input[i] && data->input[i] != c)
				i++;
		}
		else if (data->input[i] == '|')
		{
			m_new_token(&data->token, ft_substr(data->input, 0, i));
			data->input = m_cut_until_end(data->input, i + 1);
			if (!data->input || data->token == NULL)
				return (MALLOC);
			i = -1;
		}
	}
	if (data->input && data->input[0])
		if (m_new_token(&data->token, ft_substr(data->input, 0, i)) == NULL)
			return (MALLOC);
	return (SUCCESS);
}
