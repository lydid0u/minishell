/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:40:48 by lboudiel          #+#    #+#             */
/*   Updated: 2024/03/30 08:03:00 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	printf("\n"); // Affiche une nouvelle ligne
}

void	handle_sigterm(void)
{
	printf("\nExiting the shell.\n");
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_copyenv		*lst_envp;
	char			*prompt;
	int				nbcmd;
	char			**tab;

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
		if (!pipex.prompt)
			break ;
		quote_positif(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		{
			tab = ft_split(pipex.cmd[0], ' ');
			if (strcmp(tab[0], "export") == 0)
			{
				built_in_export(&tab[1], lst_envp);
			}
			if (strcmp(tab[0], "unset") == 0)
			{
				built_in_unset(&tab[1], lst_envp);
			}
			if (strcmp(tab[0], "echo") == 0)
			{
				built_in_echo(&tab[1]);
			}
			if (strcmp(tab[0], "pwd") == 0)
			{
				built_in_pwd(lst_envp);
			}
			if (strcmp(tab[0], "cd") == 0)
			{
				built_in_cd(&tab[1], lst_envp);
			}
			if (strcmp(tab[0], "env") == 0)
			{
				built_in_env(lst_envp);
			}
			free_tab(tab);
		}
		exec(nbcmd, lst_envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	printf("la\n");
	free_lst(lst_envp);
	return (1);
}
