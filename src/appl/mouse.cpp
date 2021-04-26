#include "mouse.hpp"

int MouseViewPort::_button;
double MouseViewPort::_xpos;
double MouseViewPort::_ypos; 
bool MouseViewPort::_clickUsed;
float MouseViewPort::_horAspect;
float MouseViewPort::_verAspect;
unsigned int MouseViewPort::_viewportLeftOffset;
unsigned int MouseViewPort::_viewportBottomOffset;

void MouseViewPort::set_button(int click){
    _button= click;
}

void MouseViewPort::set_pos(double xposition, double yposition)
{
    _xpos = (xposition-_viewportLeftOffset)*_horAspect;
    _ypos = (yposition-_viewportBottomOffset) *_verAspect;
}

void MouseViewPort::set_used(bool status)
{
    _clickUsed=status;
}

bool MouseViewPort::get_used()
{
    return _clickUsed;
}


void MouseViewPort::set_horAspect(float newhor)
{
    _horAspect = newhor;
}

void MouseViewPort::set_verAspect(float newver)
{
    _verAspect=newver;
}

unsigned int MouseViewPort::get_viewportLeftOffset()
{
    return _viewportLeftOffset;
}

void MouseViewPort::set_viewportLeftOffset(unsigned int inLeftOffset)
{
    _viewportLeftOffset=inLeftOffset;
}

void MouseViewPort::set_viewporBottomOffset(unsigned int inBottomOffset)
{
    _viewportBottomOffset = inBottomOffset;
}
