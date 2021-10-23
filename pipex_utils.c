/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:07:16 by tlemma            #+#    #+#             */
/*   Updated: 2021/10/23 15:59:59 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **to_free)
{
	if (*to_free != NULL)
	{
		free(*to_free);
		*to_free = NULL;
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	char	*cp_ret;
	char	*cp_s;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (s2);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	cp_ret = ret;
	cp_s = s1;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	cp_s = s2;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	*cp_ret = '\0';
	ft_free(&s1);
	// ft_free(&s2);
	return (ret);
}