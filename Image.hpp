#ifndef IMAGE_HPP
# define IMAGE_HPP

# include <string>
# include <iostream>
# include <vector>
# include <SDL2/SDL.h>

class Image
{
    private:
        uint32_t    ConvertColor(const double r, const double g, const double b);
        void        InitTexture();

        std::vector<std::vector<double>>    m_rChannel;
        std::vector<std::vector<double>>    m_gChannel;
        std::vector<std::vector<double>>    m_bChannel;
        int                                 m_x;
        int                                 m_y;
        SDL_Renderer                        *m_renderer;
        SDL_Texture                         *m_texture;
     public:
        Image();
        ~Image();
        void        Init(const int x, const int y, SDL_Renderer *renderer);
        void        SetPixel(const int x, const int y, const double r, const double g, const double b);
        void        Display();        
};
#endif