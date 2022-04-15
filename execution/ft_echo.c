/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 02:44:37 by rimney            #+#    #+#             */
/*   Updated: 2022/04/14 23:17:00 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void       ft_echo(char *str, int flag)
{
    int i = 0;
    int j = 0;
    if(flag == 1)
    {
        while(str[i] != '\n')
            i++;
        while(j < i)
        {
            printf("%c", str[j]);
            j++;
        }
    }
    if(flag == 0)
        printf("%s", str);
}
