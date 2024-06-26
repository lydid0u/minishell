/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lboudjel <marvin@42.fr>                    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/05/04 14:13:09 by lboudjel          #+#    #+#             */
/*   Updated: 2023/05/04 14:13:09 by lboudjel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "gnl/get_next_line.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_isprint(int c);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
void	ft_strcat(char *dest, const char *src);
int		ft_isascii(int c);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *s1, const char *s2, size_t n);
void	*ft_memset(void *ptr, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *destination, const void *source, size_t n);
void	*ft_memmove(void *destina, const void *source, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft__strlen(const char *str);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_tolower(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
char	*ft_itoa(int n);
char	*ft_strjoin_slash(char *s1, char *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		countword(const char *s, char c);
char	*ft_strcpy(char *s1, char *s2);

int		countword_v2(const char *s);
char	*copystr_v2(const char *original);
char	**ft_fill_tab_v2(char const *s, char **tab, int len_tab);
char	**ft_split_v2(char *s);

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}		t_list;

t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif