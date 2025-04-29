/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:02:37 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:02:38 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_env(t_data *data, char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env && env[count])
		count++;
	data->env_copy = malloc(sizeof(char *) * (count + 1));
	if (!data->env_copy)
		return (MALLOC);
	while (i < count)
	{
		data->env_copy[i] = ft_strdup(env[i]);
		if (data->env_copy[i] == NULL)
			return (m_free(data->env_copy), MALLOC);
		i++;
	}
	data->env_copy[i] = NULL;
	return (SUCCESS);
}

int	m_init_data_1(t_data *data, char *input)
{
	data->input = ft_strdup(input);
	if (data->input == NULL)
		return (MALLOC);
	data->status = 0;
	data->env_list.key = NULL;
	data->env_list.value = NULL;
	data->env_list.next = NULL;
	data->token = NULL;
	data->env_copy = NULL;
	if (data->value)
	{
		data->exit_status = 0;
		data->value = false;
	}
	return (SUCCESS);
}

void	m_init_data(t_data *data, char *input, char **env)
{
	int			i;
	t_env_list	*new;

	i = 0;
	m_init_data_1(data, input);
	while (env[i])
	{
		new = m_new_env_node(env[i]);
		if (new)
		{
			if (!data->env_list.key)
			{
				data->env_list.key = new->key;
				data->env_list.value = new->value;
				free(new);
			}
			else
				m_add_env_back(&data->env_list, new);
		}
		else
			m_exit(data, MALLOC);
		i++;
	}
	data->status = copy_env(data, env);
}
