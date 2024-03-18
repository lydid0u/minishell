/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 05:13:10 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/18 05:13:39 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	func(char *str, int *i)
{
	printf("ici la [%c]\n", &str[0]);
}

int	main(void)
{
	char str[100] = "moha231234546546565med";

	int i = 0;
	while (str[i] && str[i] != '1')
		i++;
	printf("jenvoie a func: {%s}\n", &str[i]);
	func(&str[i], &i);
}
