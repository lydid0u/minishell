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

void	handle_built_in_no_exec(t_pipex *pipex, t_copyenv *lst_envp)		;


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
		if (!pipex.prompt)
			break ;
		pipex.prompt = suppresing_quote(pipex.prompt);
		quote_positif(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		if (nbcmd == 1 && is_builtin(pipex.cmd[0]))
			handle_built_in_no_exec(&pipex, lst_envp);
		else
			exec(nbcmd, lst_envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	free_lst(lst_envp);
	return (1);
}

//leaks sur ls | cd