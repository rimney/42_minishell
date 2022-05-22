/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:53:22 by rimney            #+#    #+#             */
/*   Updated: 2022/05/20 19:14:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int count_env(char **envp)
{
    int i;

    i  = 0;
    while (envp[i])
        i++;

    return (i);
}


int main(int argc, char **argv, char **envp)
{
    char *str;

    printf("%d\n", count_env(envp));
    return (0);
}
    