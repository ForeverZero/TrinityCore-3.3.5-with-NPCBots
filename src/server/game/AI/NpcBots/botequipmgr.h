//
// Created by qq821 on 2022/4/2.
//

#ifndef TRINITYCORE_BOTEQUIPMGR_H
#define TRINITYCORE_BOTEQUIPMGR_H

#include "Creature.h"

class BotEquipMgr
{
    public:
        static bool InitBotEquip(Creature* bot);
        static bool ClearBotEquip(Creature* bot);
};


#endif //TRINITYCORE_BOTEQUIPMGR_H
