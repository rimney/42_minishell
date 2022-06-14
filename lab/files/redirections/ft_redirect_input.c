/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:02:42 by rimney            #+#    #+#             */
/*   Updated: 2022/06/13 21:21:12 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    redirect(t_exec *exec, int command_location)
{
    int fd;

    fd = open(exec->command[exec->input_count], O_RDONLY);
    dup2(fd, 0);
    close(fd);
    ft_execute_command(exec, command_location);
    
}

int    ft_redirect_input(t_exec *exec, t_pipe *tpipe, int index, int location_flag)
{
    int i;
    int input_file;
    int pid;
    int command_location;

    i = index;
    tpipe->fd[0] = 0;

    if(location_flag == 0)
         command_location = 0;
    else
        command_location = index - 1;
    printf("%s << \n", exec->command[command_location]);
    while(i < exec->input_count)
    {
        //printf("%s <<\n", exec->command[exec->input_count]);
        input_file = open(exec->command[exec->input_count], O_RDONLY);
        if(input_file == -1)
        {
            perror("minishell error");
            return 0;
        }
        if(ft_strcmp(exec->command[i], "<") == 0 && i == exec->input_count - 1)
        {
         //   printf("dd\n");
            pid = fork();
            if (pid == 0)
                redirect(exec, command_location);
            else
                waitpid(pid, 0, 0);
        }
        i++;
    }
    return (i);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *line;
// 	char **line_parser;
// 	int pid;
// 	char *history;

// 	while((line = readline("Minishell >> ")))
// 	{
// 		line_parser = ft_split(line, ' ');
// 		add_history(line);
// 		if(ft_strcmp(line, "history") == 0)
// 			printf("h\n");
// 		else
//     	{
//       			ft_redirect_input(ft_count_elements(line_parser), line_parser, envp);
// 	  		ft_free(line_parser);
//      		free(line);
// 		}
// 	}	
// 	return (0);
// }