#ifndef __CHECKBOXLANGUAGE__
#define __CHECKBOXLANGUAGE__

#include <list>

#include "AButton.hpp"
#include "Data.hpp"

namespace Menu
{
  class CheckBoxLanguage : public AButton
  {
  private :
    bool			checked_;
    CheckBoxLanguage		*associate_; 
    Database::e_lang		language_;
    Data			*data_;
  public :
    CheckBoxLanguage(Database::e_lang language);
    ~CheckBoxLanguage();
    
    void	setAssociate(CheckBoxLanguage *associate_);
    virtual	void action(char c);
    virtual	void update();
    virtual	void draw();
  };
  void getLanguageBox(std::list<AButton *> &result);
};

#endif
