# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2017/12/08 18:11:02 by clcreuso    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

NAME = fdf

C_FLAGS = -Wall -Wextra -Werror -o2

FRAMEWORKS = -framework OpenGL -framework AppKit

DIR_LIB = Libft/

DIR_SRC = Source/

DIR_INC = Includes/

DIR_MLX = Minilibx/

NAME_SRC =	main_fdf.c draw_fdf.c tools_draw_fdf.c prasing_map_fdf.c prasing_file_fdf.c \
			delete_background_fdf.c print_map_fdf.c search_fdf.c tools_fdf_01.c tools_fdf_00.c error_usage_fdf.c

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(DIR_LIB)
	@make -C $(DIR_MLX)
	@$(CC) $(C_FLAGS) $(OBJ) -o $(NAME) -L $(DIR_MLX) -lmlx -L $(DIR_LIB) -lft $(FRAMEWORKS)
	@echo "\033[0;32m✅️   make fdf.\033[0m"

./%.o: ./%.c
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o  $@ -c $< 
	@echo "\033[0;32m✅️   $@ created.\033[0m"

clean:
	@make clean -C $(DIR_LIB)
	@make clean -C $(DIR_MLX)
	@rm -f $(OBJ)
	@echo "\033[38;5;202m🗑️   clean fdf.\033[0m" 

fclean: clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(NAME)
	@echo "\033[38;5;196m🗑️   fclean fdf.\033[0m" 

re: fclean all
	