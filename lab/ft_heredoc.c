/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 22:25:23 by rimney            #+#    #+#             */
/*   Updated: 2022/05/09 23:55:27 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_heredoc(char **argv)
{
    char *delimiter;
    char *line;


    if(ft_strcmp(argv[2], "<<") == 0)
    {
        delimiter = strdup(argv[3]);
        printf("%s\n", delimiter);
        while(1)
        {
            line = readline("hereddoc> ");
            if(ft_strcmp(line, delimiter) == 0)
            {
                printf("OUT!\n");
                return (1);
            }
            free(line);
        }
    }
    return(0); 
}

int main(int argc, char **argv)
{
    if(!ft_heredoc(argv))
    return (0);
}