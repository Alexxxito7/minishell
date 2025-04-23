/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:40:10 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/23 17:40:12 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_replace_variable(t_data *data, char *var_name)
{
	int			i;
	t_env_list	*pnt;

	pnt = &data->env_list;
	i = 0;
	if (ft_strncmp(var_name, "$?", 2) == 0)
	{
		return (ft_itoa(data->exit_status));
	}
	while (pnt)
	{
		while (pnt->key[i] && var_name[i] && pnt->key[i] == var_name[i])
			i++;        
		if (pnt->key[i] == var_name[i])
        {
			free(var_name);
			var_name = ft_strdup(pnt->value);
			return (var_name);
		}
		pnt = pnt->next;
	}
	free(var_name);
	return (ft_strdup(""));
}

int	m_single_quote(t_data *data, t_input_list *input_list, int *start)
{
	int	end;

	end = 0;
	if (m_new_input_node(input_list, ft_substr(data->input, 0, *start), 't') == NULL)
		return (MALLOC);
	*start += 1;
	while (data->input[*start + end] != '\'')
		end++;
	if (m_new_input_node(input_list, ft_substr(data->input, *start, end), 'f') == NULL)
		return (MALLOC);
	data->input = m_str_cut_to_end(data->input, *start + end + 1);
	*start = -1;
	return (SUCCESS);
}
int	m_double_quote(t_data *data, t_input_list *input_list, int *start)
{
	int	end;

	end = 0;
	if (m_new_input_node(input_list,  ft_substr(data->input, 0, *start), 't') == NULL)
		return (m_free_input_list(input_list), MALLOC);
	*start += 1;
	while (data->input[*start + end] != '\"')
		end++;
	if (m_new_input_node(input_list, ft_substr(data->input, *start, end), 't') == NULL)
		return (m_free_input_list(input_list), MALLOC);
	data->input = m_str_cut_to_end(data->input, *start + end + 1);
	*start = -1;
	return (SUCCESS);
}