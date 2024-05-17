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
