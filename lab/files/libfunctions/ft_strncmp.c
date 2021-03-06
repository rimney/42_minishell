/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:28:45 by rimney            #+#    #+#             */
/*   Updated: 2022/05/30 20:41:11 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int ft_strncmp(char *s1, char *s2, int n)
{
    int i;

    i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
        i++;
    return (s1[i] - s2[i]);
}