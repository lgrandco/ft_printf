NAME = libftprintf.a

SRC = ft_printf.c utils.c ft_itoa_base.c

BONUS_SRC =

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC.c=.o)

CC = clang

CFLAGS = -Wall -Werror -Wextra -g3

RM = rm -f

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

all : $(NAME)

$(LIBFT) :
	make bonus -C $(LIBFT_PATH)

$(NAME) : $(LIBFT) ${OBJ}
	cp $(LIBFT) $(NAME)
	ar rcs ${NAME} ${OBJ}

bonus : $(NAME)

clean :
	make clean -C $(LIBFT_PATH)
	$(RM) $(NAME) $(OBJ)

fclean : clean
	make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

c :
	${CC} -g3 $(SRC) -L./libft -lft

re : fclean all

.PHONY : all clean fclean re
