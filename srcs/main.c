/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/16 02:10:07 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	char			*prompt;
	int				nbcmd;

	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		ft_expand(&pipex, prompt, envp);
		if (parsing(prompt))
			continue ;
		pipex.prompt = add_spaces(prompt);
		if (!pipex.prompt)
			break ;
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		printf("pipex.prompt {%s}\n", pipex.prompt);
		exec(nbcmd, envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	return (1);
}
