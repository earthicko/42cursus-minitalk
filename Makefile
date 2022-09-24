NAME			= minitalk
BONUS			= 
INC				= -I . -I includes $(LIBFTPRINTF_INC)
LIBFTPRINTF		= libftprintf.a
LIBFTPRINTF_DIR	= libftprintf
LIBFTPRINTF_LIB	= -L libftprintf libftprintf/libftprintf.a
LIBFTPRINTF_INC	= -I libftprintf/includes

SRCDIR			= ./src/
SRCNAME			= \
				$(SRCDIR)sigcom/sigcom

SRCDIR_BONUS	= ./src_bonus/
SRCNAME_BONUS	= 

SRC				= $(addsuffix .c, $(SRCNAME))
OBJ				= $(addsuffix .o, $(SRCNAME))
SRC_BONUS		= $(addsuffix .c, $(SRCNAME_BONUS)))
OBJ_BONUS		= $(addsuffix .o, $(SRCNAME_BONUS))

RM				= rm -f
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFTPRINTF) $(SRCDIR)server.o $(SRCDIR)client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR)server.o -o server $(LIBFTPRINTF_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR)client.o -o client $(LIBFTPRINTF_LIB)

bonus : $(OBJ_BONUS) $(LIBFTPRINTF) $(SRCDIR_BONUS)server.o $(SRCDIR_BONUS)client.o
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR_BONUS)server.o -o server $(LIBFTPRINTF_LIB)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(SRCDIR_BONUS)client.o -o client $(LIBFTPRINTF_LIB)

$(LIBFTPRINTF) :
	make -C $(LIBFTPRINTF_DIR) $(LIBFTPRINTF)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	$(RM) $(OBJ) $(SRCDIR)server.o $(SRCDIR)client.o
	$(RM) $(OBJ_BONUS) $(SRCDIR_BONUS)server.o $(SRCDIR_BONUS)client.o
	make clean -C $(LIBFTPRINTF_DIR)

fclean : clean
	$(RM) server client
	make fclean -C $(LIBFTPRINTF_DIR)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re
