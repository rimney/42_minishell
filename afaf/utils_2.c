/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:29:54 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/01 04:16:58 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c < 58)
		return (1);
	return (0);
}

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	check_env_var(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '$')
	{
		if (str[i])
		{
			while (str[i])
			{
				if (!ft_isupper(str[i]) && !ft_isdigit(str[i]))
					return (0);
				i++;
			}
		}
		else
			return (0);
	}
	return (1);
}

void	parse_env(t_token **lst_token)
{
	t_token	*lst;

	lst = *lst_token;
	while (lst)
	{
		if (contain(lst->value, '$'))
		{
			if (!check_env_var(lst->value))
			{
				printf ("ENV VAR WRONG\n");
				exit(0);
			}
		}
		lst = lst->next;
	}
}
