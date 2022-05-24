/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 21:08:56 by rimney            #+#    #+#             */
/*   Updated: 2022/05/24 23:54:42 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  s_list
{
    char *str;
    struct s_list *next;
} t_list;

int ft_count_list(t_list *list)
{
    int i;

    i = 0;
    while(list)
    {
        list = list->next;
        i++;
    }
    return (i);
}

t_list  *ft_add_front(t_list *list, char *str)
{
    t_list *temp;

    temp = malloc(sizeof(t_list));
    temp->str = strdup(str);
    temp->next = list;
    list = temp; 
    return (list);
}

t_list  *ft_add_back(t_list *list, char *str)
{
    t_list *temp, *tmp = list;

    if(!list)
    {
        temp = malloc(sizeof(t_list));
        temp->str = strdup(str);
        temp->next = NULL;
        return (temp);
    }
    temp = malloc(sizeof(t_list));
    temp->str = strdup(str);
    temp->next = 0;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = temp;
    return (list);
}

// void    del_midd_node(t_list *list ,int position)
// {
//     t_list temp1 = list;
//     t_list temp2 = list;

//     if(list == NULL)
//         printf("The list is already Empty\n");
//     else if (position == 1)
//     {
//         *list = temp1->link;
//         free(temp1);
//         temp1 = NULL;
//     }
//     else
//     {
//         while (position != 1)
//         {
//             temp2 = temp1;
//             temp1 = temp1->link;
//             position--;
//         }
//         temp2->link = temp1->link;
//         free(temp1);
//         temp1 = NULL;
//     }
// }

t_list  *ft_list_del_element(t_list *list, int index)
{
    t_list  *tmp = list;

    int     i;

    i = 1;
    if (index != 0)
    {
        while(tmp)
        {
            if(index == i)
            {
                printf("<< %s >>\n", tmp->next->str);
                free(tmp->str);
                tmp->next = tmp->next->next;
                break;
            }
            tmp = tmp->next;
            i++;
        }
    }
    else
    {
        printf("<< %s >>\n", tmp->str);
        list = list->next;
    }
    return (list);
}

void    ft_destroy_list(t_list *list)
{
    while(list)
    {
        free(list->str);
        list = list->next;
    }
    free(list);
}
int main(int argc, char **argv, char **envp)
{
    t_list *list;
    t_list *temp;
    list = NULL;
    list = ft_add_back(list, "argument 1\n");
    list = ft_add_back(list, "argument 2\n");
    list = ft_add_back(list, "argument 3\n");
    list = ft_add_back(list, "argument 4\n");
    list = ft_add_back(list, "argument 5\n");
    temp = list;
    list = ft_list_del_element(list, 1);
    while(temp)
    {
        printf("%s", temp->str);
        temp = temp->next;
    }
    ft_destroy_list(list);
    //system("leaks a.out");
 
    return (0);
}