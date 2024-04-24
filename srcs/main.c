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

void free_token(t_pipex *pipex)
{
	int i;
	
	i = 0;
	free(pipex->token->cmd);
	// printf("files %d args %d\n", pipex->token->file_count, pipex->token->arg_count);
	if (pipex->token->arg_count > 0)
	{
		while (i <= pipex->token->arg_count)
    	{
			printf("free args\n");
			free(pipex->token->args[i]);
			i++;
		}	
	}
	i = 0;
	if (pipex->token->file_count > 0)
	{
		while (i <= pipex->token->file_count)
	    {
			printf("free files\n");
			free(pipex->token->files[i]);
			i++;
	    }
	}
	free(pipex->token); 
}

int	main(int argc, char **argv, char **envp)
{
	static t_pipex	pipex = {0};
	// static t_token	token = {0};
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
		tokenisation(pipex.prompt, &pipex);
		// print_token(&pipex);
		pipex.prompt = suppresing_quote(pipex.prompt);
		quote_positif(pipex.prompt);
		pipex.cmd = ft_split(pipex.prompt, '|');
		nbcmd = countword(pipex.prompt, '|');
		if (nbcmd == 1 && is_builtin(pipex.cmd[0]))
		{
			// printf("prompt %s\n", pipex.prompt);
			chevron_no_exec(&pipex, lst_envp);
		}
		else
			exec(nbcmd, lst_envp, &pipex);
		free(pipex.prompt);
		free_tab(pipex.cmd);
	}
	free_token(&pipex);
	free_lst(lst_envp);
	return (1);
}

//leaks sur ls | cd