NAME			= libftprintf.a

INC_DIR			= -I . -I includes

SRCNAME			= \
				./src/ft_printf \
				./src/t_conv \
				./src/ft_str_utils \
				./src/ft_numlen \
				./src/parse_format \
				./src/parse_format_utils \
				./src/create_str \
				./src/create_str_utils \
				./src/fwrite_chr \
				./src/fwrite_num \
				./src/fwrite_ptr \
				./src/fwrite_utils \
				./src/utils/ft_atoi \
				./src/utils/ft_isdigit \
				./src/utils/ft_lstadd_back \
				./src/utils/ft_lstclear \
				./src/utils/ft_lstnew \
				./src/utils/ft_memcpy \
				./src/utils/ft_strdup \
				./src/utils/ft_strjoin \
				./src/utils/ft_strlen \
				./src/utils/ft_substr \

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	ar -rcus $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all bonus clean fclean re
