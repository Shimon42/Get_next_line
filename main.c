#include "get_next_line.h"

int main(void)
{
	int fd = open("tests/normal.txt", O_RDONLY);
	char *line ;
	line = NULL;
	int i = 0;
	int res = 1;

	/*int fd2 = open("tests/test2", O_RDONLY);
	char *line2;
	line2 = NULL;
	int res2 = 1;

	int fd3 = open("tests/test3", O_RDONLY);
	char *line3;
	line3 = NULL;
	int res3 = 1;

	int fd4 = open("tests/test4", O_RDONLY);
	char *line4;
	line4 = NULL;
	int res4 = 1;
	
	int fd5 = 0;
	char *line5;
	line5 = NULL;
	int res5 = 1;*/
	printf("\n\033[1;33m--------------- GNL START ------------------\033[0m\n");
	while (res )
	{
		printf("\n\033[1;34m--------------- GNL CALL - %d ----------------\033[0m\n", i);
		if (res > 0)
		{
			res = get_next_line(fd, &line);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
		}
		
	/*	if (res2 > 0)
		{
			res2 = get_next_line(fd2, &line2);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
		}

		if(res3 > 0)
		{
			res3 = get_next_line(fd3, &line3);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd3, i, line3, res3);
		}
		
		if(res4 > 0)
		{
			res4 = get_next_line(fd4, &line4);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd4, i, line4, res4);
		}

		if(res5 > 0)
		{
			res5 = get_next_line(fd5, &line5);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd5, i, line5, res5);
		}*/
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}

