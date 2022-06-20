/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_middle_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:44:08 by rimney            #+#    #+#             */
/*   Updated: 2022/06/20 20:00:22 by rimney           ###   ########.fr       */
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
		printf("PASSS\n");
		ft_dup_and_redirect(fd, exec, i + 2);
		i += 4;
	}
	if((exec->command[i + 2] && ft_is_another_flag(exec, i + 2) != HEREDOC
		&& ft_is_another_flag(exec, i + 2) != REDIROUT && ft_is_another_flag(exec, i + 1) != REDIRIN)
			|| exec->command[i + 2] == NULL)
	{
		printf("%d <<<<<<< \n", exec->pipe_count);
		ft_mini_pipe(exec, tpipe, fd, i - 1, i);
		i += exec->pipe_count;
				//exec->pipe_count = ft_count_till_other_token(exec, i, "|");
	}
    return (i);
}