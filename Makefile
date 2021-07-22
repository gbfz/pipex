NAME				=	pipex

COMPILER			=	clang
CFLAGS				=	-Wall -Wextra -Werror
DEBUG				=	-g

MAIN_SRC_DIR		=	main_srcs/
BONUS_SRC_DIR		=	bonus_srcs/
SHARED_SRC_DIR		=	shared_srcs/

MAIN_SRCS				=	pipex.c main_exec.c
BONUS_SRCS				=	pipex_bonus.c main_exec_bonus.c heredoc_exec_bonus.c
SHARED_SRCS				=	append.c cmd_args.c compare.c duplicate.c exit_code.c	\
							free_string_arr.c ft_calloc.c ft_split.c ft_strjoin.c	\
							length.c pid_singleton.c pipe_singleton.c pipe_list.c

MAIN_SRCS				:=	$(addprefix $(MAIN_SRC_DIR), $(MAIN_SRCS))
BONUS_SRCS				:=	$(addprefix $(BONUS_SRC_DIR), $(BONUS_SRCS))
SHARED_SRCS				:=	$(addprefix $(SHARED_SRC_DIR), $(SHARED_SRCS))

HEADER					=	includes/pipex.h

#MAIN_OBJ_DIR			=	main_objs/
#BONUS_OBJ_DIR			=	bonus_objs/
#SHARED_OBJ_DIR			=	shared_objs/

OBJ_DIR					=	objs/

OBJS					=	$(MAIN_SRCS:%.c=%.o) $(SHARED_SRCS:%.c=%.o)

$(OBJ_DIR):
						mkdir -p $@

bonus:					$(OBJ_DIR) $(OBJS)

#MAIN_OBJS				=	$(MAIN_SRCS:%.c=%.o)
#BONUS_OBJS				=	$(BONUS_SRCS:%.c=%.o)
#SHARED_OBJS				=	$(SHARED_SRCS:%.c=%.o)
#
#MAIN_OBJS				:=	$(patsubst $(MAIN_SRC_DIR)%, $(MAIN_OBJ_DIR)%, $(MAIN_OBJS))
#BONUS_OBJS				:=	$(patsubst $(BONUS_SRC_DIR)%, $(BONUS_OBJ_DIR)%, $(BONUS_OBJS))
#SHARED_OBJS				:=	$(patsubst $(SHARED_SRC_DIR)%, $(SHARED_OBJ_DIR)%, $(SHARED_OBJS))

#$(MAIN_OBJ_DIR):
#						mkdir -p $@
#$(BONUS_OBJ_DIR):
#						mkdir -p $@
#$(SHARED_OBJ_DIR):
#						mkdir -p $@

$(MAIN_OBJ_DIR)%.o:		$(MAIN_SRC_DIR)%.c $(HEADER) Makefile
						$(COMPILER) $(DEBUG) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)%.o:	$(BONUS_SRC_DIR)%.c $(HEADER) Makefile
						$(COMPILER) $(DEBUG) $(CFLAGS) -c $< -o $@

$(SHARED_OBJ_DIR)%.o:	$(SHARED_SRC_DIR)%.c $(HEADER) Makefile
						$(COMPILER) $(DEBUG) $(CFLAGS) -c $< -o $@

clean:
						rm -rf $(MAIN_OBJ_DIR) $(BONUS_OBJ_DIR) $(SHARED_OBJ_DIR)

fclean:					clean
						rm -f $(NAME)

re:						fclean all

bonusre:				fclean bonus

.PHONY:					all clean fclean re bonusre
