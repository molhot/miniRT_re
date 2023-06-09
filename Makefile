NAME = miniRT
LIBMLX = minilibx-linux/libmlx_Linux.a

SRCS	=	miniRT_main.c\
			ready_vector.c\
			calculate_vector.c\
			constructor/constructor.c\
				constructor/ready_fixvectors/ready_eye_v.c\
				constructor/ready_fixvectors/ready_lgtarr.c\
				constructor/ready_fixvectors/ready_objarr.c\
			exec/draw_pixcel.c\
			exec/grasp_objtype.c\
			exec/map.c\
			exec/RGB_handling.c\
			exec/ray_trans.c\
			exec/exec_minirt.c\
			exec/ch_eye2anyobjs.c\
				exec/ch_anyits/ch_eye2ball_its.c\
				exec/ch_anyits/ch_eye2plane_its.c\
				exec/ch_anyits/ch_eye2cylinder_its.c\
				exec/calculate_ratio/cal_ratio_ball.c\
				exec/calculate_ratio/cal_ratio_plane.c\
				exec/calculate_ratio/cal_ratio_cylinder.c\
				exec/render_obj/render_ball.c\
				exec/render_obj/render_plane.c\
				exec/render_obj/render_cylinder.c

OBJS = $(SRCS:.c=.o)

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -I includes

ifdef TEST
	CFLAGS += -D TEST
endif

test:
	make all TEST=1

all: $(NAME)

${NAME}: ${OBJS} ${LIBMLX}
	${CC} ${OBJS} ${LIBMLX} -lm -lX11 -lXext -o $(NAME)

${LIBMLX}:
	make -C minilibx-linux/

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY:			all clean fclean re bonus