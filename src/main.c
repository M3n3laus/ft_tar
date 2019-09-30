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
	int i = 1;
	union u_raw_block padding;
	int fd;

	fd = open(av[1], O_CREAT | O_WRONLY);
	while(++i < ac)
	{
		memset(&st, 0, sizeof(struct stat));
		memset(&padding, 0, 512);
		stat(av[i], &st);
		if (S_ISREG(st.st_mode))
			handle_file(av[i]);
		else if (S_ISDIR(st.st_mode))
			handle_dir(av[i]);
	}
	push_block(padding);
	push_block(padding);
	write_blocks(fd);
	return(0);
}
	
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
