#include "Window.hpp"

Window::Window() : m_isRunning(true), m_window(nullptr), m_renderer(nullptr)
{
}

bool    Window::OnInit()
{
        double  red;
        double  green;

        std::cout << "Initializing SDL..." << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return (false);
    }
    m_window = SDL_CreateWindow(
        "SDL Template",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN
    );
    if (m_window != nullptr)
    {
        m_renderer = SDL_CreateRenderer(m_window, -1, 0);
        m_image.Init(1280, 720, m_renderer);
        for (int x = 0; x < 1280; x++)
        {
            for (int y = 0; y < 720; y++)
            {
                m_image.SetPixel(x, y, 1.0, 0.0, 0.0);
                red = (static_cast<double>(x) / 1280.0) * 255.0;
                green = (static_cast<double>(y) / 720.0) * 255.0;
                m_image.SetPixel(x, y, red, green, 0.0);
            }
        }
    }
    else
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return (false);
    }
    return (true);
}

int     Window::Execute()
{
        SDL_Event event;

        if (!OnInit())
                return (-1);
        std::cout << "SDL Initialized!" << std::endl;
        while (m_isRunning)
        {
                while (SDL_PollEvent(&event) != 0)
                        OnEvent(&event);
                OnLoop();
                OnRender();
        }
        OnExit();
        return (0);
}

void    Window::OnEvent(SDL_Event *event)
{
        if (event->type == SDL_QUIT)
                m_isRunning = false;
}

void    Window::OnLoop()
{
}

void    Window::OnRender()
{
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        SDL_RenderClear(m_renderer);
        m_image.Display();
        SDL_RenderPresent(m_renderer);
}

void    Window::OnExit()
{
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        m_window = nullptr;
        SDL_Quit();
}