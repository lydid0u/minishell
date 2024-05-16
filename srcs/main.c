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

int	main_parsing(char *prompt, t_pipex *pipex, t_copyenv *lst_envp)
{
	add_history(prompt);
	pipex->prompt = final_string(prompt, lst_envp, pipex, 0);
	if (parsing(pipex->prompt))
	{
		pipex->status_code = 2;
		free(pipex->prompt);
		return (2);
	}
	pipex->prompt = add_spaces(pipex->prompt);
	if (!pipex->prompt)
		return (1);
	pipex->prompt = suppresing_quote(pipex->prompt);
	pipex->cmd = ft_split(pipex->prompt, '|');
	if (!pipex->cmd || !pipex->cmd[0])
	{
		free(pipex->prompt);
		free_tab(pipex->cmd);
		return (2);
	}
	pipex->nbr_cmd = countword(pipex->prompt, '|');
	here_doc(pipex, NULL, lst_envp, pipex->prompt);
	quote_positif(pipex->prompt);
	return (0);
}

void	free_n_leave(t_pipex *pipex, t_copyenv *lst_envp)
{
	free_lst(lst_envp);
	free_tab(pipex->tab_env);
	printf("exit\n");
	rl_clear_history();
}

void	main_exec(t_pipex *pipex, t_token *token, t_copyenv *lst_envp)
{
	if (pipex->nbr_cmd == 1 && is_builtin(token->cmd))
	{
		pipex->status_code = 0;
		chevron_no_fork(pipex, token, lst_envp);
		free_token(token);
	}
	else
	{
		free_token(token);
		exec(lst_envp, pipex);
	}
}

int	mini_main(t_pipex *pipex, t_copyenv *lst_envp)
{
	t_token	*token;
	char	*prompt;
	int		ret;

	while (1)
	{
		prompt = readline("minishell> ");
		if (!prompt)
			break ;
		if (!*prompt)
			continue ;
		ret = main_parsing(prompt, pipex, lst_envp);
		if (ret == 1)
			break ;
		if (ret == 2)
			continue ;
		token = tokenisation(pipex->cmd[0]);
		main_exec(pipex, token, lst_envp);
		free(pipex->prompt);
		free_tab(pipex->cmd);
		free_heredoc(pipex);
	}
	free_n_leave(pipex, lst_envp);
	return (pipex->status_code);
}

int	main(int argc, char **argv, char **envp)
{
	if (!isatty(0))
		return (1);
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrl_c);
	t_pipex *(pipex) = starton();
	t_copyenv *(lst_envp) = create_lst(envp);
	if (!lst_envp)
		return (1);
	mini_main(pipex, lst_envp);
	return (0);
}

// pipex->cmd = on split au pipe -> je recupere chaque commande