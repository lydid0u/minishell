/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:18:38 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/26 22:17:31 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	print_s(va_list args)
{
	char	*s;

	s = (char *)va_arg(args, char *);
	if (s == NULL)
		return (ft_putstr("(null)"));
	else
		ft_putstr(s);
	return (ft_strlen_printf(s));
}
