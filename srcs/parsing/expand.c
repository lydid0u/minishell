/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:21:09 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 05:21:32 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// une key est valide si:
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

int	get_len_of_value_from_str(char *input, char **envp)
{
	char	*value;
	char	stock;
	int		value_len;
	int		len_key;

	len_key = get_len_of_key(input);
	stock = input[len_key];
	input[len_key] = '\0';
	value = get_value_from_key(input, envp);
	input[len_key] = stock;
	value_len = ft__strlen(value);
	return (value_len);
}

int	get_len_of_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	return (i);
}

int	total_expand(char *input, char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		handle_single_quote(input, &i, &count);
		while (input[i] == '$')
		{
			i++;
			if (is_key_valid(&input[i], envp))
			{
				i += get_len_of_key(&input[i]);
				break ;
			}
			count += get_len_of_value_from_str(&input[i], envp);
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

char	*get_value_from_key(char *key, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = get_len_of_key(&key[i]);
	while (envp[i])
	{
		if (ft_strncmp(key, envp[i], len) == 0)
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*final_string(char *input, char **envp)
{
	int		i;
	int		j;
	int		k;
	char	*value;
	char	*output;

	i = 0;
	j = 0;
	output = malloc(sizeof(char) * (total_expand(input, envp) + 1));
	while (input[i])
	{
		write_single_quote(input, output, &i, &j);
		while (input[i] == '$')
		{
			i++;
			if (is_key_valid(&input[i], envp))
			{
				i += get_len_of_key(&input[i]);
				break ;
			}
			value = get_value_from_key(&input[i], envp);
			printf("VALUE {%s}\n", value);
			k = 0;
			while (value[k])
			{
				output[j] = value[k];
				j++;
				k++;
			}
			i += get_len_of_key(&input[i]);
		}
		if (input[i])
		{
			output[j] = input[i];
			i++;
			j++;
		}
	}
	output[j] = '\0';
	return (free(input), output);
}
