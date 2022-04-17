/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 22:36:22 by rimney            #+#    #+#             */
/*   Updated: 2022/04/16 22:40:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(char *path)
{
    if(chdir(path) == 0)
    {
        ft_pwd();
        return (1);
    }
    else
    {
        printf("failed\n");
        return (0);
    }
}