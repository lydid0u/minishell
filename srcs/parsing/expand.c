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

void	i_and_count_plus_plus(int *i, int *count, int i_plus, int count_plus)
{
	(*i) += i_plus;
	(*count) += count_plus;
}

int	total_expand(char *input, t_copyenv *lst_envp, t_pipex *pipex, int i)
{
	int (count) = 0;
	char *(value) = ft_itoa(pipex->status_code);
	while (input[i])
	{
		handle_single_quote(input, &i, &count);
		while (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				i_and_count_plus_plus(&i, &count, 2, ft_strlen(value));
				continue ;
			}
			else if (!ft_isalnum(input[i + 1]) && input[i] != '_')
			{
				i_and_count_plus_plus(&i, &count, 2, 2);
				break ;
			}
			i_and_count_plus_plus(&i, &count, 1, 1);
			if (is_key_valid(&input[i], lst_envp))
			{
				i += get_len_of_key(&input[i]);
				continue ;
			}
			count += get_len_of_value_from_str(&input[i], lst_envp);
			i += get_len_of_key(&input[i]);
		}
		if (input[i] == '\'')
			continue ;
		if (input[i])
			i_and_count_plus_plus(&i, &count, 1, 1);
	}
	return (free(value), count);
}
