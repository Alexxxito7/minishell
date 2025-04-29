/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:45 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:17 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	to_print(t_i_list **list)
{
	t_i_list	*pnt;

	pnt = *list;
	if (!*list)
		return ;
	while (pnt)
	{
		printf("len =	%zu	c =	%c	p =	%c	s =	%s\n",
			ft_strlen(pnt->str), pnt->c, pnt->p, pnt->str);
		pnt = pnt->next;
	}
}

void	m_print_token(t_token **token)
{
	int		i;
	t_token	*pnt;

	i = 1;
	pnt = *token;
	while (pnt)
	{
		printf("\n------------------------------\n");
		printf("token %d	%s\n", i, pnt->token);
		to_print(&pnt->i_list);
		printf("\n------------------------------\n");
		pnt = pnt->next;
		i++;
	}
}

int	m_parsing_and_tokenizing(t_data *data)
{
	if (m_count_quote(data->input))
		return (128);
	data->status = m_create_tokens(data);
	if (data->status != SUCCESS)
		m_exit(data, data->status);
	data->status = m_find_quote(data);
	m_print_token(&data->token);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	t_data		data;

	(void)argc;
	(void)argv;
	data.value = true;
	while (1)
	{
		input = readline("minishell:~$");
		if (input[0])
		{
			add_history(input);
			m_init_data(&data, input, env);
			if (data.status != SUCCESS)
				return (free(input), m_exit(&data, data.status), data.status);
			data.status = m_parsing_and_tokenizing(&data);
			if (data.status != SUCCESS)
				m_exit(&data, data.status);
			//m_free_data(&data);
		}
		free(input);
	}
	return (clear_history(), SUCCESS);
}
