//
// Created by qq821 on 2022/4/2.
//

#include "botequipmgr.h"
#include "Creature.h"
#include "botcommon.h"
#include "bot_ai.h"
#include "Item.h"
#include "Log.h"
#include "Player.h"
#include "botequiptemplate.h"

const std::map<uint8, uint8> BotPlayerSlotMap = {
        {BOT_SLOT_MAINHAND   ,  EQUIPMENT_SLOT_MAINHAND},
        {BOT_SLOT_OFFHAND    ,  EQUIPMENT_SLOT_OFFHAND},
        {BOT_SLOT_RANGED     ,  EQUIPMENT_SLOT_RANGED},
        {BOT_SLOT_HEAD       ,  EQUIPMENT_SLOT_HEAD},
        {BOT_SLOT_SHOULDERS  ,  EQUIPMENT_SLOT_SHOULDERS},
        {BOT_SLOT_CHEST      ,  EQUIPMENT_SLOT_CHEST},
        {BOT_SLOT_WAIST      ,  EQUIPMENT_SLOT_WAIST},
        {BOT_SLOT_LEGS       ,  EQUIPMENT_SLOT_LEGS},
        {BOT_SLOT_FEET       ,  EQUIPMENT_SLOT_FEET},
        {BOT_SLOT_WRIST      ,  EQUIPMENT_SLOT_WRISTS},
        {BOT_SLOT_HANDS      ,  EQUIPMENT_SLOT_HANDS},
        {BOT_SLOT_BACK       ,  EQUIPMENT_SLOT_BACK},
        {BOT_SLOT_BODY       ,  EQUIPMENT_SLOT_BODY},
        {BOT_SLOT_FINGER1    ,  EQUIPMENT_SLOT_FINGER1},
        {BOT_SLOT_FINGER2    ,  EQUIPMENT_SLOT_FINGER2},
        {BOT_SLOT_TRINKET1   ,  EQUIPMENT_SLOT_TRINKET1},
        {BOT_SLOT_TRINKET2   ,  EQUIPMENT_SLOT_TRINKET2},
        {BOT_SLOT_NECK       ,  EQUIPMENT_SLOT_NECK},
};

typedef std::map<uint8, SlotLevelEquip> BotSpecEquipTemplate;
const BotSpecEquipTemplate WarriorTankEquipTemplate = {
        {BOT_SLOT_MAINHAND,         WarriorTankMainHand     },
        {BOT_SLOT_RANGED,           WarriorRange            },
        {BOT_SLOT_OFFHAND,          WarriorTankOffHand      },
        {BOT_SLOT_HEAD,             WarriorTankHead         },
        {BOT_SLOT_SHOULDERS,        WarriorTankShoulder     },
        {BOT_SLOT_CHEST,            WarriorTankChest        },
        {BOT_SLOT_WAIST,            WarriorTankWaist        },
        {BOT_SLOT_LEGS,             WarriorTankLegs         },
        {BOT_SLOT_FEET,             WarriorTankFeet         },
        {BOT_SLOT_WRIST,            WarriorTankWrist        },
        {BOT_SLOT_HANDS,            WarriorTankHands        },
        {BOT_SLOT_BACK,             StrTankBack             },
        {BOT_SLOT_FINGER1 ,         StrTankFinger1          },
        {BOT_SLOT_FINGER2 ,         StrTankFinger2          },
        {BOT_SLOT_TRINKET1,         TankTrinket1            },
        {BOT_SLOT_TRINKET2,         TankTrinket2            },
        {BOT_SLOT_NECK    ,         StrTankNeck             },
};
const BotSpecEquipTemplate WarriorArmsEquipTemplate = {
        {BOT_SLOT_MAINHAND,         StrDpsMainHand         },
        {BOT_SLOT_RANGED,           WarriorRange           },
//        {BOT_SLOT_OFFHAND,          NoNeedThis      },
        {BOT_SLOT_HEAD,             WarriorDpsHead         },
        {BOT_SLOT_SHOULDERS,        WarriorDpsShoulder     },
        {BOT_SLOT_CHEST,            WarriorDpsChest        },
        {BOT_SLOT_WAIST,            WarriorDpsWaist        },
        {BOT_SLOT_LEGS,             WarriorDpsLegs         },
        {BOT_SLOT_FEET,             WarriorDpsFeet         },
        {BOT_SLOT_WRIST,            WarriorDpsWrist        },
        {BOT_SLOT_HANDS,            WarriorDpsHands        },
        {BOT_SLOT_BACK,             StrDpsBack             },
        {BOT_SLOT_FINGER1 ,         StrDpsFinger1          },
        {BOT_SLOT_FINGER2 ,         StrDpsFinger2          },
        {BOT_SLOT_TRINKET1,         StrDpsTrinket1         },
        {BOT_SLOT_TRINKET2,         StrDpsTrinket2         },
        {BOT_SLOT_NECK    ,         StrDpsNeck             },
};

const BotSpecEquipTemplate WarriorFuryEquipTemplate = {
        {BOT_SLOT_MAINHAND,         StrDpsMainHand         },
        {BOT_SLOT_RANGED,           WarriorRange           },
        {BOT_SLOT_OFFHAND,          StrDpsMainHand         },
        {BOT_SLOT_HEAD,             WarriorDpsHead         },
        {BOT_SLOT_SHOULDERS,        WarriorDpsShoulder     },
        {BOT_SLOT_CHEST,            WarriorDpsChest        },
        {BOT_SLOT_WAIST,            WarriorDpsWaist        },
        {BOT_SLOT_LEGS,             WarriorDpsLegs         },
        {BOT_SLOT_FEET,             WarriorDpsFeet         },
        {BOT_SLOT_WRIST,            WarriorDpsWrist        },
        {BOT_SLOT_HANDS,            WarriorDpsHands        },
        {BOT_SLOT_BACK,             StrDpsBack             },
        {BOT_SLOT_FINGER1 ,         StrDpsFinger1          },
        {BOT_SLOT_FINGER2 ,         StrDpsFinger2          },
        {BOT_SLOT_TRINKET1,         StrDpsTrinket1         },
        {BOT_SLOT_TRINKET2,         StrDpsTrinket2         },
        {BOT_SLOT_NECK    ,         StrDpsNeck             },
};

const BotSpecEquipTemplate PaladinTankEquipTemplate = {
        {BOT_SLOT_MAINHAND,         WarriorTankMainHand     },
        {BOT_SLOT_RANGED,           PaladinTankRange        },
        {BOT_SLOT_OFFHAND,          WarriorTankOffHand      },
        {BOT_SLOT_HEAD,             PaladinTankHead         },
        {BOT_SLOT_SHOULDERS,        PaladinTankShoulder     },
        {BOT_SLOT_CHEST,            PaladinTankChest        },
        {BOT_SLOT_WAIST,            PaladinTankWaist        },
        {BOT_SLOT_LEGS,             PaladinTankLegs         },
        {BOT_SLOT_FEET,             PaladinTankFeet         },
        {BOT_SLOT_WRIST,            PaladinTankWrist        },
        {BOT_SLOT_HANDS,            PaladinTankHands        },
        {BOT_SLOT_BACK,             StrTankBack             },
        {BOT_SLOT_FINGER1 ,         StrTankFinger1          },
        {BOT_SLOT_FINGER2 ,         StrTankFinger2          },
        {BOT_SLOT_TRINKET1,         TankTrinket1            },
        {BOT_SLOT_TRINKET2,         TankTrinket2            },
        {BOT_SLOT_NECK    ,         StrTankNeck             },
};

const BotSpecEquipTemplate PaladinRetributionEquipTemplate = {
        {BOT_SLOT_MAINHAND,         StrDpsMainHand               },
        {BOT_SLOT_RANGED,           PaladinRetributionRange      },
//        {BOT_SLOT_OFFHAND,          no need this      },
        {BOT_SLOT_HEAD,             PaladinRetributionHead       },
        {BOT_SLOT_SHOULDERS,        PaladinRetributionShoulder   },
        {BOT_SLOT_CHEST,            PaladinRetributionChest      },
        {BOT_SLOT_WAIST,            PaladinRetributionWaist      },
        {BOT_SLOT_LEGS,             PaladinRetributionLegs       },
        {BOT_SLOT_FEET,             PaladinRetributionFeet       },
        {BOT_SLOT_WRIST,            PaladinRetributionWrist     },
        {BOT_SLOT_HANDS,            PaladinRetributionHands     },
        {BOT_SLOT_BACK,             StrDpsBack                   },
        {BOT_SLOT_FINGER1 ,         StrDpsFinger1                },
        {BOT_SLOT_FINGER2 ,         StrDpsFinger2                },
        {BOT_SLOT_TRINKET1,         StrDpsTrinket1               },
        {BOT_SLOT_TRINKET2,         StrDpsTrinket2               },
        {BOT_SLOT_NECK    ,         StrDpsNeck                   },
};

const BotSpecEquipTemplate PaladinHolyEquipTemplate = {
        {BOT_SLOT_MAINHAND,         PaladinHolyMainHand               },
        {BOT_SLOT_RANGED,           PaladinHolyRange                  },
        {BOT_SLOT_OFFHAND,          PaladinHolyOffHand                },
        {BOT_SLOT_HEAD,             PaladinHolyHead                   },
        {BOT_SLOT_SHOULDERS,        PaladinHolyShoulder               },
        {BOT_SLOT_CHEST,            PaladinHolyChest                  },
        {BOT_SLOT_WAIST,            PaladinHolyWaist                  },
//        {BOT_SLOT_LEGS,             PaladinRetributionLegs       },
//        {BOT_SLOT_FEET,             PaladinRetributionFeet       },
//        {BOT_SLOT_WRIST,            PaladinRetributionWrist     },
//        {BOT_SLOT_HANDS,            PaladinRetributionHands     },
//        {BOT_SLOT_BACK,             StrDpsBack                   },
//        {BOT_SLOT_FINGER1 ,         StrDpsFinger1                },
//        {BOT_SLOT_FINGER2 ,         StrDpsFinger2                },
//        {BOT_SLOT_TRINKET1,         StrDpsTrinket1               },
//        {BOT_SLOT_TRINKET2,         StrDpsTrinket2               },
//        {BOT_SLOT_NECK    ,         StrDpsNeck                   },
};

const std::map<uint8, BotSpecEquipTemplate> AllBotSpecEquipTemplate = {
        {BOT_SPEC_WARRIOR_PROTECTION,       WarriorTankEquipTemplate        },
        {BOT_SPEC_WARRIOR_ARMS,             WarriorArmsEquipTemplate        },
        {BOT_SPEC_WARRIOR_FURY,             WarriorFuryEquipTemplate        },
        {BOT_SPEC_PALADIN_PROTECTION,       PaladinTankEquipTemplate        },
        {BOT_SPEC_PALADIN_RETRIBUTION,      PaladinRetributionEquipTemplate },
        {BOT_SPEC_PALADIN_HOLY,             PaladinHolyEquipTemplate        },
};

void BotEquipMgr::InitBotEquip(Creature* bot) {
    // 找到天赋模板
    auto templateItr = AllBotSpecEquipTemplate.find(bot->GetBotAI()->GetSpec());
    if (templateItr == AllBotSpecEquipTemplate.end()) {
        bot->Say("not equip template found for my current spec.", LANG_COMMON);
        return;
    }

    // 根据每个slot决定给BOT穿什么装备
    for (uint8 slot = BOT_SLOT_MAINHAND; slot < BOT_INVENTORY_SIZE; ++slot) {

        uint8 spec = bot->GetBotAI()->GetSpec();

        // 找到SLOT模板
        BotSpecEquipTemplate bset = templateItr->second;
        auto slotItr = bset.find(slot);
        if (slotItr == bset.end()) {
            TC_LOG_WARN("server.loading", "equip template not found for spec %u, slot %u", spec, slot);
            continue;
        }
        std::map<uint32, uint32> slotLevelEquip = slotItr->second;

        // bot slot 转为player slot
        uint32 slotLevel = _getSlotLevel(bot, slot);
        if (slotLevel == 0) {
            TC_LOG_ERROR("server.loading", "bot slot %u, get player slot level %u", slot, slotLevel);
            continue;
        }

        // 找出最接近slotLevel的itemId
        uint32 itemId = 0;
        for (auto itr = slotLevelEquip.begin(); itr != slotLevelEquip.end(); ++itr) {
            if (itr->first > slotLevel)
                break;
            itemId = itr->second;
        }
        if (itemId == 0) {
            TC_LOG_WARN("server.loading", "spec %u, slot %u, level %u, item id not found", spec, slot, slotLevel);
            continue;
        }

        // 给BOT穿上
        Item* item = Item::CreateItem(itemId, 1);
        if (!item) {
            TC_LOG_ERROR("server.loading", "failed to create item %u", itemId);
            continue;
        }
        if (!bot->GetBotAI()->Equip(slot, item, bot->GetOwnerGUID())) {
            TC_LOG_ERROR("server.loading", "failed to equip item %u", itemId);
            continue;
        }
    }
}

uint32 BotEquipMgr::_getSlotLevel(Creature* bot, uint8 slot) {
    Player* owner = bot->GetBotOwner();
    if (!owner)
        return 0;
    if (owner->GetLevel() < 80)
        return owner->GetLevel();
    uint8 pSlot = _mapBotSlotToPlayerSlot(slot);
    if (pSlot < EQUIPMENT_SLOT_START || pSlot > EQUIPMENT_SLOT_END) {
        TC_LOG_ERROR("server.loading", "pSlot %u convert to pSlot %u", slot, pSlot);
        return 0;
    }
    // 如果玩家副手没有装备，返回主手
    Item* slotEquip = owner->GetItemByPos(INVENTORY_SLOT_BAG_0, pSlot);
    if (!slotEquip) {
        if (slot == BOT_SLOT_OFFHAND)
            return _getSlotLevel(bot, BOT_SLOT_MAINHAND);
        else
            return 187;
    }
    uint32 itemLevel = slotEquip->GetTemplate()->ItemLevel;
    return itemLevel < 187 ? 187 : itemLevel;
}

uint8 BotEquipMgr::_mapBotSlotToPlayerSlot(uint8 pSlot) {
    auto itr = BotPlayerSlotMap.find(pSlot);
    if (itr == BotPlayerSlotMap.end())
        return EQUIPMENT_SLOT_END + 1;
    return itr->second;
}