/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 04:47:20 by rimney            #+#    #+#             */
/*   Updated: 2022/05/31 04:26:53 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char *history;

// int ft_count_elements(char **str)
// {
//   int i;

//   i = 0;
//   while(str[i])
//     i++;
//   return (i);
// }
int exuecute( char **args , int index, int in, int max,  char   **envp)
{
    if (index >= max)
        return 0;
        
    int fd[2]  =  {-1, -1};
    int o = -1;
    if (args[index + 1] != NULL)
    {
        pipe(fd);
        o =  fd[0];
    }
    int pid = fork();
    if (pid == 0)
    {
        if  (in != -1)
        {
            dup2(in , 0);    
            close(in);
        }
        if (fd[1] != -1)
        {
            dup2(fd[1] , 1);
            close(fd[1]);
        }
        close(fd[0]);
        char *ar[2];
        ar[0] = ft_exec_command(envp , args[index]);
        ar[1] = NULL;
        if(execve(ar[0],ar , envp) == -1)
		{
			printf("command not found\n");
			exit(0);
			// return 0;
		}
		exit(0);
    }
    if (in  != -1)
        close(in);
    if (fd[1] !=  -1)
        close(fd[1]);
  
  exuecute(args ,  index + 2, o, max,envp);
     waitpid(pid , 0 , 0);
     return 0;

}
// void ft_pipes(int in, int out, char *command, char **envp)
// {
//     int pid;
//     char **command_parser;

//     command_parser = ft_split(command, ' ');
//     pid = fork();
//     if(pid == 0)
//     {
//         if(in != 0)
//         {
//             dup2(in, 0);
//             close(in);
//         }
//         if(out != 1)
//         {
//             dup2(out, 1);
//             close(out);
//         }
//     execve(ft_exec_command(envp, command_parser[0]), command_parser, envp);
// 	exit(0);
//     }
// }
// int    ft_pipe(int n_pipes, char **argv, char **envp)
// {
//     int i;
//     int pid;
//     int in;
//     int fd[2];
//     char **cmd_parser = ft_split(argv[n_pipes - 1], ' ');

//     in = 0;
//     i = 0;
//     while (i < n_pipes - 1)
//     {
//         if(ft_strcmp(argv[i], "|") == 0)
//         {
//         	pipe(fd);
//               ft_pipes(in, fd[1], argv[i - 1], envp);
//         	close(fd[1]);
//             in = fd[0];
//         }
//         i++;
//     }
// 	pid = fork();
// 	if(pid == 0)
// 	{
// 		if(in != 0)
// 		dup2(in, 0);
//     	if(execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp) == -1)
// 		{
// 			printf("command not found\n");
// 			exit(0);
// 			// return 0;
// 		}
// 		exit(0);
// 	}
// 	wait(NULL);
// 	wait(NULL);
// 	return (fd[1]);
// }



int main(int argc, char **argv, char **envp)
{
  char *line;
  char **line_parser;
  int pid;

  while((line = readline("Minishell >> ")))
  {
    add_history(line);
    line_parser = ft_split(line, ' ');
    // if(ft_strcmp(line, "history") == 0)
    //   ft_print_history(history);
    // else
    // {
        exuecute(line_parser, 0, -1, ft_count_elements(line_parser), envp);
          waitpid(-1 , 0 , 0);
       // ft_pipe(ft_count_elements(line_parser), line_parser, envp);
    //   ft_free(line_parser);
    //   free(line);
  }
  return (0);
}
