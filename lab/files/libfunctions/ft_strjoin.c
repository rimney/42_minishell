/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 01:41:29 by rimney            #+#    #+#             */
/*   Updated: 2022/05/30 20:41:07 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char    *ft_strjoin(char *s1, char *s2, char *s3)
{
    int i;
    char *str;
    int len;

    i = 0;
    len = 0;
    str = malloc(sizeof(char) * strlen(s1) + strlen(s2) + strlen(s3) + 1);
    while(s1[i])
    {
        str[len] = s1[i];
        i++;
        len++;
    }
    i = 0;
    while(s2[i])
    {
        str[len] = s2[i];
        i++;
        len++;
    }
    i = 0;
    while(s3[i])
    {
        str[len] = s3[i];
        i++;
        len++;
    }
    str[len + 1] = '\0';
    return (str);
}