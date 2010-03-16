#include "precompiled.h"

bool GossipHello_npc_morph(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM(0,"Illidan Morph",GOSSIP_SENDER_MAIN,1000);
	pPlayer->ADD_GOSSIP_ITEM(0,"Lich King Morph",GOSSIP_SENDER_MAIN,2000);

	pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetGUID());
	return true;
}

void SendDefaultMenu_npc_morph(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
	// Not allow in combat
    if (pPlayer->isInCombat())
    {
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->MonsterSay("You are in combat", LANG_UNIVERSAL, NULL);
    return;
    }

	switch(uiAction)
	{
	case 1000: //Illidan
		pPlayer->SetDisplayId(21135);
		pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X,0.4f);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;
	case 2000: //Lich King
		pPlayer->SetDisplayId(27481);
		pPlayer->SetFloatValue(OBJECT_FIELD_SCALE_X,0.8f);
		pPlayer->CLOSE_GOSSIP_MENU();
		break;


	}

}

bool GossipSelect_npc_morph(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	if (uiSender == GOSSIP_SENDER_MAIN)
	SendDefaultMenu_npc_morph(pPlayer, pCreature, uiAction);
	return true;
}

void AddSC_npc_morph()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_morph";
    newscript->pGossipHello =  &GossipHello_npc_morph;
    newscript->pGossipSelect = &GossipSelect_npc_morph;
    newscript->RegisterSelf();
}