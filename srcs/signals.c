/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:39:55 by lboudjel          #+#    #+#             */
/*   Updated: 2024/04/29 17:29:43 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	backslash(int signal)
{
	if (signal == SIGQUIT)
		exit(131);
	if (signal == SIGINT)
		exit(130);
}

void	ctrl_c(int signal)
{
	t_pipex	*pipex;

	if (signal == SIGINT)
	{
		pipex = starton();
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		pipex->status_code = 130;
	}
}

t_pipex	*starton(void)
{
	static t_pipex	pipex;

	return (&pipex);
}
