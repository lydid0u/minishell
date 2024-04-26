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
    	printf( "argument : %s\n", pipex->token->args[i]);
	}
    printf("\n");
    for (int i = 0; i < pipex->token->file_count; i++) 
    {
        printf("Redirection: %d\n", pipex->token->redir[i]);
        printf("File: %s\n", pipex->token->files[i]);
    }
}

void free_token(t_token *token)
{
	int i;
	
	i = 1;
	while (i <= token->arg_count)
	{
		free(token->tabargs[i]);
		i++;
	}
	i = 0;
	while (i != token->file_count)
	{
		free(token->tabfiles[i]);
		i++;
	}
	free(token->tabargs);
	free(token->tabfiles);
	free(token->tabredir);
	free(token); 
}

void free_token_exec(t_pipex *pipex)
{
	// int i;
	
	// i = 1;
	// free(pipex->token->cmd);
	// printf("argcount {%d} i {%d}\n", token->arg_count, i);
	// while (i != token->arg_count)
	// {
	// 	printf("argcount {%d} i {%d}\n", token->arg_count, i);
	// 	free(token->tabargs[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i != token->file_count)
	// {
	// 	free(token->tabfiles[i]);
	// 	i++;
	// }
	free(pipex->token->tabargs);
	free(pipex->token->tabfiles);
	free(pipex->token->tabredir);
	free(pipex->token); 
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
		pipex.prompt = final_string(prompt, lst_envp);
		if (parsing(pipex.prompt))
		{
			free(pipex.prompt);
			continue ;
		}
		pipex.prompt = add_spaces(pipex.prompt);
		if (!pipex.prompt)
			break ;
		// print_token(&pipex);
		pipex.prompt = suppresing_quote(pipex.prompt);
		quote_positif(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		if (nbcmd == 1 && is_builtin(pipex.cmd[0]))
		{
			token = tokenisation(pipex.cmd[0]);
			chevron_no_exec(&pipex, token, lst_envp);
			free_token(token);
		}
		else
		{
			exec(nbcmd, lst_envp, &pipex);
			// free_token_exec(&pipex);
		}
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	free_lst(lst_envp);
	return (1);
}