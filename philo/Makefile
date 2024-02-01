NAME				= philo
INC					= .
SRC_DIR				= src/
OBJ_DIR				= obj/

CC					= cc
CFLAGS				= -Wall -Werror -Wextra -I$(INC) -fsanitize=thread #-lpthread
RM					= rm -f

PHILO_DIR 			= 	validation_and_errors/error_handling.c \
						validation_and_errors/parse_args.c \
						\
						actions/action_handler.c \
						actions/routine.c \
						actions/sleep.c \
						actions/think.c \
						actions/eat.c \
						\
						other/thread_handler.c \
						other/philo_status.c \
						other/utils.c \
						other/init.c \
						\
						main.c

SRCS 				= $(addprefix $(SRC_DIR), $(PHILO_DIR))
OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

start:				
	@echo "Starting the build process..."
	@make all
	@echo "Build process completed."

all: $(NAME)
	@echo "Executable $(NAME) has been created successfully."

$(NAME): $(OBJ)
	@echo "Linking object files to create the executable $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
#	@echo "Executable $(NAME) has been created."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
#	@echo "Compiling $<..."
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo "Object file $@ has been created."

clean:
	@echo "Cleaning up object files..."
	@$(RM) -r $(OBJ_DIR)
	@echo "Object files have been removed."

fclean: clean
	@echo "Cleaning up executable $(NAME)..."
	@$(RM) $(NAME)
	@echo "Executable $(NAME) has been removed."

re: fclean all
#	@echo "Rebuild process completed."

.PHONY: start all clean fclean re