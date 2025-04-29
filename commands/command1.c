/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:39:56 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:02:57 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TOKEN LIST --> INPUT LIST --> ELEMENTS WITH FLAG

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/

int	m_cd(char **path)
{
	char	*path_copy;

	if (path[1] == NULL) //          path[0] = cd     path[1] = Desktop/minishell/...
	{
		path_copy = getenv("HOME");
		if (!path_copy)
			return(printf("cd: Home path undefined"), ERROR);
	}
	else
		path_copy = path[1];
	if (chdir(path_copy) != 0)
		return(printf("cd: Path not found"), ERROR);
	return (SUCCESS);
}

// Function to get the home directory environment variable
char *get_home_directory() {
    char *home = ;
    if (!home) {
        );
    }
    return home;
}

int m_cd(t_list *list_pipe)
{
    char *path_copy;
    
    if (list_pipe == NULL)
    {
        path_copy = getenv("HOME");
        if (!path_copy)
            return (printf("cd: HOME path undefined\n"), ERROR);
    }
    else if (args->content == NULL)  // No valid content in the first node
    {
        path_copy = get_home_directory();
        if (!path_copy) {
            return ERROR;
        }
    }
    else  // Extract the argument from the linked list
    {
        path_copy = (char *)args->content;  // First argument in the linked list
    }

    // Check if the path is absolute (starts with '/')
    if (path_copy[0] == '/')
    {
        if (chdir(path_copy) != 0)
        {
            return (printf("cd: Path not found\n"), ERROR);
        }
    }
    else
    {
        // Relative path: resolve based on the current working directory
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            return (printf("cd: Error getting current directory\n"), ERROR);
        }

        // Combine the current directory with the relative path
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", cwd, path_copy);

        // Try changing to the full path
        if (chdir(full_path) != 0)
        {
            return (printf("cd: Path not found\n"), ERROR);
        }
    }

    return SUCCESS;
}


int	m_echo(char **content)
{

}

echo -n Hello