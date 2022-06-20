/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 04:47:20 by rimney            #+#    #+#             */
/*   Updated: 2022/06/20 13:48:33 by rimney           ###   ########.fr       */
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
    if(out != -1)
    {
        dup2(out, 1);
        close(out);
    }
    tpipe->max = 0;
    close(tpipe->fd[0]);
        ft_execute_command(exec, index);
    //exec->redirecion_flag = 0;
 }

 void   ft_apply_input_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index)
 {
    if(in != -1)
    {
        dup2(in, 0);
        close(in);
    }
    if(out != -1)
    {
        dup2(out, 1);
        close(out);
    }
    tpipe->fd[0] = 0;
    close(tpipe->fd[0]);
    ft_execute_command(exec, index);
 }

int ft_flag_after_pipe(t_exec *exec)
{
    //printf("%d >> hfhfhf\n", exec->redirecion_flag);
    if(exec->redirecion_flag == 1 || exec->append_flag == 1 || exec->input_flag == 1)
        return (1);
    return (0);
}

// void    ft_redirect_after_pipe_flag(t_exec *exec, t_pipe *tpipe, int fd, int index, int in_save)
// {
//     int pid;    

//     printf("%d << redi flag\n", exec->redirecion_flag);
//     if(exec->redirecion_flag == 1)
//     {
//         printf("dddd\n");
//         fd = open(exec->command[index + exec->redirection_count + 4], O_RDWR | O_CREAT | O_TRUNC, 0644);
//         printf("%d << fd \n", fd);
//     }
//     if(exec->append_flag == 1)
//         fd = open(exec->command[index + exec->append_count + 2], O_RDWR | O_CREAT | O_APPEND, 0644);
//     if(exec->input_flag == 1)
//     {
//         fd = open(exec->command[index + exec->input_count + 2], O_RDWR);
//         pid = fork();
//         if(pid == 0)
//             ft_apply_input_redirection_after_pipe(fd, -1, tpipe, exec, index + 2);
//     }
//     pid = fork();
//     if(pid == 0)
//         ft_apply_redirection_after_pipe(in_save, fd, tpipe, exec, index + 2);
//     wait(NULL);
// }

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
    // printf("%d in\n", in)
    // if(exec->command[index + 1])
    // {
    //     if(ft_strcmp(exec->command[index + 1], ">") == 0)
    //     {
    //         exec->redirecion_flag = 1;
    //         ft_redirect_after_pipe_flag(exec, tpipe, fd,  index - 2, in_save);
    //         return index;
    //     }
    // }
  //  close(tpipe->fd[0]);
    // if(exec->command[index + 1] && ft_strcmp(exec->command[index + 1], ">") == 0 && exec->pipe_count > 2)
    // {
    //     exec->redirecion_flag = 1;
    //     ft_redirect_after_pipe_flag(exec, tpipe, fd, index - 2, in_save);
    //     printf("passZZZZed\n");
    //     return (index);
    // }
    if (index < tpipe->max)
    {
        execute_pipe(exec, index + 2, in_save , tpipe);
    }
    wait(NULL);
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
