/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:46:30 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:06 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_i_list	*m_new_i_node(t_i_list **list, char *str, char c, char p)
{
	t_i_list	*new_node;

	str = m_trim(str);
	if (!str)
		return (NULL);
	new_node = malloc(sizeof(t_i_list));
	if (new_node == NULL)
		return (free(str), NULL);
	new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (free(new_node), free(str), NULL);
	new_node->c = c;
	new_node->p = p;
	new_node->next = NULL;
	m_add_input_list_back(list, new_node);
	return (free(str), new_node);
}

void	m_free_input_list(t_i_list **input_list)
{
	t_i_list	*pnt;
	t_i_list	*next;

	pnt = *input_list;
	while (pnt)
	{
		next = pnt->next;
		free(pnt->str);
		free(pnt);
		pnt = next;
	}
}

void	m_add_input_list_back(t_i_list **list, t_i_list *new_node)
{
	t_i_list	*pnt;

	if (!list || !new_node)
		return ;
	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	pnt = *list;
	while (pnt->next != NULL)
		pnt = pnt->next;
	pnt->next = new_node;
}
