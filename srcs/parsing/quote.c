/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:11:21 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/23 00:27:26 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

""''''''''''gfhfg'gfh'lalalala"

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

// effacer les quotes pour gerer la string plus tard par exemple dans echo
char	*suppresing_quote(char *input)
{
	char	quote;
	char	*output;

	int (i) = 0;
	int (j) = 0;
	output = malloc(sizeof(char) * (ft_strlen(input)) + 1);
	if (!output)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				output[j++] = input[i++];
			i++;
		}
		if (input[i] == '\'' || input[i] == '"')
			continue ;
		if (input[i])
			output[j++] = input[i++];
	}
	output[j] = '\0';
	return (free(input), output);
}
