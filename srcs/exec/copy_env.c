/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:07:28 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/24 02:42:09 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_copyenv *lst = head;
	copy_envp(envp, lst);
	return (head);
	// free_lst(head);
}

void	copy_envp(char **envp, t_copyenv *lst)
{
	int			i;
	int			j;
	int			k;
	int			v;
	char		*key;
	char		*value;
	t_copyenv	*current;
	int lentoalloc; 

	i = 0;
	current = lst;
	while (envp[i] && current != NULL)
	{
		j = 0;
		k = 0;
		v = 0;
		key = malloc(sizeof(char) * (get_len_of_key(envp[i]) + 1));
		while (envp[i][j] && current)
		{
			key[k] = envp[i][j];
			j++;
			k++;
			if (envp[i][j] == '=')
			{
				key[k] = '\0';
				key_env(current, key);
				j++;
				lentoalloc = ft_strlen(&envp[i][j]);
				value = malloc(sizeof(char) * (lentoalloc + 1));
				while (envp[i][j])
					value[v++] = envp[i][j++];
				value[v] = '\0';
			}
		}
		value_env(current, value);
		free(key);
		free(value);
		// free(current->key);
		// current->key = NULL;
		// free(current->value);
		// current->value = NULL;
		current = current->next;
		i++;
	}
}

void	free_lst(t_copyenv *lst)
{
	t_copyenv *current;
	t_copyenv *nxt;

	current = lst;
	while (current)
	{
		nxt = current->next;
		free(current);
		free(current->key);
		free(current->value);
		current = nxt;
	}
}
