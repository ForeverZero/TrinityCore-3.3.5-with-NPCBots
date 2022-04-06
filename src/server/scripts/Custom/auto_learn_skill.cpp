//
// Created by qq821 on 2022/4/5.
//

#include "ScriptMgr.h"
#include "Player.h"
#include "DBCStructure.h"
#include "DBCStore.h"
#include "Trainer.h"
#include "ObjectMgr.h"

class auto_learn_skill : PlayerScript {
public:
    auto_learn_skill () : PlayerScript("auto_learn_skill"){}
    void OnLevelChanged(Player* player, uint8) override {
        std::vector<Trainer::Trainer const*> const& trainers = sObjectMgr->GetClassTrainers(player->GetClass());

        bool hadNew;
        do
        {
            hadNew = false;
            for (Trainer::Trainer const* trainer : trainers)
            {
                if (!trainer->IsTrainerValidForPlayer(player))
                    continue;
                for (Trainer::Spell const& trainerSpell : trainer->GetSpells())
                {
                    if (!trainer->CanTeachSpell(player, &trainerSpell))
                        continue;

                    if (trainerSpell.IsCastable())
                        player->CastSpell(player, trainerSpell.SpellId, true);
                    else
                        player->LearnSpell(trainerSpell.SpellId, false);

                    hadNew = true;
                }
            }
        } while (hadNew);
    }
};

void AddSC_als() {
    new auto_learn_skill();
}