/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:46:30 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/21 12:46:32 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input_list	*m_new_input_node(t_input_list *list, char *str, char c)
{
	t_input_list	*new_node;

	if (!list || !str)
		return (NULL);
	if (list->str == NULL)
	{
		list->next = NULL;
		list->c = c;
		list->str = ft_strdup(str);
		if (!list->str)
			m_free_input_list(list);
		return (free(str), list);
	}
	new_node = (t_input_list *)malloc(sizeof(t_input_list));
	if (new_node == NULL)
		return (free(str), NULL);
	new_node->str = ft_strdup(str);
	new_node->c = c;
	new_node->next = NULL;
    if (!new_node->str)
		return (free(str), NULL);
    while (list->next)
		list = list->next;
	list->next = new_node;
	return (free(str), new_node);
}

void	m_free_input_list(t_input_list *input_list)
{
	t_input_list  *pnt;

    pnt = input_list;
	while (pnt)
	{
		t_input_list *next = pnt->next;
		free(pnt->str);
		pnt = next;
	}
	input_list->next = NULL;
	free(input_list->str);
	input_list->str = NULL;
	input_list = NULL;
}