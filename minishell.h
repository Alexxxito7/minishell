/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:42:27 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:36 by rghazary         ###   ########.fr       */
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

extern int	g_signal_main;

enum e_struct
{
	SUCCESS,
	ERROR,
	MALLOC
};
typedef struct s_i_list
{
	char				*str;
	char				c;
	char				p;
	struct s_i_list		*next;
}	t_i_list;

typedef struct s_token
{
	struct s_i_list		*i_list;
	char				*token;
	struct s_token		*next;
}						t_token;

typedef struct s_env_list
{
	char				*key;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_data
{
	bool				value;
	int					exit_status;
	char				*input;
	char				**env_copy;
	int					status;
	struct s_env_list	env_list;
	struct s_token		*token;
}	t_data;

////  free.c

void			m_free_data(t_data *data);
void			m_print_status(int status);
void			m_free(char **str);
void			m_exit(t_data *data, int status);

////  minishell.c

void			m_print_token(t_token **token);
void			to_print(t_i_list **list);

////// init.c

void			m_init_data(t_data *data, char *input, char **env);
int				copy_env(t_data *data, char **env);

/////   variable.c

char			*m_replace_variable(t_data *data, char *var_name);
int				m_find_variable(t_data *data, t_i_list **i_list);

// quote.c

int				m_count_quote(char *input);
int				m_single_quote(t_token *t_pnt, int *start, bool *quote);
int				m_double_quote(t_token *t_pnt, int *start, bool *quote);
int				m_find_quote(t_data *data);

// string.c

char			*m_trim(char *input);
char			*m_cut_until_end(char *str, int start);
char			*m_str_concat(char *str1, char *str2);

// signal.c
void	signal_setup();
void	signal_handler(int sig);

// env_list.c

void			m_add_env_back(t_env_list *lst, t_env_list *new);
void			m_free_data(t_data *data);

t_env_list		*m_new_env_node(char *str);

//// input_list.c

void			m_free_input_list(t_i_list **i_list);
void			m_add_input_list_back(t_i_list **list, t_i_list *new_node);
t_i_list		*m_new_i_node(t_i_list **list, char *str, char c, char p);

//// tokens

int				m_create_tokens(t_data *data);
int				m_trim_tokens(t_data *data);
void			m_free_token_list(t_token **token_list);
t_token			*m_new_token(t_token **list, char *str);

#endif
