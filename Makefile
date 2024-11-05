NAME =	libgetnextline.a

SRC	= \
get_next_line.c       \
get_next_line_utils.c
    
OBJS = $(SRC:.c=.o) 

CC = cc
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42
RM = rm -rf
AR = ar crs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)		

re:	fclean all

.PHONY:	all clean fclean re