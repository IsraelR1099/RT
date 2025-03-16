#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SDL2/SDL.h>
# include <iostream>

# include "Image.hpp"

class Window
{
    private:
        bool            m_isRunning;
        SDL_Window*     m_window;
        SDL_Renderer*   m_renderer;
        Image           m_image;
    public:
        Window();
        ~Window() = default;
        int     Execute();
        bool    OnInit();
        void    OnEvent(SDL_Event* event);
        void    OnLoop();
        void    OnRender();
        void    OnExit();
};
#endif