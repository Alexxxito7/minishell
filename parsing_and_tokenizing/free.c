/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:39:56 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:02:57 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	m_free_data(t_data *data)
{
	t_env_list	*pnt;
	t_env_list	*next;

	pnt = data->env_list.next;
	if (data->token)
		m_free_token_list(&data->token);
	while (pnt)
	{
		next = pnt->next;
		free(pnt->key);
		free(pnt->value);
		free(pnt);
		pnt = next;
	}
	data->env_list.next = NULL;
	free(data->env_list.key);
	free(data->env_list.value);
	free(data->input);
	m_free(data->env_copy);
	data->env_list.key = NULL;
	data->env_list.value = NULL;
}

void	m_free(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
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
}

void	m_exit(t_data *data, int status)
{
	m_print_status(status);
	if (data)
		m_free_data(data);
	if (status != 128)
		rl_clear_history();
	data->exit_status = status;
	if (status == 2)
		exit(status);
}

void	m_free_token_list(t_token **token_list)
{
	t_token	*pnt;
	t_token	*next;

	pnt = *token_list;
	while (pnt)
	{
		next = pnt->next;
		free(pnt->token);
		if (pnt->i_list)
			m_free_input_list(&pnt->i_list);
		free(pnt);
		pnt = next;
	}
}
