default: all

trapezio: trapezio_composto.c
	gcc trapezio_composto.c -o trapezio_composto -lm

simpson: simpson_composto.c
	gcc simpson_composto.c -o simpson_composto -lm

mc_1d: monte_carlo_unidimensional.c
	gcc monte_carlo_unidimensional.c -o monte_carlo_unidimensional -lm

mc_2d: monte_carlo_bidimensional.c
	gcc monte_carlo_bidimensional.c -o monte_carlo_bidimensional -lm

all: trapezio simpson mc_1d mc_2d
