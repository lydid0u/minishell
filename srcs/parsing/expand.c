/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:21:09 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 07:07:13 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// une key est valide :
// tant que il y a des lettres et/ou qu'il des tirets du bas et/ou chiffres
// si elle commence par un chiffre

/*
	input	= {$BLABLA 123 $USER $SDADSADSADSASAD}
	output	= { 123 lboudjel }
	input	= {$BLABLA 123 $USER$SDADSADSADSASAD}
	output	= { 123 lboudjel}
	input	= 
----------------------------------

key = USER
value = lboudjel 

*/
// avion $USER bla
// USER bla

char	*get_value_from_key(char *key, t_copyenv *lst_envp)
{
	int		len;
	char	*key_env;

	while (lst_envp)
	{
		key_env = get_key(lst_envp->key);
		len = get_len_of_key(key_env);
		(void)len;
		if (ft_strcmp(key, key_env) == 0)
			return (free(key_env), lst_envp->value);
		free(key_env);
		lst_envp = lst_envp->next;
	}
	return (NULL);
}

int	get_len_of_value_from_str(char *input, t_copyenv *lst_envp)
{
	char	*value;
	char	stock;
	int		value_len;
	int		len_key;

	len_key = get_len_of_key(input);
	stock = input[len_key];
	input[len_key] = '\0';
	value = get_value_from_key(input, lst_envp);
	input[len_key] = stock;
	value_len = ft_strlen(value);
	return (value_len);
}

int	get_len_of_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_' || key[i] == '?'))
		i++;
	return (i);
}

int	total_expand(char *input, t_copyenv *lst_envp)
{
	int (i) = 0;
	int (count) = 0;
	while (input[i])
	{
		handle_single_quote(input, &i, &count);
		while (input[i] == '$')
		{
			i++;
			count++;
			if (is_key_valid(&input[i], lst_envp))
			{
				i += get_len_of_key(&input[i]);
				continue ;
			}
			count += get_len_of_value_from_str(&input[i], lst_envp);
			i += get_len_of_key(&input[i]);
		}
		if (input[i])
		{
			i++;
			count++;
		}
	}
	return (count);
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

/*
char	*final_string(char *input, t_copyenv *lst_envp, t_pipex *pipex)
{
	int		k;
	char	*value;
	char	*output;
	char	*key;

	int (i) = 0;
	int (j) = 0;
	output = malloc(sizeof(char) * (total_expand(input, lst_envp)) + 1);
	if (!output)
		return (NULL);
	while (input[i])
	{
		write_single_quote(input, output, &i, &j);
		while (input[i] == '$')
		{
			if (input[i + 1] == ' ' || input[i + 1] == '\t'
				|| input[i + 1] == '\0' || input[i + 1] == '"')
			{
				output[j++] = input[i++];
				break ;
			}
			i++;
			if (input[i] == '?')
			{
				char *v = ft_itoa(pipex->status_code);
				for (int r = 0; v[r]; r++)
					output[j++] = v[r];
				free(v);
				i++;
				continue ;
			}
			key = get_key_expand(&input[i]);
			if (!key)
				return (NULL);
			if (is_key_valid(key, lst_envp) != 0)
			{
				i += get_len_of_key(key);
				free(key);
				continue ;
			}
			value = get_value_from_key(key, lst_envp);
			k = 0;
			while (value[k])
				output[j++] = value[k++];
			i += get_len_of_key(&input[i]);
			free(key);
		}
		if (input[i])
			output[j++] = input[i++];
	}
	output[j] = '\0';
	return (free(input), output);
}
*/