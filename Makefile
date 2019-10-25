NAME	= gnl
SRCS	=	get_next_line.c \
			get_next_line_utils.c

SRCSG	=	get_next_line-ok-not-normed.c \
			get_next_line_utils.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -D BUFFER_SIZE=100000
RM		= rm -f
INCLUDES =	get_next_line.h

all:		$(NAME)

$(NAME): 	
			clear
			$(CC) $(CFLAGS) $(SRCS) $(INCLUDES)

launch :	re
			clear
			./a.out

launchg :	fclean
			clear
			$(CC) $(CFLAGS) $(SRCSG) $(INCLUDES)
			./a.out

clean:		
			${RM} $(OBJS) $(OBJSBNS)

fclean:		clean
			${RM} $(NAME)
			
re:			fclean all

sanitize:	$(OBJS)
			$(CC) $(CFLAGS) -g3 -fsanitize=address -o $(NAME) $(OBJS)

.PHONY: all clean fclean re