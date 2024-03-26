/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 01:21:09 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/26 04:03:04 by lboudjel         ###   ########.fr       */
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

char	*get_value_from_key(char *key, t_copyenv *lst_envp)
{
	int	i;
	int	len;
	char	*key_env;

	i = 0;
	while (lst_envp)
	{
		key_env = get_key(lst_envp->key);
		len = get_len_of_key(key_env);
		if (ft_strcmp(key, key_env) == 0)
		{
			printf("LST VALUE %s", lst_envp->value);
			return (free(key_env), lst_envp->value);
		}
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
	value_len = ft__strlen(value);
	printf("VALUE {%s}\n", value);
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

int	total_expand(char *input, t_copyenv *lst_envp)
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
			if (is_key_valid(&input[i], lst_envp))
			{
				printf("la\n");
				i += get_len_of_key(&input[i]);
				break ;
			}
			count += get_len_of_value_from_str(&input[i], lst_envp);
			i += get_len_of_key(&input[i]);
		}
		if (input[i] == '$')
			continue;
		if (input[i])
		{
			i++;
			count++;
		}
	}
	printf("COUNT {%i}\n", count);
	return (count);
}

char	*final_string(char *input, t_copyenv *lst_envp)
{
	int		i;
	int		j;
	int		k;
	char	*value;
	char	*output;
	char 	*key;

	i = 0;
	j = 0;
	output = malloc(sizeof(char) * (total_expand(input, lst_envp) + 1));
	if (!output)
		return (NULL);
	while (input[i])
	{
		write_single_quote(input, output, &i, &j);
		while (input[i] == '$')
		{
			i++;
			key = get_key_expand(&input[i]);
			if (is_key_valid(key, lst_envp) != 0)
			{
				printf("la string {%s}\n", key);
				i += get_len_of_key(key);
				free(key);
				break ;
			}
			value = get_value_from_key(key, lst_envp);
			k = 0;
			while (value[k])
			{
				output[j] = value[k];
				j++;
				k++;
			}
			i += get_len_of_key(&input[i]);
			free(key);
		}
		if (input[i] == '$')
			continue;
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


	// while (input[i])
	// {
	// 	write_single_quote(input, output, &i, &j);
	// 	while (input[i] == '$')
	// 	{
	// 		i++;
	// 		if (is_key_valid(&input[i], envp))
	// 		{
	// 			printf("HERE dans le if is key valid\n");
	// 			i += get_len_of_key(&input[i]);
	// 			break ;
	// 		}
	// 		// ft_strjoin(&output[j], get_value_from_key(&input[i], envp));
	// 		// printf("---------- %s\n", output);
	// 		// while (output[j])
	// 			// j++;
	// 		value = malloc(sizeof(char) * (get_len_of_value_from_str(&input[i], envp) + 1));
	// 		if (!value)
	// 			return (NULL);
	// 		value = get_value_from_key(&input[i], envp);
	// 		printf("VALUE {%s}\n", value);
	// 		k = 0;	
	// 		while (value[k])
	// 		{
	// 			output[j] = value[k];
	// 			j++;
	// 			k++;
	// 		}
	// 		printf("INPUT I %s\n", &input[i]);
	// 		i += get_len_of_key(&input[i]);
	// 	}

