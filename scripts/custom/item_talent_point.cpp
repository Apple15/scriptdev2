#include "precompiled.h"

bool ItemUse_item_talent_point(Player* pPlayer, Item* pItem, const SpellCastTargets &pTargets)
{
if ((pPlayer->isInCombat()) || (pPlayer->IsTaxiFlying()) || (pPlayer->isDead()))
{
      pPlayer->SendEquipError(EQUIP_ERR_NOT_IN_COMBAT, pItem, NULL);
        return false;
}
      pPlayer->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
{
      pPlayer->SetFreeTalentPoints(1);
      pPlayer->SendTalentsInfoData(false);
      pPlayer->DestroyItemCount(pItem->GetEntry(),1,true);
      return true;
}
}
void AddSC_item_talent_point()
{
    Script *newscript;

      newscript = new Script;
    newscript->Name="item_talent_point";
    newscript->pItemUse = &ItemUse_item_talent_point;
    newscript->RegisterSelf();
}