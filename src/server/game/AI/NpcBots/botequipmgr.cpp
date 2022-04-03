//
// Created by qq821 on 2022/4/2.
//

#include "botequipmgr.h"
#include "Creature.h"
#include "botcommon.h"
#include "bot_ai.h"
#include "Item.h"
#include "Log.h"

const std::vector<uint32> DefaultEquip = {
        0,        // MAINHAND
        0,       // OFFHAND
        0,           // RANGED
        0,           // HEAD
        0,        // SHOULDERS
        0,        // CHEST
        0,       // WAIST
        0,        // LEGS
        0,        // FEET
        0,        // WRIST
        0,        // HANDS
        0,          // BACK
        0,          // BODY
        0,          // FINGER1
        0,          // FINGER2
        0,          // TRINKET1
        0,          // TRINKET2
        0,          // NECK
};

const std::vector<uint32> WarriorTankLevel15Equip = {
        6504,        // MAINHAND
        13245,       // OFFHAND
        0,           // RANGED
        0,           // HEAD
        1744,        // SHOULDERS
        6731,        // CHEST
        12978,       // WAIST
        2166,        // LEGS
        3302,        // FEET
        15400,        // WRIST
        2980,        // HANDS
        0,          // BACK
        0,          // BODY
        0,          // FINGER1
        0,          // FINGER2
        0,          // TRINKET1
        0,          // TRINKET2
        0,          // NECK
};

const std::vector<uint32> WarriorTankLevel30Equip = {
        8225,       // MAINHAND
        4065,       // OFFHAND
        15286,       // RANGED
        7915,       // HEAD
        3841,       // SHOULDERS
        7688,        // CHEST
        10329,       // WAIST
        14766,        // LEGS
        10332,        // FEET
        10333,        // WRIST
        23170,       // HANDS
        13121,       // BACK
        0,       // BODY
        0,       // FINGER1
        0,       // FINGER2
        0,       // TRINKET1
        0,       // TRINKET2
        13084,       // NECK
};

const std::vector<uint32> WarriorTankLevel40Equip = {
        7943,       // MAINHAND
        9918,       // OFFHAND
        15287,       // RANGED
        10763,       // HEAD
        7918,       // SHOULDERS
        14821,        // CHEST
        8159,       // WAIST
        7926,        // LEGS
        8160,        // FEET
        14834,        // WRIST
        13071,       // HANDS
        11311,       // BACK
        0,       // BODY
        0,       // FINGER1
        0,       // FINGER2
        0,       // TRINKET1
        0,       // TRINKET2
        13088,       // NECK
};

const std::vector<uint32> WarriorTankLevel50Equip = {
        2244,       // MAINHAND
        10835,      // OFFHAND
        13022,      // RANGED
        22223,      // HEAD
        14552,      // SHOULDERS
        11678,      // CHEST
        11703,      // WAIST
        11927,      // LEGS
        22270,      // FEET
        19580,      // WRIST
        14855,      // HANDS
        11677,      // BACK
        0,          // BODY
        0,          // FINGER1
        0,          // FINGER2
        0,          // TRINKET1
        0,          // TRINKET2
        11755,      // NECK
};

const std::vector<uint32> WarriorTankLevel60Equip = {
        23054,          // MAINHAND
        23043,          // OFFHAND
        22811,          // RANGED
        21329,          // HEAD
        21330,           // SHOULDERS
        21331,           // CHEST
        21598,          // WAIST
        21332,           // LEGS
        21333,          // FEET
        22671,          // WRIST
        22670,          // HANDS
        22938,          // BACK
        0,          // BODY
        23059,          // FINGER1
        23028,          // FINGER2
        23040,          // TRINKET1
        19406,          // TRINKET2
        22732,          // NECK
};

const std::vector<uint32> WarriorTankLevel70Equip = {
        30311,          // MAINHAND
        30314,          // OFFHAND
        34334,          // RANGED
        30974,          // HEAD
        30980,          // SHOULDERS
        30976,          // CHEST
        34547,          // WAIST
        30978,          // LEGS
        34568,          // FEET
        34442,          // WRIST
        30970,          // HANDS
        34190,          // BACK
        0,          // BODY
        34213,          // FINGER1
        32261,          // FINGER2
        33830,          // TRINKET1
        30629,          // TRINKET2
        34178,          // NECK
};

void BotEquipMgr::InitBotEquip(Creature* bot) {
    switch (bot->GetBotAI()->GetSpec()) {
        case BOT_SPEC_WARRIOR_PROTECTION:
            _initWarriorTankEquip(bot);
            break;
        default:
            bot->Say("equip init does not support for my current spec.", LANG_COMMON);
    }
}

void BotEquipMgr::_initWarriorTankEquip(Creature* bot) {
    uint8 botLevel = bot->GetLevel();
    std::vector<uint32> equipTemplate;

//    if (botLevel >= 15 && botLevel < 30) {
//        equipTemplate = WarriorTankLevel15Equip;
//    }else {
//        bot->Say("not equip template found for my current level and spec.", LANG_COMMON);
//    }

    //debug
    equipTemplate = WarriorTankLevel70Equip;

    _doEquip(bot, equipTemplate);
}

void BotEquipMgr::_doEquip(Creature* bot, std::vector<uint32> equipTemplate) {
    bot_ai* ai = bot->GetBotAI();
    for(uint8 slot = BOT_SLOT_MAINHAND; slot < BOT_INVENTORY_SIZE; slot++) {
        uint32 itemId = equipTemplate[slot];
        if (itemId <= 0)
            continue;
        Item* slotItem = bot->GetBotEquips(slot);
        if (slotItem && slotItem->GetEntry() == itemId)
            continue;

        Item* item = Item::CreateItem(equipTemplate[slot], 1);
        if (!item) {
            TC_LOG_ERROR("misc", "failed to create item %u", itemId);
            continue;
        }
        if (!ai->Equip(slot, item, bot->GetOwnerGUID())) {
            TC_LOG_ERROR("misc", "failed to equip item %u", itemId);
            continue;
        }
    }
}