#include "State/StateManager.hpp"
#include "Menu/GameMenuNext.hpp"

namespace Menu
{
  GameMenuNext::GameMenuNext(GameMenu	*state) : state_(state), data_(Data::getInstance())
  {
    Graphic::ImagePosition  pos(800, 550, 1000, 610);
    this->position_ = pos;
    this->initAffichage(Data::BG_BUTTON, Data::BG_BUTTON_OVER, Data::BG_BUTTON_CLICKED, this->position_);
    this->setTextValue(this->data_->db.getText(this->data_->gameSettings.language, "next"));
    this->setTextSize(18);
    this->centerText();
  }
  GameMenuNext::~GameMenuNext()
  {
  }

  void GameMenuNext::action(char)
  {
    this->state_->saveValue();
    this->data_->states->push(State::SELECTPLAYER1);
  }

  void GameMenuNext::update()
  {
  }

}
