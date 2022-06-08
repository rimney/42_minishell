/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 04:47:20 by rimney            #+#    #+#             */
/*   Updated: 2022/06/08 04:25:49 by rimney           ###   ########.fr       */
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





void	ft_pipe(int in, t_pipe *tpipe, t_exec *exec, int index)
{

    if  (in != -1)
    {
        dup2(in , 0);    
        close(in);
    }
    if (tpipe->fd[1] != -1)
    {
        dup2(tpipe->fd[1] , 1);
        close(tpipe->fd[1]);
    }

    close(tpipe->fd[0]);
        ft_execute_command(exec, index);
}

 void    ft_apply_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index)
 {
    if (in != -1)
    {
        dup2(in, 0);
        close(in);
    }
    if(out != 0)
    {
        dup2(out, 1);
        close(out);
    }
    close(tpipe->fd[0]);
   // close(tpipe->fd[1]);
     ft_execute_command(exec, index);
    exit(0);
 }


int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe)
{
	int in_save;
	int pid;
    int fd;

    fd = -1;
    if (exec->command[index + 1] != NULL)
    {
        pipe(tpipe->fd);
        in_save =  tpipe->fd[0];
    }
    pid = fork();
    if (pid == 0)
    {
		ft_pipe(in, tpipe, exec, index);
		exit(0);
    }
    if (in != -1)
        close(in);
    if (tpipe->fd[1] !=  -1)
        close(tpipe->fd[1]);
    // if (index == tpipe->max - 1 && exec->redirection_count > 0)
    // {
    //     fd = open(exec->command[index + 2], O_CREAT | O_RDWR | O_APPEND, 0644);
    //     in_save = tpipe->fd[0];
    //     pid = fork();
    //     if(pid == 0)
    //      ft_apply_redirection_after_pipe(in_save, fd,  tpipe, exec, index);
    // } 
    // printf("%d << index \n", index);
    // printf("%d << max \n", tpipe->max);
    //close(tpipe->fd[0]);
  
    if (index < tpipe->max)
  	    execute_pipe(exec, index + 2, in_save , tpipe);
    waitpid(pid , 0 , 0);
     return index;
}


// int main(int argc, char **argv, char **envp)
// {
// 	char *line;
// 	char **line_parser;
// 	t_env env;
// 	t_pipe pipe;

// 	ft_get_env(&env, envp);
// 	line = readline("Minishell >>");
// 	line_parser = ft_split(line, ' ');
// 	ft_assign_tpipe(&pipe, ft_count_elements(line_parser), envp); // should be replaced with npipes;
// 	while((line = readline("Minishell >> ")))
// 	{
// 		add_history(line);
//     	line_parser = ft_split(line, ' ');
// 		pipe.max = ft_count_elements(line_parser);
// 	    exuecute_pipe(line_parser, 0, -1, &pipe);
//         waitpid(-1 , 0 , 0);
//   		free(line);
//   	}
//   	return (0);
// }
