/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 03:11:21 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/07 04:41:51 by lboudjel         ###   ########.fr       */
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

void	quote_negatif(char *input)
{
	//voir avec juju le cas des plusiuers quotes pq jai un char bizarre qui pop
	int i;
	char quote;
	
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

int	parsing(char *input)
{
	char	*output;

	if (check_quotes(input))
	{
		ft_printf("bash: error with the quotes\n");
		return (1);
	}
	output = add_spaces(input);
	if (!output)
		return (1);
	if (check_token(input))
		return (1);
	// quote_negatif(input);
	return (0);
}
