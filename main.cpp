#include <SDL2/SDL.h>
#include <GLES2/gl2.h>

#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#endif

#include "game.hpp"

// Whether we should quit. It is most convenient for this to be filescope right now.
static bool done = false;

struct SDL_graphics {
	int width_;
	int height_;
	SDL_Window * window_;
	SDL_Renderer * renderer_;

	SDL_graphics(int width, int height)
		: width_(width)
		, height_(height)
		, window_(nullptr)
		, renderer_(nullptr)
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2); 
		// Probably not necessary but can't hurt

		SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_OPENGL, &window_, &renderer_);

		int w, h;
		SDL_GetWindowSize(window_, &w, &h);		
	}
};

static std::string locate_assets();

struct program {
	SDL_graphics graphics_;
	std::unique_ptr<game> game_;

	program(int width, int height)
		: graphics_(width, height)
		, game_(new game())
	{
	}
};

static Uint32 last_time = 0;

void loop_iteration(program* prog)
{
	// Now render graphics
	{
		glClear(GL_COLOR_BUFFER_BIT);

		prog->game_->draw();

		// Now flip the frame
		SDL_GL_SwapWindow(prog->graphics_.window_); //->swap_buffers();
	}

	done |= SDL_QuitRequested();
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	int width = 800, height = 600;

	// The mechanism of "emscripten_set_main_loop" is a bit opaque, better not to make this a stack object.
	program * me = new program(width, height);

	// Now enter main loop
	last_time = SDL_GetTicks();

#ifdef EMSCRIPTEN
	emscripten_set_main_loop_arg((em_arg_callback_func)loop_iteration, me, 0, 1);
#else
	while (!done) {
		loop_iteration(me);
	}
        delete me;
#endif


	SDL_Quit();

	return 0;
}
