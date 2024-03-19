#include "minishell.h"

t_copyenv *create_node(void)
{
    t_copyenv *node;
	
	node = malloc(sizeof(t_copyenv));
    if (node == NULL)
        return (NULL);
    node->key = NULL;
    node->value = NULL;
    node->next = NULL;

    return node;
}

void key_env(t_copyenv *node, char *key)
{
    if (node != NULL)
    {
        node->key = malloc(ft___strlen(key) + 1);
        ft_strcpy(node->key, key);
    }
}

void value_env(t_copyenv *node, char *value)
{
    if (node != NULL)
    {
        node->value = malloc(ft___strlen(value) + 1);
        ft_strcpy(node->value, value);
    }
}

int	nbr_of_element_in_envp(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
    {

		i++;
    }
	return (i);
}

void create_lst(char **envp)
{
    t_copyenv *head;
    t_copyenv *new;
    t_copyenv *current;
	int i;
	int size;

	i = 0;
	size = nbr_of_element_in_envp(envp);
	head = NULL;
	new = NULL;
	current = NULL;
	while (i < size - 2) // pq - 2??
	{
		new = create_node();
		if (head == NULL)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
    copy_envp(envp, head);
    free_lst(head);
    // t_copyenv *lst = head;
    // while (lst != NULL)
    // {
    //     printf("KEY: {%s}\nVALUE: {%s}\n\n", lst->key, lst->value);
    //     lst = lst->next;
    // }
}

void	copy_envp(char **envp, t_copyenv *lst)
{
	int i;
	int j;
	int k;
	int v;
	char *key;
	char *value;
	t_copyenv *current;

	i = 0;
	current = lst;
	while (envp[i] && current != NULL)
	{
		j = 0;
		k = 0;
		v = 0;
		key = malloc (sizeof(char) * (get_len_of_key(envp[i]) + 1));
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
				value = malloc (sizeof(char) * (get_len_of_value_from_str(envp[i], envp) + 1));
				while (envp[i][j])
				{
					value[v] = envp[i][j];
					j++;
					v++;
				}
				value[v] = '\0';
			}
		}
		value_env(current, value);
		free(key);
		free(value);
		free(current->key);
		free(current->value);
		current = current->next;
		i++;
	}
}

void    free_lst(t_copyenv *lst)
{
    t_copyenv   *nxt;

    while (lst)
    {
        nxt = lst->next;
        free(lst);
        lst = nxt;
    }
}

