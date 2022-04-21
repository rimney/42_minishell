/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:48:10 by rimney            #+#    #+#             */
/*   Updated: 2022/04/21 02:55:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *ft_test(char *str, char *src)
{
    int i;
    int j;
    char *temp;

    temp = malloc(sizeof(char) * strlen(str) + strlen(src) + 1);
    i = 0;
    j = 0;
    while(src[i])
    {
        temp[i] = src[i];
        i++;
    }
    while(str[j])
    {
        temp[i] = str[j];
        i++;
        j++;
    }
    temp[i] = '\0';
    return (temp);
}

int main(int argc, char **argv)
{
    if(argc == 3)
    {
        printf("%s", ft_test(argv[1], argv[2]));
    }
    return (0);
}