#include "Image.hpp"

Image::Image() : m_x(0), m_y(0), m_renderer(nullptr), m_texture(nullptr)
{
}

Image::~Image()
{
    if (m_texture != nullptr)
        SDL_DestroyTexture(m_texture);
}

void Image::Init(const int x, const int y, SDL_Renderer *renderer)
{
    m_rChannel.resize(x, std::vector<double>(y, 0.0));
    m_gChannel.resize(x, std::vector<double>(y, 0.0));
    m_bChannel.resize(x, std::vector<double>(y, 0.0));
    m_x = x;
    m_y = y;
    m_renderer = renderer;
    InitTexture();
}

void Image::SetPixel(const int x, const int y, const double r, const double g, const double b)
{
    m_rChannel[x][y] = r;
    m_gChannel[x][y] = g;
    m_bChannel[x][y] = b;
}

void Image::Display()
{
    try
    {
        uint32_t    *tmpPixels = new uint32_t[m_x * m_y];
        SDL_Rect    srcRect = {0, 0, m_x, m_y};
        SDL_Rect    bounds;

        std::fill(tmpPixels, tmpPixels + (m_x * m_y), 0);
        for (int x = 0; x < m_x; x++)
        {
            for (int y = 0; y < m_y; y++)
            {
                tmpPixels[(y * m_x) + x] = ConvertColor(
                    m_rChannel[x][y],
                    m_gChannel[x][y],
                    m_bChannel[x][y]
                );
            }
        }
        SDL_UpdateTexture(m_texture, nullptr, tmpPixels, m_x * sizeof(uint32_t));
        delete[] tmpPixels;
        bounds = srcRect;
        SDL_RenderCopy(m_renderer, m_texture, &srcRect, &bounds);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "Error new: " << e.what() << std::endl;
        return;
    }

}

void Image::InitTexture()
{
    uint32_t    rmask;
    uint32_t    gmask;
    uint32_t    bmask;
    uint32_t    amask;
    SDL_Surface *tmpSurface;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else    
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif
    if (m_texture != nullptr)
        SDL_DestroyTexture(m_texture);
    tmpSurface = SDL_CreateRGBSurface(
        0,
        m_x,
        m_y,
        32,
        rmask,
        gmask,
        bmask,
        amask
    );
    m_texture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

uint32_t Image::ConvertColor(const double r, const double g, const double b)
{
    unsigned char   rByte;
    unsigned char   gByte;
    unsigned char   bByte;
    uint32_t        pixelColor;

    rByte = static_cast<unsigned char>(r);
    gByte = static_cast<unsigned char>(g);
    bByte = static_cast<unsigned char>(b);

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        pixelColor = (rByte << 24) + (gByte << 16) + (bByte << 8) + 0xff;
    #else
        pixelColor = (0xff << 24) + (rByte << 16) + (gByte << 8) + bByte;
    #endif
    return (pixelColor);
}