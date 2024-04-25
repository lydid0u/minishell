/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lboudjel <lboudjel@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/12/19 18:20:13 by lboudjel          #+#    #+#             */
/*   Updated: 2024/03/30 07:05:47 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// strace -o /dev/pts/11 -f

#include "minishell.h"

// INPUT : cat a | < b cat | cat > c | cat c
/*

	1) je prend ma string et je split au pipe
	2) je check dans la string si ya redirection > si oui,
	jouvre le fd/le cree tout ca
	>  si non, salam
	3) je dup2 le dernier
*/

void	redirection(t_pipex *pipex, int i)
{
	if (i != 0)
	{
		dup2(pipex->prev, 0);
		close(pipex->prev);
	}
	if (i != pipex->nbr_cmd - 1)
		dup2(pipex->fd[1], 1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}


void	print_tokenexec(t_token *token)
{
	fprintf(stderr, "PRINT TOKEN IN EXEC\n");

    fprintf(stderr, "Command: %s\n", token->cmd);
    for (int i = 1; i < token->arg_count; i++) 
    {
    	fprintf(stderr, "argument : %s\n", token->tabargs[i]);
	}
    fprintf(stderr, "\n");
    for (int i = 0; i < token->file_count; i++) 
    {
        fprintf(stderr, "Redirection: %d\n", token->tabredir[i]);
        fprintf(stderr, "File: %s\n", token->tabfiles[i]);
    }
}

t_token *allocstruct(char **tab)
{
	t_token *tok = malloc(sizeof(t_token));

	int i = 0;
	int r = 0;
	int a = 0;

	while (tab[i])
	{
		if (is_a_redirection(tab[i]))
		{
			r++;
			i++;
		}
		else
		{
			a++;
		}
		i++;
	}

	tok->tabargs = ft_calloc(sizeof(char *), a + 1);
	tok->tabfiles = ft_calloc(sizeof(char *), r + 1);
	tok->tabredir = ft_calloc(sizeof(int), r + 1);
	return (tok);
}


t_token *tokenisation(char *input)
{
	t_token *token;
	
	int r = 0;
	int a = 0;
	char **tab = ft_split_v2(input);
	token = allocstruct(tab);

	int i = 0;
	while (tab[i])
	{
		if (is_a_redirection(tab[i]))
		{
			token->tabredir[r] = is_a_redirection(tab[i++]);
			token->tabfiles[r++] = suppresing_quote(ft_strdup(tab[i]));
		}
		else
		{
			token->tabargs[a++] = suppresing_quote(ft_strdup(tab[i]));
		}
		i++;
	}
	free_tab(tab);
	token->cmd = token->tabargs[0];
	token->arg_count = a;
	token->file_count = r;
	print_tokenexec(token);
	return (token);
}


void	child(t_pipex *pipex, t_copyenv *lst_envp, int i)
{
	// char	*path;
	t_token *mycmd;

	free(pipex->prompt);
	redirection(pipex, i);
	// ici parsing
	mycmd =	tokenisation(pipex->arg_cmd[i]);
	// chevron(pipex, i);/
	handle_redirection(mycmd);
	if (handle_built_in_pipex(mycmd, pipex) == 0)
		return (free_tab(pipex->cmd), exit(1));
	else
	{
		// pipex->tab_cmd = ft_split(pipex->arg_cmd[i], ' ');
		// if (!pipex->tab_cmd)
			// return (free_tab(pipex->tab_cmd));
		// path = access_cmd(pipex, 0);
		// if (path)
		fprintf(stderr, "cjef\n");
		execvp(mycmd->cmd, mycmd->tabargs);
	}
	free_tab(pipex->cmd);
	free_lst(lst_envp);
	pipex->token = mycmd;
	free_token(pipex);
	return (exit(127));
}

void	piping_and_forking(t_pipex *pipex, t_copyenv *lst_envp)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (ft_printf("Error: pipe function\n"), exit(EXIT_FAILURE));
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
			return (ft_printf("Error: fork function\n"), exit(EXIT_FAILURE));
		if (pipex->pid[i] == 0)
			child(pipex, lst_envp, i);
		else
		{
			close(pipex->fd[1]);
			if (i != 0)
				close(pipex->prev);
			pipex->prev = pipex->fd[0];
		}
		i++;
	}
	i = 0;
	while (i < pipex->nbr_cmd)
		waitpid(pipex->pid[i++], NULL, 0);
}

void	init_struct(t_pipex *pipex, int argc, char **argv, t_copyenv *lst_envp)
{
	pipex->envp = lst_envp;
	pipex->arg_cmd = argv;
	pipex->nbr_cmd = argc;
}

int	exec(int argc, t_copyenv *lst_envp, t_pipex *pipex)
{
	init_struct(pipex, argc, pipex->cmd, lst_envp);
	piping_and_forking(pipex, lst_envp);
	close(pipex->fd[0]);
	return (1);
}
