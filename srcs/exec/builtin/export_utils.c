/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
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
	if (ft_isdigit(str[0]))
		return (NULL);
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

t_copyenv	*create_node(void)
{
	t_copyenv	*node;

	node = malloc(sizeof(t_copyenv));
	if (!node)
		return (NULL);
	node->key = NULL;
	node->value = NULL;
	node->next = NULL;
	return (node);
}
