/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:00:29 by atarchou          #+#    #+#             */
/*   Updated: 2022/05/28 16:29:31 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (i <= size)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;
	size_t	j;

	if (!s)
		return (NULL);
	i = 0;
	j = ft_strlen(s);
	if (start > j)
		return (NULL);
	tmp = ft_strnew(len);
	if (tmp == NULL)
		return (NULL);
	while (i < len && s[start])
	{
		tmp[i] = s[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	print_lst(t_token *lst)
{
	while (lst)
	{
		printf("value = : %s\ntype = %d\n\n", lst->value, lst->type);
		lst = lst->next;
	}
}

void	print_redir(t_redir *lst)
{
	while (lst)
	{
		printf("file = : %s\nredir type = %d\n\n", lst->file, lst->type);
		lst = lst->next;
	}
}
