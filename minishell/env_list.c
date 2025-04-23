#include "minishell.h"

t_env_list	*m_new_variable(char *str)
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

void	m_init_data(t_data *data, char *input, char **env)
{
	int			i;
	t_env_list	*new;

	i = 0;
	data->exit_status = 0;
	data->input = input;
	data->result = NULL;
	data->env_list.key = NULL;
	data->env_list.value = NULL;
	data->env_list.next = NULL;
	while (env[i])
	{
		new = m_new_variable(env[i]);
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
			m_exit_error(data, MALLOC);
		i++;
	}
}

void	m_add_env_back(t_env_list *lst, t_env_list *new)
{
	if (!lst || !new)
		return;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

void	m_free_data(t_data *data)
{
    t_env_list *pnt;
    
    pnt = data->env_list.next;

    while (pnt)
    {
        t_env_list *next = pnt->next;
        free(pnt->key);
        free(pnt->value);
        free(pnt);
        pnt = next;
    }
    data->env_list.next = NULL;
    free(data->env_list.key);
    free(data->env_list.value);
    data->env_list.key = NULL;
    data->env_list.value = NULL;
	//free(data->input);
	free(data->result);
}

