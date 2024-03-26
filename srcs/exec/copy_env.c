/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/26 00:17:26 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	key_env(t_copyenv *node, char *key)
{
	if (node != NULL)
	{
		node->key = malloc(ft__strlen(key) + 1);
		strcpy(node->key, key);
	}
}

void	value_env(t_copyenv *node, char *value)
{
	if (node != NULL)
	{
		node->value = malloc(ft__strlen(value) + 1);
		strcpy(node->value, value);
	}
}

int	nbr_of_element_in_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

t_copyenv	*create_lst(char **envp)
{
	t_copyenv	*head;
	t_copyenv	*new;
	t_copyenv	*current;
	int			i;
	int			size;

	i = 0;
	size = nbr_of_element_in_envp(envp);
	head = NULL;
	new = NULL;
	current = NULL;
	while (i < size - 1)
	{
		new = create_node();
		if (head == NULL)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	current = head;
	copy_envp(envp, current);
	return (head);
}

void	copy_envp(char **envp, t_copyenv *lst)
{
	int			i;
	int			j;
	int 		size;
	t_copyenv	*current;

	i = 0;
	current = lst;
	while (envp[i] && current)
	{
		j = 0;
		current->key = get_key(envp[i]);
		j += (ft__strlen(current->key) + 1);
		size = ft__strlen(envp[i]);
		current->value = malloc((sizeof(char) * size) + 1);
		j = 0;
		while (envp[i][j])
		{
			current->value[j] = envp[i][j];
			j++;
		}
		current->value[j] = '\0';
		current = current->next;
		i++;
	}
}
