/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:20:48 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/29 01:46:35 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quote(char *input, int *i, int *count)
{
	if (input[*i] && input[*i] == '\'')
	{
		(*i)++;
		(*count)++;
		while (input[*i] && input[*i] != '\'')
		{
			(*i)++;
			(*count)++;
		}
		(*i)++;
		(*count)++;
	}
}

void	write_single_quote(char *input, char *output, int *i, int *j)
{
	if (input[*i] && input[*i] == '\'')
	{
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
		while (input[*i] && input[*i] != '\'')
		{
			output[*j] = input[*i];
			(*i)++;
			(*j)++;
		}
		output[*j] = input[*i];
		(*i)++;
		(*j)++;
	}
}

int	is_key_valid(char *key, t_copyenv *lst_envp)
{
	char	*key_env;

	key = get_key_expand(key);
	while (lst_envp)
	{
		key_env = get_key_expand(lst_envp->key);
		if (strcmp(key, key_env) == 0)
			return (free(key_env), free(key), 0);
		lst_envp = lst_envp->next;
		free(key_env);
	}
	return (free(key), 1);
}

char	*get_key_expand(char *str)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	key = malloc(sizeof(char) * (get_len_of_key(str) + 1));
	if (!key)
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
	{
		key[j++] = str[i++];
	}
	key[j] = '\0';
	return (key);
}

void	question_mark(t_pipex *pipex, char *output, int *j)
{
	char	*value;
	int		i;

	i = 0;
	value = ft_itoa(pipex->status_code);
	while (value[i])
	{
		output[*j] = value[i];
		(*j)++;
		i++;
	}
	free(value);
}
