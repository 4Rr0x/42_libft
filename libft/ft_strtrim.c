/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopedro- <jopedro-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:20:48 by jopedro-          #+#    #+#             */
/*   Updated: 2024/11/07 13:21:39 by jopedro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = (ft_strlen(s1) - 1);
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	while (s1[start] && ft_strchr(set, s1[end]))
		end--;
	return (ft_substr(s1, start, ((end - start) + 1)));
}
