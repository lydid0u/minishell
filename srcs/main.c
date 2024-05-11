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

int	main(int argc, char **argv, char **envp)
{
	t_token			*token;
	char			*prompt;
	int				nbcmd;

	(void)argc;
	(void)argv;
	//isatty();
	t_pipex	*pipex = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	t_copyenv *(lst_envp) = create_lst(envp);
	if (!lst_envp)
		return (1);
	pipex->tab_env = NULL;
	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		add_history(prompt);
		pipex->prompt = final_string(prompt, lst_envp, pipex);
		if (parsing(pipex->prompt))
		{
			pipex->status_code = 2;
			free(pipex->prompt);
			continue ;
		}
		pipex->prompt = add_spaces(pipex->prompt); //COMMENTEE
		if (!pipex->prompt)
			break ;
		pipex->prompt = suppresing_quote(pipex->prompt);
		pipex->cmd = ft_split(pipex->prompt, '|');
		if (!pipex->cmd || !pipex->cmd[0])
		{
			free_tab(pipex->cmd);
			continue ;
		}
		nbcmd = countword(pipex->prompt, '|');
		quote_positif(pipex->prompt);
		token = tokenisation(pipex->cmd[0]); //COMMENTEE
		if (nbcmd == 1 && is_builtin(token->cmd))
		{
			pipex->status_code = 0;
			chevron_no_fork(pipex, token, lst_envp); //COMMENTEE
			free_token(token);
		}
		else
		{
			free_token(token);
			exec(nbcmd, lst_envp, pipex); //COMMENTEE
		}
		free(pipex->prompt);
		free_tab(pipex->cmd);
	}
	int i = -1;
	while (++i < pipex->nbr_heredoc)
		close(pipex->heredoc[i].hd_pipe[0]);
	free_lst(lst_envp);
	free_tab(pipex->tab_env);
	printf("exit\n");
	rl_clear_history();
	return (pipex->status_code);
}

// pipex->cmd = on split au pipe -> je recupere chaque commande