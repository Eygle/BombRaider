CC		=	g++

RM		=	rm -f

CPPFLAGS	=	-Wall -Wextra -Werror
CPPFLAGS	+=	 -I./includes -I./libs/kompex -I./libs/libgdl_gl-2012.4/ -I./libs/Sounds

LDFLAGS		=	-lpthread -ldl -lgdl_gl -lGL -lGLU -lkompex-sqlite-wrapper -lfmodex64-4.44.14
LDFLAGS		+=	-Llibs/bin -lticpp

NAME		=	bomberman

LINK		=	./srcs/

GRAPHIC		=	$(LINK)Graphic/

CHARACTER	=	$(LINK)Character/

CHAMPION	=	$(LINK)Champion/

DATABASE	=	$(LINK)Database/

THREADING	=	$(LINK)Threading/

MAP		=	$(LINK)Map/

INPUT		=	$(LINK)Input/

STATE		=	$(LINK)State/

MENU		=	$(LINK)Menu/

MENU_BIND	=	$(MENU)Binding/

CLOCK		=	$(LINK)Clock/

SOUND		=	$(LINK)Sound/

SRCS		=	$(LINK)main.cpp \
			$(LINK)Data.cpp \
			$(LINK)Profile.cpp \
			$(LINK)Statistics.cpp \
			$(LINK)Status.cpp \
			$(LINK)Core.cpp \
			$(LINK)GameSettings.cpp \
			$(LINK)GameInfo.cpp \
			$(CLOCK)Clock.cpp \
			$(CLOCK)Time.cpp \
			$(CHARACTER)Character.cpp \
			$(CHARACTER)AI.cpp \
			$(CHARACTER)Player.cpp \
			$(CHAMPION)Minion.cpp\
			$(CHAMPION)Champion.cpp\
			$(CHAMPION)Chogath.cpp\
			$(CHAMPION)ChogathSkill.cpp \
			$(CHAMPION)Corki.cpp\
			$(CHAMPION)Fiddlestick.cpp \
			$(CHAMPION)Nocturne.cpp\
			$(CHAMPION)Ryze.cpp\
			$(CHAMPION)ASkill.cpp \
			$(CHAMPION)BuffSkill.cpp \
			$(CHAMPION)CorkiSkill.cpp \
			$(DATABASE)Database.cpp \
			$(GRAPHIC)AObject.cpp \
			$(GRAPHIC)Camera.cpp \
			$(GRAPHIC)GuiImage.cpp \
			$(GRAPHIC)Graphic.cpp \
			$(GRAPHIC)GraphicGui.cpp \
			$(GRAPHIC)Model.cpp \
			$(GRAPHIC)Primitive.cpp \
			$(GRAPHIC)Vector3f.cpp \
			$(INPUT)Event.cpp \
			$(INPUT)EventHandler.cpp \
			$(INPUT)EventManager.cpp \
			$(INPUT)InputManager.cpp \
			$(INPUT)MouseHandler.cpp \
			$(INPUT)Pad.cpp \
			$(MAP)ABomb.cpp \
			$(MAP)AEntity.cpp \
			$(MAP)ARessource.cpp \
			$(MAP)BombInfo.cpp \
			$(MAP)Box.cpp \
			$(MAP)BrainRessource.cpp \
			$(MAP)Buff.cpp \
			$(MAP)ClassicBomb.cpp \
			$(MAP)Explosion.cpp \
			$(MAP)FufuBomb.cpp \
			$(MAP)FufuRessource.cpp \
			$(MAP)GameMap.cpp \
			$(MAP)MapCase.cpp \
			$(MAP)MissileBomb.cpp \
			$(MAP)MissileRessource.cpp \
			$(MAP)RebonBomb.cpp \
			$(MAP)RebonRessource.cpp \
			$(MAP)XBomb.cpp \
			$(MAP)XRessource.cpp \
			$(MAP)PiercingBomb.cpp \
			$(MAP)PiercingRessource.cpp \
			$(MAP)MineBomb.cpp \
			$(MAP)MineRessource.cpp \
			$(MAP)Wall.cpp \
			$(MENU)AButton.cpp \
			$(MENU)CreditState.cpp \
			$(MENU)MenuCamera.cpp \
			$(MENU)MenuState.cpp \
			$(MENU)MainMenu.cpp \
			$(MENU)SimpleButton.cpp \
			$(MENU)CheckBoxLanguage.cpp \
			$(MENU)CheckBoxMap.cpp \
			$(MENU)PauseState.cpp \
			$(MENU)SoundSwitcher.cpp \
			$(MENU)SettingState.cpp \
			$(MENU)SelectPlayer.cpp \
			$(MENU)SelectPlayerButton.cpp \
			$(MENU)SelectPlayerArrayButton.cpp \
			$(MENU)SwitchStateButton.cpp \
			$(MENU)SaveButton.cpp \
			$(MENU)LoadButton.cpp \
			$(MENU)GameMenu.cpp \
			$(MENU)GameMenuNext.cpp \
			$(MENU)Switcher.cpp \
			$(MENU)PlayerSwitcher.cpp \
			$(MENU)IntroState.cpp \
			$(MENU)AISwitcher.cpp \
			$(MENU)MapSizeSwitcher.cpp \
			$(MENU)FrequencySwitcher.cpp \
			$(MENU)ProfilInput.cpp \
			$(MENU)ScoreState.cpp \
			$(MENU)SettingBackButton.cpp \
			$(MENU)AIDificultySwitcher.cpp \
			$(MENU_BIND)Binding.cpp \
			$(MENU_BIND)KeyButton.cpp \
			$(MENU_BIND)CheckBox.cpp \
			$(SOUND)FmodManager.cpp \
			$(SOUND)FmodSound.cpp \
			$(STATE)Arcade.cpp \
			$(STATE)AState.cpp \
			$(STATE)StateManager.cpp \
			$(THREADING)Mutex.cpp

OBJS		=	$(SRCS:.cpp=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

prepare		:	cp -r libs/bin_x86_64/* /usr/lib/ 

prepare_x86	:	cp -r libs/bin_x86 /usr/lib32

clean		:
			@$(RM) $(OBJS)

fclean		:	clean
			@$(RM) $(NAME)

re		:	fclean all
