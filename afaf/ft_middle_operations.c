/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:44:08 by rimney            #+#    #+#             */
/*   Updated: 2022/06/21 17:28:28 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_apply_pipe_middle(t_exec *exec, t_pipe *tpipe, int i)
{
    int fd;

    fd = -1;
	exec->pipe_count = ft_count_till_other_token(exec, i, "|");
	fd = open(exec->command[i - 1], O_RDWR);
	if(exec->command[i + 2] && ft_is_another_flag(exec, i + 2) == APPEND)
	{
		ft_dup_and_redirect(fd, exec, i + 2);
		i += 4;
	}
	if((exec->command[i + 2] && ft_is_another_flag(exec, i + 2) != HEREDOC
		&& ft_is_another_flag(exec, i + 1) != REDIRIN && ft_is_another_flag(exec, i + 2) != REDIROUT)
			|| exec->command[i + 2] == NULL)
	{
		if(exec->command[i + 2] && ft_strcmp(exec->command[i + 2], ">") == 0)
			printf("SIKE\n");
		else
		{
			printf("sss\n");
			ft_mini_pipe(exec, tpipe, fd, i - 1, i);
		}
			
		i += exec->pipe_count;
	}
    return (i);
}

int ft_apply_redin_middle(t_exec *exec, t_pipe *tpipe,  int i)
{
	if(exec->command[i] && ft_is_another_flag(exec, i) == REDIRIN && exec->pipe_count == 2)
	{
		if(exec->command[i + 2] && exec->command[i + 4])
		{
			if(ft_strcmp(exec->command[i + 2], "|") && ft_strcmp(exec->command[i + 4], "<") == 0)
			{
				while(ft_strcmp(exec->command[i], "<") == 0)
					i += 4;
			}
		}
		if(exec->command[i + 2] == NULL)
		{
			exec->input_count = ft_count_till_other_token(exec, i, "<");
			ft_redirect_input(exec, tpipe, i, i - 1);
		
		}
		if(exec->command[i + 2])
			i += exec->input_count - 1;
		else	
			i += exec->input_count;
	}
	return i;	
}

int	ft_middle_rediout(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;

	if(exec->command[i] && ft_is_another_flag(exec, i) == REDIROUT && exec->pipe_count == 2)
	{
		tpipe->fd[0] = 0;
	//	printf("%s <<<<<<< herehre\n", exec->command[i - exec->pipe_count - 1]);
		fd = open(exec->command[i - exec->pipe_count - 1], O_RDWR);
		ft_dup_and_redirect(fd, exec, i);
		if(exec->command[i + 2])
			i += exec->redirection_count - 1;
		else
		 i += exec->redirection_count - 1;
	}
	return (i);
}