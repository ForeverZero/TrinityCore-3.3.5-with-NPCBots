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
        static uint32 _findBestEquipForSlot(Creature* bot, uint8 slot);
        static uint32 _getSlotLevel(Creature* bot, uint8 slot);
        static uint8 _mapBotSlotToPlayerSlot(uint8 pSlot);
};


#endif //TRINITYCORE_BOTEQUIPMGR_H
