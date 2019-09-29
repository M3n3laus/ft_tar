/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trashcan.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 13:27:24 by smaddox           #+#    #+#             */
/*   Updated: 2019/08/08 12:29:17 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRASHCAN_H
# define TRASHCAN_H

# include <stdarg.h>
# include <stdlib.h>

# define DEFAULT_SIZE 200

typedef struct		s_trashcan
{
	void			*can[DEFAULT_SIZE];
	int				top;
}					t_rash_can;

void				mom(void *pointer);
int					trash_overflow(void);
int					trashcan_empty(void);
void				garbage_day(void);

extern t_rash_can g_can;

#endif
