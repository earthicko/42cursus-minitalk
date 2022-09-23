NAME			= minitalk
BONUS			= 
INC				= -I . -I includes $(LIBFTPRINTF_INC)
LIBFTPRINTF		= libftprintf.a
LIBFTPRINTF_DIR	= libftprintf
LIBFTPRINTF_LIB	= -L libftprintf libftprintf/libftprintf.a
LIBFTPRINTF_INC	= -I libftprintf/includes

SRCNAME			= \
				./sigcom/sigcom \
				./sigcom/sigcom_send

SRCNAME_BONUS	= 

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))
SRC_BONUS		= $(addsuffix .c, $(SRCNAME_BONUS)))
OBJ_BONUS		= $(addsuffix .o, $(SRCNAME_BONUS))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFTPRINTF) server.o client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) server.o -o server $(LIBFTPRINTF_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) client.o -o client $(LIBFTPRINTF_LIB)

bonus : $(OBJ_BONUS) $(LIBFTPRINTF)
	@$(CC) $(CFLAGS) $(INC) $(OBJ_BONUS) -o $(BONUS) $(LIBFTPRINTF_LIB)

$(LIBFTPRINTF) :
	make -C $(LIBFTPRINTF_DIR) $(LIBFTPRINTF)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ) server.o client.o $(OBJ_BONUS)
	make clean -C $(LIBFTPRINTF_DIR)

fclean : clean
	$(RM) server client
	make fclean -C $(LIBFTPRINTF_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
