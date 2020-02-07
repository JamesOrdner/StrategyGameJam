#ifndef SDLMath_hpp
#define SDLMath_hpp

#include <SDL_rect.h>
#include <cfloat>

SDL_Point operator+(const SDL_Point& lhs, const SDL_Point& rhs);

void operator+=(SDL_Point& lhs, const SDL_Point& rhs);

SDL_Point operator-(const SDL_Point& lhs, const SDL_Point& rhs);

void operator-=(SDL_Point& lhs, const SDL_Point& rhs);

SDL_FPoint operator+(const SDL_FPoint& lhs, const SDL_FPoint& rhs);

void operator+=(SDL_FPoint& lhs, const SDL_FPoint& rhs);

SDL_FPoint operator-(const SDL_FPoint& lhs, const SDL_FPoint& rhs);

void operator-=(SDL_FPoint& lhs, const SDL_FPoint& rhs);

SDL_FPoint operator*(const SDL_FPoint& lhs, float rhs);

SDL_FPoint operator*(const SDL_FPoint& lhs, const SDL_FPoint& rhs);

SDL_FPoint operator/(const SDL_FPoint& lhs, float rhs);

SDL_FPoint operator/(const SDL_FPoint& lhs, const SDL_FPoint& rhs);

SDL_FPoint normalize(const SDL_FPoint& a);

float dist(const SDL_FPoint& a, const SDL_FPoint& b);

#endif /* SDLMath_hpp */
