/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:53:22 by rimney            #+#    #+#             */
/*   Updated: 2022/05/20 02:32:50 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int main(int argc, char **argv, char **envp)
{
    char *str;

    str = ft_check_command(envp, argv[1]);
    printf("%s |\n", str);
    return (0);
}
    