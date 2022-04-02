//
// Created by qq821 on 2022/4/2.
//

#include "botequipmgr.h"
#include "Creature.h"
#include "botcommon.h"
#include "bot_ai.h"

bool BotEquipMgr::InitBotEquip(Creature* bot) {
    return false;
}

bool BotEquipMgr::ClearBotEquip(Creature *bot) {
    for (uint8 slot = BOT_SLOT_MAINHAND; slot < BOT_INVENTORY_SIZE; slot++)
        if (!bot->GetBotAI()->UnEquip(slot, bot->GetOwnerGUID()))
            return false;
    return true;
}