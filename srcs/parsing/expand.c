/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:21:09 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/16 02:16:03 by lboudjel         ###   ########.fr       */
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
		handle_single_quote(&input[i], &i, &count);
		while (input[i] == '$')
		{
			i++;
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
	len = ft_strlen(key);
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
	int	i;
	int	len;
	char *value;

	i = 0;
	len = 0;
	value = 
	while (input[i])
	{
		handle_single_quote(&input[i], &i, &len);
		while (input[i] == '$')
		{
			i++;
			len += get_len_of_value_from_str(&input[i], envp);
			i += get_len_of_key(&input[i]);
		}
		if (input[i])
		{
			i++;
			len++;
		}
	}
	return (len);
}


char	*ft_expand(t_pipex *pipex, char *str, char **envp)
{
	char *new = malloc(sizeof(char) * total_expand(str, envp));
	
	new = 
	// return (new);
}
