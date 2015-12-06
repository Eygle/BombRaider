#include "Core.hpp"
#include "Champion/Corki.hpp"
#include "Champion/Chogath.hpp"
#include "Champion/Ryze.hpp"
#include "Champion/Nocturne.hpp"
#include "Champion/Minion.hpp"
#include "Champion/Fiddlestick.hpp"

Core::Core()
  : inputManager_(&(this->eventManager_), &(this->input_))
{
}

Core::~Core()
{
}

void	Core::initialize()
{
  Data	*datas = Data::getInstance();

  // Init Windows
  this->window_.setWidth(datas->gameSettings.screenWidth);
  this->window_.setHeight(datas->gameSettings.screenHeight);
  this->window_.create();
  // Init singletone
  datas->gameClock = &this->gameClock_;
  datas->championsPool.push_back(new Champion::Corki);
  datas->championsPool.push_back(new Champion::Chogath);
  datas->championsPool.push_back(new Champion::Ryze);
  datas->championsPool.push_back(new Champion::Nocturne);
  datas->championsPool.push_back(new Champion::Fiddlestick);
  // Init stateManager
  this->stateManager_.init(&this->eventManager_, &this->gameInfos_, &this->gameClock_);
  // Push first states
  datas->soundManager->playSound(Sound::MENU_MUSIC);
  this->stateManager_.push(State::MAINMENU);
  this->stateManager_.push(State::INTRO);
  this->inputManager_.addPad();
  this->inputManager_.addPad();
  // Start input's thread
  this->thread_ = new Threading::Thread<int, Input::InputManager *>
    (&Input::InputManager::ManageInput, &(this->inputManager_));
  this->thread_->create();
}

void	Core::draw()
{
  this->stateManager_.draw();
}
void	Core::unload()
{
  this->thread_->cancel();
  this->inputManager_.removePad();
}

void	Core::update()
{
  if (!this->stateManager_.update())
    this->window_.close();
}
