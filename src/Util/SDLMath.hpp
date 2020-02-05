#ifndef SDLMath_hpp
#define SDLMath_hpp

#include <cfloat>

SDL_Point operator+(const SDL_Point& lhs, const SDL_Point& rhs)
{
    return SDL_Point{ lhs.x + rhs.x, lhs.y + rhs.y };
}

void operator+=(SDL_Point& lhs, const SDL_Point& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}

SDL_Point operator-(const SDL_Point& lhs, const SDL_Point& rhs)
{
    return SDL_Point{ lhs.x - rhs.x, lhs.y - rhs.y };
}

void operator-=(SDL_Point& lhs, const SDL_Point& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
}

SDL_FPoint operator+(const SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    return SDL_FPoint{ lhs.x + rhs.x, lhs.y + rhs.y };
}

void operator+=(SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}

SDL_FPoint operator-(const SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    return SDL_FPoint{ lhs.x - rhs.x, lhs.y - rhs.y };
}

void operator-=(SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
}

SDL_FPoint operator*(const SDL_FPoint& lhs, float rhs)
{
    return SDL_FPoint{ lhs.x * rhs, lhs.y * rhs };
}

SDL_FPoint operator*(const SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    return SDL_FPoint{ lhs.x * rhs.x, lhs.y * rhs.y };
}

SDL_FPoint operator/(const SDL_FPoint& lhs, float rhs)
{
    return SDL_FPoint{ lhs.x / rhs, lhs.y / rhs };
}

SDL_FPoint operator/(const SDL_FPoint& lhs, const SDL_FPoint& rhs)
{
    return SDL_FPoint{ lhs.x / rhs.x, lhs.y / rhs.y };
}

SDL_FPoint normalize(const SDL_FPoint& a)
{
    float norm = a.x * a.x + a.y * a.y;
    return (norm < FLT_EPSILON) ? SDL_FPoint{} : a / sqrtf(norm);
}

#endif /* SDLMath_hpp */
