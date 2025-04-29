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

void read_heredoc(const char *delimiter)
{
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();
    if (pid == 0)
    {
        // === CHILD PROCESS: handles heredoc input ===

        g_signal_main = 0;             // heredoc mode
        signal_handler();          // heredoc signal behavior
        close(pipefd[0]);              // child only writes

        while (1)
        {
            char *line = readline("> ");

            if (!line)
            {
                // Ctrl+D pressed: EOF
                write(1, "\n", 1);
                break;
            }

            if (strcmp(line, delimiter) == 0)
            {
                // Delimiter reached
                free(line);
                break;
            }

            // Write input to heredoc pipe
            write(pipefd[1], line, strlen(line));
            write(pipefd[1], "\n", 1);
            free(line);
        }
        close(pipefd[1]);
        exit(0);  // normal heredoc exit
    }
    else
    {
        // === PARENT PROCESS: waits and sets up STDIN ===
        int status;
        close(pipefd[1]);              // parent only reads
        waitpid(pid, &status, 0);      // wait for heredoc process
        g_signal_main = 1;             // back to shell mode
        signal_handler();
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        {
            // Ctrl+C during heredoc → abort input
            close(pipefd[0]);
            return;
        }

        // If heredoc exited normally: redirect STDIN to heredoc content
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
}