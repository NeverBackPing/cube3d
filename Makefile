####################### 🛠️ ##############################

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
RM = rm -rf

####################### 🤖 ##############################

NAME = cub3D

######################## 📁 #############################

LIBFT = srcs/dependency/libft/libft.a

LIBFT_DIR = srcs/dependency/libft

LIBC = $(shell ls $(LIBFT_DIR)/*.c)

LIBFT_OBJS = $(LIBC:.c=.o)

######################## 📁 #############################

PARSING = srcs/parsing/parsing.a

PARSING_DIR = srcs/parsing/

PARSING_SRC = $(shell ls $(PARSING_DIR)/*.c)

PARSING_OBJS = $(PARSING_SRC:.c=.o)

######################## 📁 #############################

GNL = srcs/dependency/get_next_line.a

GNL_DIR = srcs/dependency/gnl

GNL_SRC = $(shell ls $(GNL_DIR)/*.c)

GNL_OBJS = $(GNL_SRC:.c=.o)

######################## 📁 #############################

MLX_LIB = mlx/libmlx.a

MLX_DIR = mlx

MLX = -Lmlx -lX11 -lXext -lm

######################## 📁 #############################

SRC = $(shell ls srcs/*.c)

SRCS = ${SRC} $(LIBC) $(PARSING_SRC)

OBJS = $(SRCS:.c=.o)

######################## 🧠 #############################

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I$(PARSING_DIR) -I$(GNL_DIR) -I$(MLX_DIR)

######################## 🎨 #############################

BLUE	=	\033[0;34m
GREEN	=	\033[0;32m
RED		=	\033[31m
RESET	=	\033[0m
YELLOW	=	\033[0;33m

define HEADER

 ██████╗██╗   ██╗██████╗ ███████╗    ██████╗ ██████╗
██╔════╝██║   ██║██╔══██╗██╔════╝    ╚════██╗██╔══██╗
██║     ██║   ██║██████╔╝█████╗       █████╔╝██║  ██║
██║     ██║   ██║██╔══██╗██╔══╝       ╚═══██╗██║  ██║
╚██████╗╚██████╔╝██████╔╝███████╗    ██████╔╝██████╔╝
 ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝    ╚═════╝ ╚═════╝

endef
export HEADER

######################## 🗃️ #############################

%.o: %.c
	$(CC) $(CFLAGS)  $(INCLUDES) $(INC) -c $< -o $@

######################## 🎶🎹 ############################

all: $(LIBFT) $(PARSING_DIR) $(MLX_LIB) $(NAME) header

$(LIBFT): $(LIBFT_OBJS)
		ar rcs $(LIBFT) $(LIBFT_OBJS)

$(PARSING): $(PARSING_OBJS)
		ar rcs $(PARSING) $(PARSING_OBJS)

$(GNL): $(GNL_OBJS)
		ar rcs $(GNL) $(GNL_OBJS)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

header:
	@echo "$(GREEN)$$HEADER$(RESET)"

$(NAME): $(OBJS) $(LIBFT) $(PARSING) $(GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(PARSING) $(GNL) $(MLX_LIB) $(MLX) -o $(NAME)

clean:
	$(RM) $(OBJS) $(LIBFT_OBJS) $(PARSING_OBJS) $(GNL_OBJS)

fclean: clean
	$(RM) $(LIBFT) $(PARSING) $(GNL) $(MLX_LIB) mlx/libmlx_Linux.a $(NAME)

re: fclean all

.PHONY: all clean fclean header re