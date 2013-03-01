
#include "head.hh"

void	Colors::cout(int fg)
{
  textcolor(1, fg, BLACK);
}

void	Colors::cend()
{
  textcolor(0, WHITE, BLACK);
}

void    Colors::textcolor(int attr, int fg, int bg)
{
  if (Datas::SHOW)
    printf("%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
}

Colors::Colors()
{

}

Colors::~Colors()
{

}
