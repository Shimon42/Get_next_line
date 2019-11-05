#include "get_next_line.h"

char* readline(fd)
{
	char *tmp = malloc(1000000 * sizeof(char));
	char *tmpCur;

	tmpCur = tmp;
	while (read(fd, tmpCur, 1) && *tmpCur != '\n')
	{
		tmpCur++;
	}
	*tmpCur = '\0';
	return (tmp);
}

int		ft_strcomp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int main(void)
{
	//char *testfile = "tests/test";
	int fd = open("tests/bar.txt", O_RDONLY);
	int fdcheck = open("tests/bar.txt", O_RDONLY);
	char *line ;
	line = NULL;
	int i = 0;
	int res = 1;
	char *exp1;

	int fd2 = open("tests/test2", O_RDONLY);
	int fd2check = open("tests/test2", O_RDONLY);
	char *line2;
	line2 = NULL;
	char *exp2;
	int res2;

	int fd3 = open("tests/test3", O_RDONLY);
	int fd3check = open("tests/test3", O_RDONLY);
	char *line3;
	line3 = NULL;
	int res3 = 1;
	char *exp3;

	int fd4 = open("tests/test4", O_RDONLY);
	int fd4check = open("tests/test4", O_RDONLY);
	char *line4;
	line4 = NULL;
	int res4 = 1;
	char *exp4;

	int fd5 = 0;
	char *line5;
	line5 = NULL;
	int res5 = 1;


	printf("\n\033[1;33m--------------- GNL START ----------- BUFF: %d-------\033[0m\n", BUFFER_SIZE);
	while (res > 0)
	{
		printf("\n\033[1;34m--------------- GNL CALL - %d -------- BUFF: %d --------\033[0m\n", i, BUFFER_SIZE);
		
		if (res > 0 || res2 > 0 || res3 > 0 || res4 > 0 || res5 >0)
		{
			exp1 = readline(fdcheck);
			res = get_next_line(fd, &line);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd, i, line, res);
			if (exp1 && line && ft_strcomp(exp1, line) != 0)
			{
				printf("DIFF\n");
				return (0);
			}
		}
		if (res2 > 0)
		{
			exp2 = readline(fd2check);
			res2 = get_next_line(fd2, &line2);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd2, i, line2, res2);
			if (exp2 && line2 && ft_strcomp(exp2, line2) != 0)
			{
				printf("DIFF\n");
				return (0);
			}
		}

		if(res3 > 0)
		{
			exp3 = readline(fd3check);
			res3 = get_next_line(fd3, &line3);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd3, i, line3, res3);
			if (exp3 && line3 && ft_strcomp(exp3, line3) != 0)
			{
				printf("DIFF\n");
				return (0);
			}
		}
		
		if(res4 > 0)
		{
			exp4 = readline(fd4check);
			res4 = get_next_line(fd4, &line4);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd4, i, line4, res4);
			if (exp4 && line4 && ft_strcomp(exp4, line4) != 0)
			{
				printf("DIFF\n");
				return (0);
			}
		}

		if(res5 > 0)
		{
			res5 = get_next_line(fd5, &line5);
			printf("\033[0;32mfd: %d - RES %d -> %s\033[0;35m[end]\033[0m - RETURN %d\n", fd5, i, line5, res5);
		}
		i++;
	}
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
	printf("\n\033[1;32m--------------- GNL   END ------------------\033[0m\n");
}

