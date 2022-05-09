/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/08 19:19:02 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	ft_append(char **argv, char *str, int fd)
// {
//     if(fd < 0)
//     {
//         printf("file discreptor error\n");
//         return ;
//     }
//     fd = open(W_ONLY)
// }

int	main(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">>") == 0)
	{
		fd = open(argv[2], O_RDWR);
		if(fd == -1)
		{
			fd = open(argv[2], O_CREAT, 0644);
		}
		while(1)
		{
			fd = open(argv[2], O_RDWR | O_APPEND, 0644);
			line = readline("");
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
		}
	}
	else
	{
		fd = open(argv[1], O_RDWR | O_APPEND);
		write(fd, "test\n", 5);
	}
	return (0);
}