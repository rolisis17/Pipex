/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcella-d <dcella-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:14:30 by dcella-d          #+#    #+#             */
/*   Updated: 2023/04/06 19:52:56 by dcella-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

//			Part I

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

size_t	ft_strlen(const char *str);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_strchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c);

int		ft_toupper(int c);

int		ft_tolower(int c);

void	*ft_memset(void *s, int c, size_t n);

void	ft_bzero(void *s, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_atoi(const char *nptr);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strdup(const char *s);

//			Part II

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strjoin(char *s1, char *s2, int f);

char	*ft_strtrim(char const *s1, char const *set);

char	**ft_split(char const *s, char c);

char	*ft_itoa(int n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

//			!!  BONUS !!

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}					t_list;

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//				GNL

char	*get_next_line(int fd);

void	*ft_calloc_gnl(size_t nmemb, size_t size);

char	*ft_strjoin_gnl(char *s1, char *s2, int f);

int		ft_strlen_gnl(const char *s);

int		gnl_check(char *line);

char	*full_line(int fd, char *keep);

char	*makeline(char *keep, int posnextline);

//				PRINTF

int		ft_printf(const char *str, ...);

int		ft_count(const char *str, va_list args);

int		ft_flags(char uck, va_list args);

int		ft_putchar(char c);

int		ft_putstr(char *s);

int		ft_putnbr(int nbr);

int		ft_putunsigned(unsigned int nbr);

int		ft_puthexa(unsigned int nbr, char *base);

int		ft_putaddress(unsigned long int nbr, char *base, int safe);

#endif
