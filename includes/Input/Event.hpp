#ifndef __EVENT__
#define __EVENT__

#include <GDL/Input.hpp>

namespace Input
{
  enum e_eventState
    {
      RELEASE = 0,
      PRESSED,
      NOTHING
    };

  enum    Key
    {
      A, B, C, D, E, F, G, H, I, J, K, L, M,
      N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
      Num0, Num1, Num2, Num3, Num4,
      Num5, Num6, Num7, Num8, Num9,
      Escape, LControl, LShift, LAlt, LSystem,
      RControl, RShift, RAlt, RSystem, Menu,
      LBracket, RBracket, SemiColon, Comma,
      Period, Quote, Slash, BackSlash, Tilde,
      Equal, Dash, Space, Return, Back, Tab,
      PageUp, PageDown, End, Home, Insert,
      Delete, Add, Subtract, Multiply,
      Divide, Left, Right, Up, Down,
      Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
      Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
      F1, F2, F3, F4, F5, F6, F7, F8, F9,
      F10, F11, F12, F13, F14, F15,
      Pause, Count,
      LJ1, RJ1, LB1, RB1, CD1, Back1, Start1, LT1, RT1, A1, B1, X1, Y1, LJP1, RJP1, MidleB1,
      LJ2, RJ2, LB2, RB2, CD2, Back2, Start2, LT2, RT2, A2, B2, X2, Y2, LJP2, RJP2, MidleB2,
      NONE
    };

  class Event
  {
  private :
    Key			key_;
    e_eventState	state_;
    float		value_;
  public:
    Event(Key key, e_eventState state, float value);
    Event();
    ~Event();
    Key			getKeys() const;
    e_eventState	getState() const;
    int			getValue() const;
    void		setKeys(Key	  key_);
    void		setState(e_eventState state);
    void		setValue(float value);
  };
}

#endif
