#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "../common/viewgame.h"

/**
 * @brief Enumeração que representa os jogos.
 */
enum EnumChoice {
  Trivia, 
  Perfil
};

class ViewManager : public ViewGame{
  
  public:
    ViewManager();
    EnumChoice displayStart();
    bool displayRules() override;

};

#endif