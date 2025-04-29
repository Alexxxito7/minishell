/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:40:10 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:04:08 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	m_find_variable_3(char *str, int start)
{
	if (str[start] == '$' && (str[start + 1] == ' '
			|| str[start + 1] == '\''
			|| str[start + 1] == '\"'
			|| str[start + 1] == '$'))
	{
		return (1);
	}
	return (0);
}

int	m_find_variable_2(t_data *data, t_i_list *pnt, int *start)
{
	char	*temp;
	int		end;

	end = 0;
	temp = ft_substr(pnt->str, 0, *start);
	if (!temp)
		return (MALLOC);
	*start += 1;
	while (ft_isdigit(pnt->str[*start + end])
		|| ft_isalpha(pnt->str[*start + end]))
		end++;
	temp = m_str_concat(temp,
			m_replace_variable(data, ft_substr(pnt->str, *start, end)));
	if (!temp)
		return (MALLOC);
	pnt->str = m_str_concat(temp, m_cut_until_end(pnt->str, *start + end));
	if (!pnt->str)
		return (MALLOC);
	*start = -1;
	return (SUCCESS);
}

int	m_find_variable_1(t_data *data, t_i_list *pnt, int *start)
{
	char	*temp;

	temp = m_str_concat(ft_substr(pnt->str, 0, *start),
			m_replace_variable(data, ft_substr(pnt->str, *start, 2)));
	if (!temp)
		return (MALLOC);
	pnt->str = m_str_concat(temp, m_cut_until_end(pnt->str, *start + 2));
	if (!pnt->str)
		return (MALLOC);
	*start = -1;
	return (SUCCESS);
}

int	m_find_variable(t_data *data, t_i_list **input_list)
{
	t_i_list		*pnt;
	int				start;

	pnt = *input_list;
	while (pnt)
	{
		if (pnt->c == 't')
		{
			start = -1;
			while (pnt->str[++start])
			{
				if (pnt->str[start] == '$' && pnt->str[start + 1] == '?')
					data->status = m_find_variable_1(data, pnt, &start);
				else if (m_find_variable_3(pnt->str, start))
					start++;
				else if (pnt->str[start] == '$' && pnt->str[start + 1])
					data->status = m_find_variable_2(data, pnt, &start);
				if (data->status != SUCCESS)
					return (data->status);
			}
		}
		pnt = pnt->next;
	}
	return (SUCCESS);
}
