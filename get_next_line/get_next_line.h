/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:50:14 by jopedro-          #+#    #+#             */
/*   Updated: 2024/12/03 10:45:53 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

char	*ft_find_line(char *text);
char	*get_next_line(int fd);
char	*ft_gnl_strchr(char *s, int c);
int		ft_gnl_strlen(char *str);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_leftovers(char *s1);

#endif
