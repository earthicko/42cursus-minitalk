/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:26:57 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 14:26:58 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf_utils.h"

static void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cursor;
	t_list	*cursor_next;

	cursor = *lst;
	while (cursor)
	{
		cursor_next = cursor->next;
		ft_lstdelone(cursor, del);
		cursor = cursor_next;
	}
	*lst = NULL;
}
