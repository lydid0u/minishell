/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/26 03:41:52 by lboudjel         ###   ########.fr       */
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
		pipex.prompt = final_string(prompt, copyenv);
		if (parsing(pipex.prompt))
			continue ;
		pipex.prompt = add_spaces(pipex.prompt);
		printf("output {%s}\n", pipex.prompt);
		if (!pipex.prompt)
			break ;
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		// {
		// 	char **tab = ft_split(pipex.cmd[0], ' ');
		// 	if (strcmp(tab[0], "export") == 0)
		// 	{
		// 		built_in_export(&tab[1], copyenv);
		// 	}
		// 	if (strcmp(tab[0], "unset") == 0)
		// 	{
		// 		built_in_unset(&tab[1], copyenv);			
		// 	}
		// 	if (strcmp(tab[0], "env") == 0)
		// 	{
		// 	    t_copyenv 	*print = copyenv;
		// 		while (print)
		// 		{
		// 			printf("%s=%s\n", print->key, print->value);
		// 			print = print->next;
		// 		}
		// 	}
		// 	free_tab(tab);
		// }
		// exec(nbcmd, envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	// free_lst(copyenv);
	return (1);
}
