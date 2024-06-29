CLI_NAME = cli
SRV_NAME = srv

GCC = cc
CFLAGS = -Ilib  -Ilibft  #-framework OpenGL -framework GLUT -Qunused-arguments  -Wl -w -Wno-deprecated-declarations #-g -fsanitize=address -Wall -Wextra -Werror

CLI_SRC = $(wildcard src/client/*.c)
SRV_SRC = $(wildcard src/server/*.c)

CLI_OBJ = $(CLI_SRC:.c=.o)
SRV_OBJ = $(SRV_SRC:.c=.o)


all: libft_build $(CLI_NAME) $(SRV_NAME)

libft_build :
	$(MAKE) -C libft

$(CLI_NAME): $(CLI_OBJ)
	$(GCC) $(CLI_OBJ) $(CFLAGS) $(LDFLAGS) -o $(CLI_NAME) -lm libft/libft.a -lreadline

$(SRV_NAME): $(SRV_OBJ)
	$(GCC) $(SRV_OBJ) $(CFLAGS) -o $(SRV_NAME) -lm libft/libft.a -lreadline

%.o: %.c
	$(GCC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(CLI_OBJ) $(SRV_OBJ)
	$(MAKE) -C libft clean

fclean: clean 
	rm -rf $(CLI_NAME) $(SRV_NAME)
	$(MAKE) -C libft fclean

re: fclean all

git:
	@echo "Enter Commit: "
	@read message; \
	git add . && git commit -m "$$message" && git push

.PHONY: all clean fclean re
