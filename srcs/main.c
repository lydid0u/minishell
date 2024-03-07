/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/07 04:24:09 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**cmd;
	int		nbcmd;

	(void)envp;
	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		if (parsing(prompt))
			continue ;
		cmd = ft_split(prompt, '|');
		nbcmd = countword(prompt, '|');
		pipex(nbcmd, cmd, envp);
		free(prompt);
		free_tab(cmd);
	}
	return (1);
}
//free cmd dans le pipex
