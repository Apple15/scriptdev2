/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Instance_Black_Temple
SD%Complete: 100
SDComment: Instance Data Scripts and functions to acquire mobs and set encounter status for use in various Black Temple Scripts
SDCategory: Black Temple
EndScriptData */

#include "precompiled.h"
#include "def_black_temple.h"

/* Black Temple encounters:
0 - High Warlord Naj'entus event
1 - Supremus Event
2 - Shade of Akama Event
3 - Teron Gorefiend Event
4 - Gurtogg Bloodboil Event
5 - Reliquary Of Souls Event
6 - Mother Shahraz Event
7 - Illidari Council Event
8 - Illidan Stormrage Event
*/

struct MANGOS_DLL_DECL instance_black_temple : public ScriptedInstance
{
    instance_black_temple(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint32 m_uiEncounter[ENCOUNTERS];
    std::string strInstData;

    uint64 m_uiNajentusGUID;
    uint64 m_uiAkamaGUID;                                   // This is the Akama that starts the Illidan encounter.
    uint64 m_uiAkama_ShadeGUID;                             // This is the Akama that starts the Shade of Akama encounter.
    uint64 m_uiShadeOfAkamaGUID;
    uint64 m_uiSupremusGUID;
    uint64 m_uiLadyMalandeGUID;
    uint64 m_uiGathiosTheShattererGUID;
    uint64 m_uiHighNethermancerZerevorGUID;
    uint64 m_uiVerasDarkshadowGUID;
    uint64 m_uiIllidariCouncilGUID;
    uint64 m_uiBloodElfCouncilVoiceGUID;
    uint64 m_uiIllidanStormrageGUID;

    uint64 m_uiNajentusGateGUID;
    uint64 m_uiMainTempleDoorsGUID;
    uint64 m_uiIllidanGateGUID;
    uint64 m_uiIllidanDoorGUID[2];
    uint64 m_uiShahrazPreDoorGUID;
    uint64 m_uiShahrazPostDoorGUID;
    uint64 m_uiCouncilDoorGUID;

    void Initialize()
    {
        m_uiNajentusGUID = 0;
        m_uiAkamaGUID = 0;
        m_uiAkama_ShadeGUID = 0;
        m_uiShadeOfAkamaGUID = 0;
        m_uiSupremusGUID = 0;
        m_uiLadyMalandeGUID = 0;
        m_uiGathiosTheShattererGUID = 0;
        m_uiHighNethermancerZerevorGUID = 0;
        m_uiVerasDarkshadowGUID = 0;
        m_uiIllidariCouncilGUID = 0;
        m_uiBloodElfCouncilVoiceGUID = 0;
        m_uiIllidanStormrageGUID = 0;

        m_uiNajentusGateGUID    = 0;
        m_uiMainTempleDoorsGUID = 0;
        m_uiIllidanGateGUID     = 0;
        m_uiIllidanDoorGUID[0]  = 0;
        m_uiIllidanDoorGUID[1]  = 0;
        m_uiShahrazPreDoorGUID  = 0;
        m_uiShahrazPostDoorGUID = 0;
        m_uiCouncilDoorGUID     = 0;

        for(uint8 i = 0; i < ENCOUNTERS; i++)
            m_uiEncounter[i] = NOT_STARTED;
    }

    bool IsEncounterInProgress() const
    {
        for(uint8 i = 0; i < ENCOUNTERS; i++)
            if (m_uiEncounter[i] == IN_PROGRESS) return true;

        return false;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case 22887: m_uiNajentusGUID                = pCreature->GetGUID(); break;
            case 23089: m_uiAkamaGUID                   = pCreature->GetGUID(); break;
            case 22990: m_uiAkama_ShadeGUID             = pCreature->GetGUID(); break;
            case 22841: m_uiShadeOfAkamaGUID            = pCreature->GetGUID(); break;
            case 22898: m_uiSupremusGUID                = pCreature->GetGUID(); break;
            case 22917: m_uiIllidanStormrageGUID        = pCreature->GetGUID(); break;
            case 22949: m_uiGathiosTheShattererGUID     = pCreature->GetGUID(); break;
            case 22950: m_uiHighNethermancerZerevorGUID = pCreature->GetGUID(); break;
            case 22951: m_uiLadyMalandeGUID             = pCreature->GetGUID(); break;
            case 22952: m_uiVerasDarkshadowGUID         = pCreature->GetGUID(); break;
            case 23426: m_uiIllidariCouncilGUID         = pCreature->GetGUID(); break;
            case 23499: m_uiBloodElfCouncilVoiceGUID    = pCreature->GetGUID(); break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case 185483:                                    // Gate past Naj'entus (at the entrance to Supermoose's courtyards)
                m_uiNajentusGateGUID = pGo->GetGUID();
                break;
            case 185882:                                    // Main Temple Doors - right past Supermoose (Supremus)
                m_uiMainTempleDoorsGUID = pGo->GetGUID();
                break;
            case 185479:                                    // Door leading to Mother Sharaz
                m_uiShahrazPreDoorGUID = pGo->GetGUID();
                break;
            case 185481:                                    // Door leading to the Council (grand promenade)
                m_uiCouncilDoorGUID = pGo->GetGUID();
                break;
            case 185482:                                    // Door after shahraz
                m_uiShahrazPostDoorGUID = pGo->GetGUID();
                break;
            case 185905:                                    // Gate leading to Temple Summit
                m_uiIllidanGateGUID = pGo->GetGUID();
                break;
            case 186261:                                    // Right door at Temple Summit
                m_uiIllidanDoorGUID[0] = pGo->GetGUID();
                break;
            case 186262:                                    // Left door at Temple Summit
                m_uiIllidanDoorGUID[1] = pGo->GetGUID();
                break;
        }
    }

    uint64 GetData64(uint32 uiData)
    {
        switch(uiData)
        {
            case DATA_HIGHWARLORDNAJENTUS:       return m_uiNajentusGUID;
            case DATA_AKAMA:                     return m_uiAkamaGUID;
            case DATA_AKAMA_SHADE:               return m_uiAkama_ShadeGUID;
            case DATA_SHADEOFAKAMA:              return m_uiShadeOfAkamaGUID;
            case DATA_SUPREMUS:                  return m_uiSupremusGUID;
            case DATA_ILLIDANSTORMRAGE:          return m_uiIllidanStormrageGUID;
            case DATA_GATHIOSTHESHATTERER:       return m_uiGathiosTheShattererGUID;
            case DATA_HIGHNETHERMANCERZEREVOR:   return m_uiHighNethermancerZerevorGUID;
            case DATA_LADYMALANDE:               return m_uiLadyMalandeGUID;
            case DATA_VERASDARKSHADOW:           return m_uiVerasDarkshadowGUID;
            case DATA_ILLIDARICOUNCIL:           return m_uiIllidariCouncilGUID;
            case DATA_GAMEOBJECT_NAJENTUS_GATE:  return m_uiNajentusGateGUID;
            case DATA_GAMEOBJECT_ILLIDAN_GATE:   return m_uiIllidanGateGUID;
            case DATA_GAMEOBJECT_ILLIDAN_DOOR_R: return m_uiIllidanDoorGUID[0];
            case DATA_GAMEOBJECT_ILLIDAN_DOOR_L: return m_uiIllidanDoorGUID[1];
            case DATA_GAMEOBJECT_SUPREMUS_DOORS: return m_uiMainTempleDoorsGUID;
            case DATA_BLOOD_ELF_COUNCIL_VOICE:   return m_uiBloodElfCouncilVoiceGUID;
            case DATA_GO_PRE_SHAHRAZ_DOOR:
                if (m_uiEncounter[2] == DONE && m_uiEncounter[3] == DONE && m_uiEncounter[4] == DONE && m_uiEncounter[5] == DONE)
                {
                    debug_log("SD2: Black Temple: Opening door to Mother Shahraz.");
                    return m_uiShahrazPreDoorGUID;
                }
                debug_log("SD2: Black Temple: Door data to Mother Shahraz requested, cannot open yet (Encounter data: %u %u %u %u)",m_uiEncounter[2],m_uiEncounter[3],m_uiEncounter[4],m_uiEncounter[5]);
                return 0;
            case DATA_GO_POST_SHAHRAZ_DOOR:      return m_uiShahrazPostDoorGUID;
            case DATA_GO_COUNCIL_DOOR:           return m_uiCouncilDoorGUID;
        }

        return 0;
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        debug_log("SD2: Instance Black Temple: SetData received for type %u with data %u",uiType,uiData);

        switch(uiType)
        {
            case TYPE_NAJENTUS:   m_uiEncounter[0] = uiData; break;
            case TYPE_SUPREMUS:   m_uiEncounter[1] = uiData; break;
            case TYPE_SHADE:      m_uiEncounter[2] = uiData; break;
            case TYPE_GOREFIEND:  m_uiEncounter[3] = uiData; break;
            case TYPE_BLOODBOIL:  m_uiEncounter[4] = uiData; break;
            case TYPE_RELIQUIARY: m_uiEncounter[5] = uiData; break;
            case TYPE_SHAHRAZ:    m_uiEncounter[6] = uiData; break;
            case TYPE_COUNCIL:    m_uiEncounter[7] = uiData; break;
            case TYPE_ILLIDAN:    m_uiEncounter[8] = uiData; break;
            default:
                error_log("SD2: Instance Black Temple: ERROR SetData = %u for type %u does not exist/not implemented.",uiType,uiData);
                break;
        }

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << m_uiEncounter[0] << " " << m_uiEncounter[1] << " " << m_uiEncounter[2] << " "
                << m_uiEncounter[3] << " " << m_uiEncounter[4] << " " << m_uiEncounter[5] << " "
                << m_uiEncounter[6] << " " << m_uiEncounter[7] << " " << m_uiEncounter[8];

            strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_NAJENTUS:   return m_uiEncounter[0];
            case TYPE_SUPREMUS:   return m_uiEncounter[1];
            case TYPE_SHADE:      return m_uiEncounter[2];
            case TYPE_GOREFIEND:  return m_uiEncounter[3];
            case TYPE_BLOODBOIL:  return m_uiEncounter[4];
            case TYPE_RELIQUIARY: return m_uiEncounter[5];
            case TYPE_SHAHRAZ:    return m_uiEncounter[6];
            case TYPE_COUNCIL:    return m_uiEncounter[7];
            case TYPE_ILLIDAN:    return m_uiEncounter[8];
        }

        return 0;
    }

    const char* Save()
    {
        return strInstData.c_str();
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);
        loadStream >> m_uiEncounter[0] >> m_uiEncounter[1] >> m_uiEncounter[2] >> m_uiEncounter[3]
            >> m_uiEncounter[4] >> m_uiEncounter[5] >> m_uiEncounter[6] >> m_uiEncounter[7] >> m_uiEncounter[8];

        for(uint8 i = 0; i < ENCOUNTERS; ++i)
            if (m_uiEncounter[i] == IN_PROGRESS)            // Do not load an encounter as "In Progress" - reset it instead.
                m_uiEncounter[i] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_black_temple(Map* pMap)
{
    return new instance_black_temple(pMap);
}

void AddSC_instance_black_temple()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "instance_black_temple";
    newscript->GetInstanceData = &GetInstanceData_instance_black_temple;
    newscript->RegisterSelf();
}
