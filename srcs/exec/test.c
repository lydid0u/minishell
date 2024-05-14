int	total_expand(char *input, t_copyenv *lst_envp, t_pipex *pipex)
{
	int (i) = 0;
	int (count) = 0;
	char *(value) = ft_itoa(pipex->status_code);
	while (input[i])
	{
		handle_single_quote(input, &i, &count);
		while (input[i] == '$')
		{
			i_and_count_plus_plus(&i, &count);
			if (input[i] == '?')
			{
				count += ft_strlen(value);
				i++;
				continue ;
			}
			if (is_key_valid(&input[i], lst_envp))
			{
				i += get_len_of_key(&input[i]);
				continue ;
			}
			count += get_len_of_value_from_str(&input[i], lst_envp);
			i += get_len_of_key(&input[i]);
		}
		if (input[i])
			i_and_count_plus_plus(&i, &count);
	}
	return (free(value), count);
}
