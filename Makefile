NAME = conatainers
CC = c++
CFLAGS = -std=c++98 -Wall -Wextra -Werror -MMD

SRC_FILES =	main.cpp
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR=obj
OBJ=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.cpp=.o))
DEP=$(addprefix $(OBJ_DIR)/,$(SRC_FILES:.cpp=.d))

INC_FILES = vector.hpp \
			utils.hpp \
			iterator.hpp \
			map.hpp \
			stack.hpp
INC_DIR = includes
CFLAGS+=-I $(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(OBJS)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $(OBJ_DIR)

clean:
		rm -rf $(OBJ_DIR)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re