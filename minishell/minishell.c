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
				else if (pnt->str[start] == '$' && (pnt->str[start + 1] == ' '
					|| pnt->str[start + 1] == '\'' || pnt->str[start + 1] == '\"'))
					start++;
				else if (pnt->str[start] == '$')
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

char	*m_str_concat(char *str1, char *str2)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!str1 || !str2)
		return (NULL);
	temp = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!temp)
		return (free(str1), free(str2), NULL);
	while (str1[++i])
		temp[i] = str1[i];
	while (str2[j])
		temp[i++] = str2[j++];
	temp[i] = '\0';
	return (free(str1), free(str2), temp);
}

void	to_print(t_input_list *list)
{
	t_input_list *pnt;

	pnt = list;
	while (pnt)
	{
		printf("len %zu > %c > %s\n", ft_strlen(pnt->str), pnt->c, pnt->str);
		pnt = pnt->next;
	}
}

char	*m_str_cut_to_end(char *str, int start)
{
	char	*temp;
	
	temp = ft_strdup(str + start);
	if (!temp)
		return (NULL);
	free(str);
	return (temp);
}
int	m_single_quote(t_data *data, t_input_list *input_list, int *start)
{
	int	end;

	end = 0;
	if (m_new_input_node(input_list, ft_substr(data->input, 0, *start), 't') == NULL)
		return (m_free_input_list(input_list), MALLOC);
	*start += 1;
	while (data->input[*start + end] != '\'')
		end++;
	if (m_new_input_node(input_list, ft_substr(data->input, *start, end), 'f') == NULL)
		return (m_free_input_list(input_list), MALLOC);
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

int	m_find_qoute(t_data *data)
{
	t_input_list	input_list;
	int				start;

	start = -1;
	input_list.next	= NULL;
	input_list.str = NULL;
	while (data->input && data->input[++start])
	{
		if (data->input[start] == '\'')
		{
			m_single_quote(data, &input_list, &start);
		}
		else if (data->input[start] == '\"')
		{
			m_double_quote(data, &input_list, &start);
		}
	}
	to_print(&input_list);
	printf("---------------------------------------\n");
	m_find_variable(data, &input_list);

	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	char		*input;
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
			m_find_qoute(&data);
			m_exit_error(&data, SUCCESS);
			return (clear_history(), SUCCESS);
		}
		add_history(input);
		free(input);
	}
	return (clear_history(), SUCCESS);
}


///    echo" $USER %kkkkkk  $PWD m"  kkkkk  "mmmmm"

////  echo 'hell' "$USER' $USER' " "$USER"