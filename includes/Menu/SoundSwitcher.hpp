#ifndef __SOUNDSWITCHER__
#define __SOUNDSWITCHER__

#include "Data.hpp"
#include "AButton.hpp"
#include "Sound/ISoundManager.hpp"

namespace Menu
{
  class SoundSwitcher : public AButton
  {
  private :
    unsigned int		value_;
    int				barex1_;
    Sound::e_soundType		type_;
    Graphic::ImagePosition 	cposition_;
    Graphic::ImagePosition 	bposition_;
    Graphic::GuiImage		cursor_;
    Data			*data_;
  public :
    SoundSwitcher(Sound::e_soundType type);
    ~SoundSwitcher();

    virtual void	update();
    virtual void	action(char c);
    virtual void	draw();
    void		setValue(int y);
    void		setCursorPosition(int x1, int y1, int x2, int y2);
    void		setCursor(const Graphic::GuiImage &cursor);
    void		setBarrePosition(int x1, int y1, int x2, int y2);
    void		updateCursor();
    bool		isSelected(int x, int y);
    void		updateFromValue();
    void		setValueDir(int value);
  };

  std::list<SoundSwitcher *> initSoundSwitcher(void);
};

#endif
