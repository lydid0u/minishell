/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 04:03:20 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/25 23:55:00 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc((sizeof(char) * i) + 1);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	if (i == 0)
		return (free(key), NULL);
	key[i] = '\0';
	return (key);
}

void	add_node_export_back(t_copyenv *lst, t_copyenv *new_node)
{
	while (lst->next)
	{
		lst = lst->next;
	}
	lst->next = new_node;
}

void	free_lst(t_copyenv *lst)
{
	t_copyenv	*current;
	t_copyenv	*nxt;

	current = lst;
	while (current)
	{
		nxt = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = nxt;
	}
}

t_copyenv	*create_node(void)
{
	t_copyenv	*node;

	node = malloc(sizeof(t_copyenv));
	if (node == NULL)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}
