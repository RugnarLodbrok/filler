#include <fcntl.h>
#include "libft_compat.h"
#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

void write_file(char *f_name, char *content)
{
	int fd;

	fd = open(f_name, O_CREAT | O_WRONLY | O_TRUNC);
	write(fd, content, ft_strlen(content));
	close(fd);
}

int main(void)
{
	t_map map;
	t_map piece;

	map = read_map("Plateau");
	piece = read_map("Piece");
	(void)map;
	(void)piece;
	return 0;
}
