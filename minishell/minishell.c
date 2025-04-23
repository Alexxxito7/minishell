/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:45 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/14 12:41:49 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*m_str_concat(char *str1, char *str2);
char	*m_str_cut_to_end(char *str, int start);
void	to_print(t_input_list *list);

void	foo1()
{
	write(2, "Rafayel\n", 8);
}

int m_find_variable(t_data *data, t_input_list *input_list)
{
	t_input_list	*pnt;
	char			*temp1;
	int				start;
	int				end;

	pnt = input_list;
	while (pnt)
	{
		if (pnt->c == 't')
		{
			start = -1;
			while (pnt->str[++start])
			{
				if (pnt->str[start] == '$' && pnt->str[start + 1] == '?')
				{
					temp1 = m_str_concat(ft_substr(pnt->str, 0, start),
					m_replace_variable(data, ft_substr(pnt->str, start, 2)));
					if (!temp1)
						return (MALLOC);
					pnt->str = m_str_concat(temp1, m_str_cut_to_end(pnt->str, start + 2));
					if (!pnt->str)
						return (MALLOC);
					start = -1;
				}
				else if (pnt->str[start] == '$' && (pnt->str[start + 1] == ' ' || pnt->str[start + 1] == '\'' || pnt->str[start + 1] == '\"' || pnt->str[start + 1] == '$'))
					start++;
				else if (pnt->str[start] == '$' && pnt->str[start + 1])
				{
					end = 0;
					temp1 = ft_substr(pnt->str, 0, start);
					if (!temp1)
						return (MALLOC);
					start++;
					while (ft_isdigit(pnt->str[start + end]) || ft_isalpha(pnt->str[start + end]))
						end++;
					temp1 = m_str_concat(temp1, m_replace_variable(data, ft_substr(pnt->str, start, end)));
					if (!temp1)
						return (MALLOC);
					pnt->str = m_str_concat(temp1, m_str_cut_to_end(pnt->str, start + end));
					if (!pnt->str)
						return (MALLOC);
					start = -1;
				}
			}
		}
		pnt = pnt->next;
	}
	to_print(input_list);
	return (SUCCESS);
}

void	to_print(t_input_list *list)
{
	t_input_list *pnt;

	if(!list->str)
		return ;
	pnt = list;
	while (pnt)
	{
		printf("len %zu > %c > %s\n", ft_strlen(pnt->str), pnt->c, pnt->str);
		pnt = pnt->next;
	}
}


char	*m_full_concat(t_input_list *input_list, char *input)
{
	t_input_list	*pnt;

	pnt = input_list;
	
	(void)input_list;
	(void)pnt;
	// input = NULL;
	input = m_str_concat(pnt->str, ft_strdup(""));
	if (input == NULL)
		printf("===%s\n", input);
	// if (!input)
	// 	return (NULL);
	// pnt = pnt->next;
	// while (pnt)
	// {
	// 	input = m_str_concat(input, pnt->str);
	// 	if (!input)
	// 		return (NULL);
	// 	pnt = pnt->next;
	// }
	// printf("===%s\n", input);
	return (input);
}

int	m_find_qoute(t_data *data)
{
	t_input_list	input_list;
	int				start;
	int				status;
	bool			quote;

	start = -1;
	input_list.next	= NULL;
	input_list.str = NULL;
	quote = true;
	while (data->input && data->input[++start])
	{
		if (data->input[start] == '\'')
		{
			if (quote == true)
				quote = !quote;
			status = m_single_quote(data, &input_list, &start);
			if (status != SUCCESS)
				return (status);
		}
		else if (data->input[start] == '\"')
		{
			if (quote == true)
				quote = !quote;
			status = m_double_quote(data, &input_list, &start);
			if (status != SUCCESS)
				return (status);
		}
	}
	if (quote == true)
	{
		if (m_new_input_node(&input_list, data->input, 't') == NULL)
			return (MALLOC);
		m_find_variable(data, &input_list);
	}
	else if (data->input[0] && !quote)
	{
		if (m_new_input_node(&input_list, data->input, 't') == NULL)
			return (MALLOC);
		m_find_variable(data, &input_list);
	}
	else
		m_find_variable(data, &input_list);
	if (m_full_concat(&input_list, data->input) == NULL)
		return (MALLOC);
	return (m_free_input_list(&input_list), SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
	int			status;
	t_data		data;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell:~$");
		input = m_trim(input);
		if (input[0])
		{
			m_init_data(&data, input, env);
			if (m_count_qoute(data.input))
				m_print_status(128);
			status = m_find_qoute(&data);
			if (status != SUCCESS)
				m_exit_error(&data, status);
			return (clear_history(), m_exit_error(&data, status), status);
		}
		add_history(input);
		free(input);
	}
	return (clear_history(), SUCCESS);
}


///    echo" $USER %kkkkkk  $PWD m"  kkkkk  "mmmmm"

////  echo 'hell' "$USER' $USER' " "$USER"