/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/06 00:59:31 by rimney           ###   ########.fr       */
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
	int fd = open(argv[1], O_RDWR | O_APPEND);
	write(fd, "ggg1\n", 5);
	return (0);
}