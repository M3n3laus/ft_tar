#include "ft_tar.h"

void handle_file(char *file_name)
{
	get_header_info(file_name);
	get_file_data(file_name);
	int fd = open("output2", O_CREAT | O_WRONLY);
	write_blocks(fd);
}

void get_file_data(char *file_name)
{
	int fd;
	int	bytes;
	union u_raw_block file_data;
	memset(&file_data, 0, sizeof(union u_raw_block));
	fd = open(file_name, O_RDONLY);
	while ((bytes = read(fd, &file_data, 512)))
	{
		push_block(file_data);
		memset(&file_data, 0, sizeof(union u_raw_block));
	}
}

void get_header_info(char *file_name)
{
	union u_raw_block	header;
	struct stat			st;
	mode_t				mode;
	char				type_flag;

	memset(&header, 0, sizeof(union u_raw_block));
	stat(file_name, &st); mode = (st.st_mode & 0x1FF); if(S_ISREG(st.st_mode))
		type_flag = '0'; 
	else if (S_ISDIR(st.st_mode))
		type_flag = '5';

	ft_printf("%s%+v", file_name, header.header.name);
	ft_printf("%06o %+v", mode, header.header.mode);
	ft_printf("%06o %+v", st.st_uid, header.header.uid);
	ft_printf("%06o %+v", st.st_gid, header.header.gid);
	ft_printf("%011o %+v", st.st_size, header.header.size);
	ft_printf("%011o %+v", st.st_mtime, header.header.mtime);
	//ft_printf("%06o%c %+v", 0, 0, header.header.chksum); //do checksum
	ft_printf("%06s %+v", "14615",header.header.chksum); //do checksum
	ft_printf("%c%+v", type_flag, header.header.typeflag);
	ft_printf("%s%+v", "ustar", header.header.magic);
	ft_printf("%s%+2v", "00", header.header.version);
	ft_printf("%s%+v", getpwuid(st.st_uid)->pw_name, header.header.uname);
	ft_printf("%s%+v", getgrgid(st.st_gid)->gr_name, header.header.gname);
	ft_printf("%06s %+v", "0", header.header.devmajor);
	ft_printf("%06s %+v", "0", header.header.devminor);
	push_block(header);
}
