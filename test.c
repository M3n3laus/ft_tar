#include "ft_tar.h"

int main(int ac, char **av)
{
	struct stat st;
	stat(av[1], &st);
	printf("%o\n", st.st_uid);
	printf("%o\n", st.st_mode & 0x1FF);
	return(0);
}
