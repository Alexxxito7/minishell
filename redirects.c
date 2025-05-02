/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghazary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:45 by rghazary          #+#    #+#             */
/*   Updated: 2025/04/26 11:03:17 by rghazary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Heredoc condition

cat << EOF | Tabs are considered
example:

The current working directory is: $PWD
    You are logged in as: $(whoami)
        Hello
EOF

The current working directory is: /home/linuxize
    You are logged in as: linuxize
        Hello
___________________________________________________________________
cat <<- EOF | Tabs are not considered (they are stripped/trimmed)

example:

The current working directory is: $PWD
    You are logged in as: $(whoami)
        Hello
EOF

The current working directory is: /home/linuxize
You are logged in as: linuxize
Hello
___________________________________________________________________
cat << "PWD" or cat << 'PWD'| Variables are NOT changed ($USER stays $USER)

example:

The current working directory is: $PWD
You are logged in as: $(whoami)
Hello
PWD

The current working directory is: $PWD
You are logged in as: $(whoami)
Hello


___________________________________________________________________
cat << PWD | Variables are changed in the text, even if they are in "" or '' ('$USER' becomes 'alschnei', "$USER" becomes "alschnei" AND brackets will stay)

example:

$USER
"$USER"
'$USER'
PWD

alschnei
"alschnei"
'alschnei'

*/




char *strip_quotes(const char *s)
{
    size_t len = strlen(s);
    if ((s[0] == '\'' || s[0] == '"') && s[len - 1] == s[0])
        return (strndup(s + 1, len - 2));
    return ft_strdup(s);
}

int is_quoted(const char *s)
{
    size_t len = strlen(s);
    return (len >= 2 && ((s[0] == '"' && s[len - 1] == '"') || (s[0] == '\'' && s[len - 1] == '\'')));
}

//expand_vars for finding env_variables m_replace_variable(t_data *data, char *var_name)

char *heredoc(char *herestring)
{
    char *raw = herestring;

    int strip_tabs = 0;
    const char *delimiter_start;

    if (strncmp(raw, "<<-", 3) == 0)
    {
        strip_tabs = 1;
        delimiter_start = raw + 3;
    } else if (strncmp(raw, "<<", 2) == 0)
    {
        delimiter_start = raw + 2;
    } else {
        return NULL; // Not a heredoc
    }
    while (*delimiter_start == ' ')
        delimiter_start++;

    int quoted = is_quoted(delimiter_start);
    char *delimiter = strip_quotes(delimiter_start);

    char *result = calloc(1, 1);
    char *line;

    while (1) {
        line = readline("> ");
        if (!line)
            break;

        if (strip_tabs) {
            while (*line == '\t')
                ft_memmove(line, line + 1, strlen(line));
        }
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        if (!quoted)
        {
            char *expanded = expand_vars(line);
            free(line);
            line = expanded;
        }
        char *tmp = malloc(strlen(result) + strlen(line) + 2);
        if (!tmp)
            exit(1); // Handle memory error
        strcpy(tmp, result);
        strcat(tmp, line);
        strcat(tmp, "\n");
        free(result);
        result = tmp;
        free(line);
    }
    free(delimiter);
    return (printf("%s", result), result);
}