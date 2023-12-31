/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:45:00 by leo               #+#    #+#             */
/*   Updated: 2023/11/07 00:24:00 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*node;

	ret = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
			return (ft_lstclear(&ret, del), NULL);
		ft_lstadd_back(&ret, node);
		lst = lst->next;
	}
	return (ret);
}
