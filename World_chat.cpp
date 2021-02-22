//Created by : parranoia 
//Updated & Modified by : JadaDev
//This world_chat sciprt used for EmuCoreCraft Repack
//DO NOT REMOVE CREDITS
//Shared : 2016 / 07 / 27


#include "ScriptPCH.h"
#include "Chat.h"
 
#define FACTION_SPECIFIC 0
 
std::string GetNameLink(Player* player)
{
        std::string name = player->GetName();
        std::string color;
        switch(player->getClass())
        {
        case CLASS_DEATH_KNIGHT:
                color = "|cffC41F3B";
                break;
        case CLASS_DRUID:
                color = "|cffFF7D0A";
                break;
        case CLASS_HUNTER:
                color = "|cffABD473";
                break;
        case CLASS_MAGE:
                color = "|cff69CCF0";
                break;
        case CLASS_PALADIN:
                color = "|cffF58CBA";
                break;
        case CLASS_PRIEST:
                color = "|cffFFFFFF";
                break;
        case CLASS_ROGUE:
                color = "|cffFFF569";
                break;
        case CLASS_SHAMAN:
                color = "|cff0070DE";
                break;
        case CLASS_WARLOCK:
                color = "|cff9482C9";
                break;
        case CLASS_WARRIOR:
                color = "|cffC79C6E";
                break;
        }
        return "|Hplayer:"+name+"|h|cffFFFFFF["+color+name+"|cffFFFFFF]|h|r";
}
 
class world_chat : public CommandScript
{
        public:
        world_chat() : CommandScript("world_chat"){}

		static bool HandleWorldChatCommand(ChatHandler * pChat, const char * args)
		{
			if (!pChat->GetSession()->GetPlayer()->CanSpeak())
				return false;
			std::string temp = args;

			if (!args || temp.find_first_not_of(' ') == std::string::npos)
				return false;

			std::string msg = "";
			Player * player = pChat->GetSession()->GetPlayer();

			switch (player->GetSession()->GetSecurity())
			{
				// Player
			case SEC_PLAYER:
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|TInterface\\icons\\INV_Bijou_Blue:15|t|cFFFFD700[World]|cff0000ff[Alliance] ";
					msg += GetNameLink(player);
					msg += " |cfffaeb00";
				}

				else
				{
					msg += "|TInterface\\icons\\INV_Bijou_Red:15|t|cFFFFD700[World]|cffff0000[Horde] ";
					msg += GetNameLink(player);
					msg += " |cfffaeb00";
				}
				break;
				// V.I.P
			case SEC_MODERATOR:
				if (player->GetTeam() == ALLIANCE)
				{
					msg += "|TInterface\\icons\\Achievement_PVP_A_A:15|t|cffB70093|Alliance]|cffFFFFFF[V|cff28FF28.I|cffFF2424.P] ";
					msg += GetNameLink(player);
					msg += " |cff0000FF";
				}
				
				else
				{
					msg += "|TInterface\\icons\\Achievement_PVP_H_H:15|t|cffB70093|Horde]|cffFFFFFF[V|cff28FF28.I|cffFF2424.P] ";
					msg += GetNameLink(player);
					msg += " |cffFF0000";
				}
				break;
				// GM
			case SEC_GAMEMASTER:
				msg += "|TInterface\\icons\\Mail_GMIcon:15|t|cff000000[Staff]|cffABD473[GameMaster] ";
				msg += GetNameLink(player);
				msg += " |cff51FF59";
				break;
				// Admin
			case SEC_ADMINISTRATOR:
				msg += "|TInterface\\icons\\Mail_GMIcon:15|t|cff000000[Staff]|cff9B9B9B[Administrator] ";
				msg += GetNameLink(player);
				msg += " |cff1AFF25";
				break;

			}

			msg += args;
			if (FACTION_SPECIFIC)
			{
				SessionMap sessions = sWorld->GetAllSessions();
				for (SessionMap::iterator itr = sessions.begin(); itr != sessions.end(); ++itr)
					if (Player* plr = itr->second->GetPlayer())
						if (plr->GetTeam() == player->GetTeam())
							sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), plr);
			}
			else
				sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);

			return true;

		}
 
		ChatCommand * GetCommands() const
		{
			static ChatCommand HandleWorldChatCommandTable[] =
			{
				{ "world", rbac::RBAC_PERM_COMMAND_CHANNEL, true, &HandleWorldChatCommand, "", NULL },
				{ NULL, 0, false, NULL, "", NULL }
			};
			return HandleWorldChatCommandTable;
		}
};
 
void AddSC_world_chat()
{
        new world_chat();
}