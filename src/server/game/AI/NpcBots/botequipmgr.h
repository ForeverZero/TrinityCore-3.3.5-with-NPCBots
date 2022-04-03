//
// Created by qq821 on 2022/4/2.
//

#ifndef TRINITYCORE_BOTEQUIPMGR_H
#define TRINITYCORE_BOTEQUIPMGR_H

#include "Creature.h"

class BotEquipMgr
{
    public:
        static void InitBotEquip(Creature* bot);
    private:
        static void _initWarriorTankEquip(Creature* bot);
        static void _doEquip(Creature* bot, std::vector<uint32> equipTemplate);
};


#endif //TRINITYCORE_BOTEQUIPMGR_H
