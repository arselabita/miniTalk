# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abita <abita@student.42vienna.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/11 12:20:50 by abita             #+#    #+#              #
#    Updated: 2025/08/11 12:21:20 by abita            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# the compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft -I./printf -g
RM = rm -f
MAKE = make

# executable name (Mandatory Part)
NAME1 = server
NAME2 = client

# executable name (Bonus Part)
BONUS_NAME1 = server_bonus
BONUS_NAME2 = client_bonus

LIBFT = libft/libft.a
PRINTF = printf/libftprintf.a

# directories
SRC_DIR = src
OBJ_DIR = build

# source to object files (Mandatory Part)
SRCS1 = $(SRC_DIR)/server.c
SRCS2 = $(SRC_DIR)/client.c

OBJS1 = $(SRCS1:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS2 = $(SRCS2:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# source to object files (Bonus Part)
BONUS_SRC1 = $(SRC_DIR)/server_bonus.c
BONUS_SRC2 = $(SRC_DIR)/client_bonus.c

BONUS_OBJ1 = $(BONUS_SRC1:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ2 = $(BONUS_SRC2:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# rules for mandatory part
all: $(NAME1) $(NAME2) $(BONUS_NAME1) $(BONUS_NAME2)

$(NAME1): $(OBJS1) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJS1) $(LIBFT) $(PRINTF)
$(NAME2): $(OBJS2) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJS2) $(LIBFT) $(PRINTF)

# rules for bonus part
$(BONUS_NAME1): $(BONUS_OBJ1) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(BONUS_NAME1) $(BONUS_OBJ1) $(LIBFT) $(PRINTF)
$(BONUS_NAME2): $(BONUS_OBJ2) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(BONUS_NAME2) $(BONUS_OBJ2) $(LIBFT) $(PRINTF)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft
$(PRINTF):
	$(MAKE) -C printf

clean:
	$(RM) $(OBJS1) $(OBJS2) $(BONUS_OBJ1) $(BONUS_OBJ2)
	$(MAKE) -C libft clean
	$(MAKE) -C printf clean

fclean: clean 
	$(RM) $(NAME1) $(NAME2) $(BONUS_NAME1) $(BONUS_NAME2)
	$(MAKE) -C libft fclean
	$(MAKE) -C printf fclean
	rm -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
.SILENT: 
