#ifndef COLORS_HH
# define COLORS_HH

class Colors
{

  public:

    static const int BLACK = 0;
    static const int RED = 1;  
    static const int GREEN = 2;
    static const int BLUE = 4;
    static const int MAGENTA = 5;
    static const int CYAN = 6;
    static const int WHITE = 7;

    void cout(int fg);
    void cend();
    void textcolor(int attr, int fg, int bg);

    Colors();
    ~Colors();
};

#endif
