#include <unistd.h>
#include <SDL.h>
#include <math.h>

static double d2r(double degree);
static void draw_point(SDL_Renderer * renderer, int x, int y, int size);

int main(int argc, char *argv[])
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    int done = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	fprintf(stderr, "SDL_Init() failed\n");
	exit(1);
    }

    window = SDL_CreateWindow("Circle",
			      SDL_WINDOWPOS_UNDEFINED,
			      SDL_WINDOWPOS_UNDEFINED,
			      640, 480,
			      SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
	fprintf(stderr, "SDL_CreateWindow() failed\n");
	exit(1);
    }


    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
	fprintf(stderr, "SDL_CreateRenderer() failed\n");
	exit(1);
    }
        
    SDL_Event e;
    while (!done)
    {
	while (SDL_PollEvent(&e) != 0)
	{
	    switch (e.type) {
	    case SDL_QUIT:
		done = 1;
		break;
	    case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
		    done = 1;
		    break;
		default:
		    break;
		}
	    default:
		break;
	    }
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int i;
	for (i = 0; i < 12; i++)
	{
	    float size = 150.0;
	    float angle = d2r(360.0 * (i / 12.0));
	    int cx = 300;
	    int cy = 220;
	    draw_point(renderer,
		       cos(angle) * size + cx,
		       sin(angle) * size + cy,
		       10);
	}
	SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

double d2r(double degree)
{
    double rad =  M_PI / 180.0;
    return degree * rad;
}

void draw_point(SDL_Renderer * renderer, int x, int y, int size)
{
    SDL_Rect rect = {x: x, y: y, w: size, h: size};
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawRect(renderer, &rect);
}
