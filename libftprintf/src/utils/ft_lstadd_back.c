/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghyle <donghyle@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:26:52 by donghyle          #+#    #+#             */
/*   Updated: 2022/07/10 14:26:53 by donghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"

static t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
