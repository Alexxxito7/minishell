/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:42:27 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/14 12:42:29 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "src/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h> 
# include <sys/stat.h> 
# include <dirent.h> 
# include <sys/wait.h>
# include <signal.h> 
# include <termios.h> 
# include <sys/ioctl.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <term.h>
# include <stdbool.h>

enum e_struct
{
	SUCCESS,
	ERROR,
	MALLOC
};

typedef struct s_input_list
{
	char				*str;
	char				c;
	struct s_input_list *next;
}	t_input_list;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	char				**result;
	char				*input;
	int					exit_status;
	struct s_env_list	env_list;
}	t_data;

/////   variable.c

char	*m_replace_variable(t_data *data, char *var_name);
int		m_single_quote(t_data *data, t_input_list *input_list, int *start);
int		m_double_quote(t_data *data, t_input_list *input_list, int *start);

// stirng.c

char	*m_trim(char *input);
int		m_count_qoute(char *input);
char	*m_str_cut_to_end(char *str, int start);
char	*m_str_concat(char *str1, char *str2);

// error.c

void	m_print_status(int status);
void	m_free(char **str);
void	m_exit_error(t_data *data, int status);

// env_list.c

t_env_list	*m_new_variable(char *str);
void		m_init_data(t_data *data, char *input, char **env);
void		m_add_env_back(t_env_list *lst, t_env_list *new);
void		m_free_data(t_data *data);


//// input_list.c
void			m_free_input_list(t_input_list *input_list);
t_input_list	*m_new_input_node(t_input_list *list, char *str, char c);

#endif
