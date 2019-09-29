/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tar.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaddox <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 06:43:15 by smaddox           #+#    #+#             */
/*   Updated: 2019/09/28 15:26:10 by smaddox          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
typedef struct		s_header_block
{									
									/*	OFFSETS	*/
	char			name[100];		/*	0		*/
	char			mode[8];		/*	100		*/
	char			uid[8];			/*	108		*/
	char			gid[8];			/*	116 	*/
	char			size[12];		/*	124		*/
	char			mtime[12];		/*	136		*/
	char			chksum[8];		/*	148 	*/
	char			typeflag;		/*	156		*/
	char			linkname[100];	/*	157 	*/
	char			magic[6];		/*	257		*/
	char			version[2];		/*	263 	*/
	char			uname[32];		/*	265		*/
	char			gname[32];		/*	297		*/
	char			devmajor[8];	/*	329		*/
	char			devminor[8];	/*	337		*/
	char			prefix[131];	/*	345		*/
	char			atime[12];		/*	476		*/
	char			ctime[12];		/*	488		*/
	char			garbage[12];	/*	500		*/
									/*	512		*/
}					t_header_block;	

typedef	struct		s_data_block
{
	unsigned char	data[512];
}					t_data_block;

/*	
 * *	Both of union members are 512 bytes
 * * *	so just write whatever is in each node's 
 * *	union to the archive
 */
 
typedef	struct		s_write_block
{
	union				u_raw_block
	{
		t_header_block	header;
		t_data_block	data;
	}					u_data;	
	struct s_write_block	*next;
}							t_write_block;	


void push_block(union u_raw_block new_block);
void print_blocks(void);


