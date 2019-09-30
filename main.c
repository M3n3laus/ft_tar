#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "ft_tar.h"

void handle_file(char *file_name);
void handle_dir(char *dir_name);

int main(int ac, char **av)
{
	struct stat st;
	int i = 0;
	t_write_block *head;

	while(++i < ac)
	{
		memset(&st, 0, sizeof(struct stat));
		stat(av[i], &st);
		if (S_ISREG(st.st_mode))
			handle_file(av[i]);
		else if (S_ISDIR(st.st_mode))
			handle_dir(av[i]);
	}
	return(0);
}

/*
void handle_file(char *file_name)
{
	int fd;
	int	bytes;
	struct stat st;
	union u_raw_block header;
	union u_raw_block file_data;
	memset(&header, 0, sizeof(union u_raw_block));
	memset(&file_data, 0, sizeof(union u_raw_block));
	stat(file_name, &st);
	memcpy(header.header.name, &file_name, strlen(file_name));
	memcpy(header.header.mode, &st.st_mode, sizeof(mode_t));
	memcpy(header.header.uid, &st.st_uid, sizeof(uid_t));
	memcpy(header.header.gid, &st.st_gid, sizeof(gid_t));
	memcpy(header.header.size, &st.st_size, sizeof(off_t));
	memcpy(header.header.mtime, &st.st_mtimespec, sizeof(struct timespec));
	push_block(header);
	if(S_ISDIR(st.st_mode))
		return;
	fd = open(file_name, O_RDONLY);
	ft_printf("%d\n", fd);
	while ((bytes = read(fd, &file_data, 512)))
	{
		push_block(file_data);
		memset(&file_data, 0, sizeof(union u_raw_block));
	}
	ft_printf("%s\n", file_name);
	write(1, "\n", 1);
	print_filename();
}
*/	
void handle_dir(char *dir_name)
{
	struct stat st;
	DIR *dirp = opendir(dir_name);
	struct dirent *next;

	handle_file(dir_name);	
	while ((next = readdir(dirp)) != NULL)
	{
		memset(&st, 0, sizeof(struct stat));
		if (next->d_name[0] != '.')
		{
			stat(next->d_name, &st);
			if (S_ISREG(st.st_mode))
				handle_file(next->d_name);
			else if(S_ISDIR(st.st_mode))
				handle_dir(next->d_name);
		}
	}
}
