/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:10 by rimney            #+#    #+#             */
/*   Updated: 2022/04/14 23:28:44 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    char *line;
    char cwd[256];
    while(1)
    {
        printf(GREEN_COLOR);
        line = readline("BomusShell$> \033[0;37m");
        if(ft_strcmp(line, "pwd") == 0)
           ft_pwd();
        // else if(ft_strcmp(line, "echo"))
        // {
        //     if(ft_strcmp(argv[2], "-n") == 0)
        //         ft_echo(argv[3], 1);
        //     else
        //         ft_echo(argv[3], 0);
        // }
        printf("%s\n", line);
    }
    return (0);
}