/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/29 01:46:11 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint() 
{
    printf("\n"); // Affiche une nouvelle ligne
}

void handle_sigterm() {
    printf("\nExiting the shell.\n");
    exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_copyenv		*lst_envp;
	char			*prompt;
	int				nbcmd;

	(void)argc;
	(void)argv;
	// signal(SIGINT, handle_sigint);
	// signal(SIGTERM, handle_sigterm);
	lst_envp = create_lst(envp);
	if (!lst_envp)
		return (1);
	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		pipex.prompt = final_string(prompt, lst_envp);
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
		// 		built_in_export(&tab[1], lst_envp);
		// 	}
		// 	if (strcmp(tab[0], "unset") == 0)
		// 	{
		// 		built_in_unset(&tab[1], lst_envp);			
		// 	}
		// 	if (strcmp(tab[0], "env") == 0)
		// 	{
		// 	    t_copyenv 	*print = lst_envp;
		// 		while (print)
		// 		{
		// 			printf("%s=%s\n", print->key, print->value);
		// 			print = print->next;
		// 		}
		// 	}
		// 	free_tab(tab);
		// }
		// exec(nbcmd, lst_envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	free_lst(lst_envp);
	return (1);
}
