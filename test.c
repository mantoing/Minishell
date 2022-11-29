#include <stdio.h>
#include <fcntl.h>
#include "./libft/libft.h"
#include <stdlib.h>

int main(void)
{
	int	fd;
	char	*str;
	char	*temp;

	temp =  ft_itoa(312);
	str = ft_strjoin("hello ",temp);
	free(temp);
	printf("%s\n", str);
	fd = open("fjdsiddf", O_RDONLY);
	printf("fd = %d\n", fd);
	while (1)
		;
	return (0);
}
