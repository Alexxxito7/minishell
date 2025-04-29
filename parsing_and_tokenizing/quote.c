/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:14:43 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:45 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	m_count_quote(char *input)
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
			val = false;
			c = input[i];
		}
		else if (!val && input[i] == c)
		{
			val = true;
			count++;
		}
		i++;
	}
	return (count % 2);
}

int	m_single_quote(t_token *t_pnt, int *start, bool *quote)
{
	int	end;

	end = 0;
	if (m_new_i_node(&t_pnt->i_list,
			ft_substr(t_pnt->token, 0, *start), 't', 't') == NULL)
		return (MALLOC);
	*start += 1;
	while (t_pnt->token[*start + end] && t_pnt->token[*start + end] != '\'')
		end++;
	if (m_new_i_node(&t_pnt->i_list,
			ft_substr(t_pnt->token, *start, end), 'f', 'f') == NULL)
		return (MALLOC);
	t_pnt->token = m_cut_until_end(t_pnt->token, *start + end + 1);
	if (t_pnt->token == NULL)
		return (MALLOC);
	*start = -1;
	*quote = false;
	return (SUCCESS);
}

int	m_double_quote(t_token *t_pnt, int *start, bool *quote)
{
	int	end;

	end = 0;
	if (m_new_i_node(&t_pnt->i_list,
			ft_substr(t_pnt->token, 0, *start), 't', 't') == NULL)
		return (MALLOC);
	*start += 1;
	while (t_pnt->token[*start + end] && t_pnt->token[*start + end] != '\"')
		end++;
	if (m_new_i_node(&t_pnt->i_list,
			ft_substr(t_pnt->token, *start, end), 't', 'f') == NULL)
		return (MALLOC);
	t_pnt->token = m_cut_until_end(t_pnt->token, *start + end + 1);
	if (t_pnt->token == NULL)
		return (MALLOC);
	*start = -1;
	*quote = false;
	return (SUCCESS);
}

int	m_find_quote_2(t_data *data, t_token *t_pnt, bool quote)
{
	if (quote == true)
	{
		if (m_new_i_node(&t_pnt->i_list, t_pnt->token, 't', 't') == NULL)
			return (MALLOC);
	}
	else if (t_pnt->token[0] && !quote)
	{
		if (m_new_i_node(&t_pnt->i_list, t_pnt->token, 't', 't') == NULL)
			return (MALLOC);
	}
	else if (!t_pnt->token[0] && !quote)
		free(t_pnt->token);
	m_find_variable(data, &t_pnt->i_list);
	t_pnt->token = NULL;
	return (data->status);
}

int	m_find_quote(t_data *data)
{
	t_token			*t_pnt;
	int				start;
	bool			quote;

	t_pnt = data->token;
	while (t_pnt)
	{
		start = -1;
		quote = true;
		while (t_pnt->token && t_pnt->token[++start])
		{
			if (t_pnt->token[start] == '\'')
				data->status = m_single_quote(t_pnt, &start, &quote);
			else if (t_pnt->token[start] == '\"')
				data->status = m_double_quote(t_pnt, &start, &quote);
			if (!quote && data->status != SUCCESS)
				return (data->status);
		}
		data->status = m_find_quote_2(data, t_pnt, quote);
		t_pnt = t_pnt->next;
	}
	return (data->status);
}
