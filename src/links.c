/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 08:34:28 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/29 10:09:21 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_tar.h"

t_write_block *head = NULL;
t_write_block *tail = NULL;

void	push_block(union u_raw_block new_block)
{
	if (!head && !tail)
	{
		head = (t_write_block*)malloc(sizeof(t_write_block));
		tail = head;
		memset(head, 0, sizeof(t_write_block));
		tail->u_data = new_block;
	}
	else
	{
		tail->next = (t_write_block*)malloc(sizeof(t_write_block));
		tail = tail->next;
		memset(tail, 0, sizeof(t_write_block));
		tail->u_data = new_block;
	}
}

void	print_blocks(void)
{
	t_write_block *temp;
	temp = head;
	char *stepper;
	int i;
	while(temp)
	{
		i = -1;
		stepper = (char*)temp;
		while(++i < 512)
			ft_printf("%c", stepper[i]);
		printf("\n");
		temp = temp->next;
	}
}

void	print_filename(void)
{
	int i = -1;
	char *temp = (char*)head;
	while (++i < 100)
		ft_printf("%02x", temp[i]);
}

void	write_blocks(int fd)
{
	t_write_block *current = head;
	while (current)
	{
		write(fd, &current->u_data, 512);
		current = current->next;
	}
}
