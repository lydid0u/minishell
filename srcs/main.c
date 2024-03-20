/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/20 03:20:13 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_copyenv		*copyenv;
	char			*prompt;
	int				nbcmd;

	(void)argc;
	(void)argv;
	copyenv = create_lst(envp);
	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		pipex.prompt = final_string(prompt, envp);
		if (parsing(pipex.prompt))
			continue ;
		pipex.prompt = add_spaces(pipex.prompt);
		if (!pipex.prompt)
			break ;
		built_export(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		{
			char **tab = ft_split(pipex.cmd[0], ' ');
			if (strcmp(tab[0], "export") == 0)
			{
				printf("aa\n");
				built_in_export(&tab[1], copyenv);
			}
		}
		// exec(nbcmd, envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	return (1);
}
