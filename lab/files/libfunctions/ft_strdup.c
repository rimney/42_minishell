/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:43:32 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 15:18:25 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char    *ft_strdup(char *s1,  int flag)
{
    int i;
    int j;
    char *str;

    i = 0;
    j = 0;
    if(flag)
    {
        str = malloc(sizeof(char) * strlen(s1) - 1);
        while(i < ft_strlen(s1) - 1)
        {
            if(s1[i] == '\"')
            {
                printf("flag\n");
                i++;
            }
            str[j] = s1[i];
            i++;
            j++;
        }
        str[j] = '\0';
        return (str);
    }
    else
    {
        str = malloc(sizeof(char) * strlen(s1) + 1);
        printf("%lu<<\n", strlen(s1));
        while(s1[i])
        {
            str[i] = s1[i];
            i++;
        }
        str[i] = '\0';
    }
    return (str);
}
