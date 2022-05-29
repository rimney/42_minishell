/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 04:47:20 by rimney            #+#    #+#             */
/*   Updated: 2022/05/29 18:31:37 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *history;

int ft_count_elements(char **str)
{
  int i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

void ft_pipes(int in, int out, char *command, char **envp)
{
    int pid;
    char **command_parser;

    command_parser = ft_split(command, ' ');
    pid = fork();
    if(pid == 0)
    {
        if(in != 0)
        {
            dup2(in, 0);
            close(in);
        }
        if(out != 1)
        {
            dup2(out, 1);
            close(out);
        }
    execve(ft_exec_command(envp, command_parser[0]), command_parser, envp);
    }
}
void    ft_pipe(int argc, char **argv, char **envp)
{
    int i;
    int pid;
    int in;
    int fd[2];
    char **cmd_parser = ft_split(argv[argc - 1], ' ');

    in = 0;
    i = 0;
    while (i < argc - 1)
    {
        if(ft_strcmp(argv[i + 1], "|") == 0)
        {
        	pipe(fd);
              ft_pipes(in, fd[1], argv[i], envp);
        	close(fd[1]);
            in = fd[0];
        }
        i++;
    }
    if(in != 0)
      dup2(in, 0);
    if(execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp) == -1)
	{
		printf("ddd\n");
		return ;
	}
}


// int main(int argc, char **argv, char **envp)
// {
//   char *line;
//   char **line_parser;
//   int pid;

//   while((line = readline("Minishell >> ")))
//   {
//     add_history(line);
//     line_parser = ft_split(line, ' ');
//     if(ft_strcmp(line, "history") == 0)
//       ft_print_history(history);
//     else
//     {
//       pid = fork();
//       if (pid == 0)
//         ft_pipe(ft_count_elements(line_parser), line_parser, envp);
//       ft_free(line_parser);
//       free(line);
//       waitpid(pid, 0, 0);
//     }
//   }
//   return (0);
// }
