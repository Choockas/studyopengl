#pragma once

class MouseViewPort{
private:
    static bool _clickUsed ;
public:
    static void set_button(int click);
    static int get_button()  { return _button;}
    static void set_pos(double xposition,double yposition);
    static double get_xpos(){ return _xpos;}
    static double get_ypos(){ return _ypos;}
    static void set_used(bool status);
    static void set_horAspect(float newhor);
    static void set_verAspect(float newver);
    static float get_horAspect()  {return _horAspect;}
    static float get_verAspect(){return _verAspect;}
    static unsigned int get_viewportLeftOffset();
    static void set_viewportLeftOffset(unsigned int inLeftOffset);
    static void set_viewporBottomOffset(unsigned int inBottomOffset);
    static bool get_used();
private:
    static  int _button;
    static double _xpos;
    static double  _ypos;
    static unsigned int _viewportLeftOffset;
    static unsigned int _viewportBottomOffset;
    static float _horAspect ;
    static float _verAspect;
    
};
