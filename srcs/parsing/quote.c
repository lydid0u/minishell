/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:11:21 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/16 01:31:23 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
checkquotes
	verifie si les quotes sont bien fermees
	
	input = '"aaaaaa"'
		return (0);

	input = 123 '"'adasasdasdasds"
		return (1);
*/

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == '\0')
				return (1);
		}
	}
	return (0);
}

//mettre tout les char dans les quotes en negatifs pour traiter juste les quotes
	//voir avec juju le cas des plusiuers quotes pq jai un char bizarre qui pop
void	quote_negatif(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
			{
				input[i] = input[i] * -1;
				i++;
			}
		}
		if (input[i])
			i++;
	}
	printf("apres : {%s}\n", input);
}

void	quote_positif(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] < 0)
			input[i] *= -1;
		i++;
	}
}

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
	}
}

//effacer les quotes pour gerer la string
// int	suppresing_quote(char *input)
// {
// 	//
// }