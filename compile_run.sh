rm pipex;
gcc main.c pipex_utils.c ./libft/libft.a -o pipex;
./pipex infile "ls -l" "grep pipex" outfile;
