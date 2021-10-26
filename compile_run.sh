rm pipex;
gcc -Wall -Wextra -Werror main.c pipex_utils.c ./libft/libft.a -o pipex;
./pipex main.c "cat -e" "grep pipex" outfile;
open outfile;