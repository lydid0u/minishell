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

void	handle_sigterm(void)
{
	printf("\nExiting the shell.\n");
	exit(EXIT_SUCCESS);
}

void	print_token(t_pipex *pipex)
{
    printf("\nCommand: %s\n", pipex->token->cmd);
    for (int i = 0; i < pipex->token->arg_count; i++) 
    {
    	printf( "argument : %s\n", pipex->token->tabargs[i]);
	}
    printf("\n");
    for (int i = 0; i < pipex->token->file_count; i++) 
    {
        printf("Redirection: %d\n", pipex->token->tabredir[i]);
        printf("File: %s\n", pipex->token->tabfiles[i]);
    }
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	t_token			*token;
	t_copyenv		*lst_envp;
	char			*prompt;
	int				nbcmd;
	(void)argc;
	(void)argv;
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
		pipex.prompt = final_string(prompt, lst_envp, &pipex);
		if (parsing(pipex.prompt))
		{
			pipex.status_code = 2;
			free(pipex.prompt);
			continue ;
		}
		pipex.prompt = add_spaces(pipex.prompt);
		if (!pipex.prompt)
			break ;
		pipex.prompt = suppresing_quote(pipex.prompt);
		pipex.arg_cmd = ft_split(pipex.prompt, '|');
		if (!pipex.arg_cmd || !pipex.arg_cmd[0])
		{
			free_tab(pipex.arg_cmd);
			continue ;
		}
		nbcmd = countword(pipex.prompt, '|');
		quote_positif(pipex.prompt);
		#if DEBUG
			printf("PROMPT IS [%s]\n", pipex.prompt);
		#endif
		token = tokenisation(pipex.arg_cmd[0]);
		if (nbcmd == 1 && is_builtin(token->cmd))
		{
			pipex.status_code = 0;
			chevron_no_exec(&pipex, token, lst_envp);
			free_token(token);
		}
		else
		{
			free_token(token);
			exec(nbcmd, lst_envp, &pipex);
		}
		free(pipex.prompt);
		free_tab(pipex.arg_cmd);
	}
	free_lst(lst_envp);
	return (pipex.status_code);
}
