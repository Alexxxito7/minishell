/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:39:56 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:02:50 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env_list	*m_new_env_node(char *str)
{
	int			i;
	t_env_list	*new_node;

	i = 0;
	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (new_node == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	new_node->key = ft_substr(str, 0, i);
	new_node->value = ft_substr(str, i + 1, ft_strlen(str));
	new_node->next = NULL;
	return (new_node);
}

void	m_add_env_back(t_env_list *lst, t_env_list *new)
{
	if (!lst || !new)
		return ;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	new->next = NULL;
}
