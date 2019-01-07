/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/demo.h>
#include <engine/graphics.h>
#include <engine/textrender.h>
#include <engine/shared/config.h>
#include <generated/protocol.h>
#include <generated/client_data.h>

#include <game/gamecore.h> // get_angle
#include <game/client/ui.h>
#include <game/client/render.h>
#include "bdadash.h"

CBdadash::CBdadash()
{
	m_NumItems = 0;
}

CBdadash::CItem *CBdadash::CreateI()
{
	if (m_NumItems < MAX_ITEMS)
	{
		CItem *p = &m_aItems[m_NumItems];
		m_NumItems++;
		return p;
	}
	return 0;
}

void CBdadash::DestroyI(CBdadash::CItem *i)
{
	m_NumItems--;
	*i = m_aItems[m_NumItems];
}

bool CBdadash::SearchType(int Type)
{
	for(int i=0; i<m_NumItems; i++)
	{
		if(m_aItems[i].m_Type == Type)
			return true;
	}
	return false;
}

void CBdadash::Create(vec2 Pos, int Type)
{
	if(!g_Config.m_Bdadash)
	return;

    CItem *i = CreateI();
	if (i)
	{
		i->m_StartPos = vec2(Pos.x, Pos.y - 50);
		i->m_EndPos = vec2(Pos.x + rand()%80-40, Pos.y - 80);
		i->m_StartTime = Client()->LocalTime();
		i->m_Speed = S_FAST;
		i->m_Size = Z_SMAL;

			switch(Type)
			{
			case SOUND_GUN_FIRE:
				if(SearchType(SOUND_GUN_FIRE))
				{
					str_copy(i->m_Text, "Ta", sizeof(i->m_Text));
				}
				else
				{
					str_copy(i->m_Text, "Ra", sizeof(i->m_Text));
					i->m_Size = Z_LARG;
				}
				break;
			case SOUND_SHOTGUN_FIRE:
				if(rand()%2==0)
					str_copy(i->m_Text, "Bang", sizeof(i->m_Text));
				else
					str_copy(i->m_Text, "Blam", sizeof(i->m_Text));
				break;
			case SOUND_GRENADE_FIRE:
				str_copy(i->m_Text, "Poom", sizeof(i->m_Text));
				break;
			case SOUND_GRENADE_EXPLODE:
				str_copy(i->m_Text, "BOOM", sizeof(i->m_Text));
				i->m_Speed = S_SLOW;
				i->m_Size = Z_LARG;
				break;
			case SOUND_HAMMER_FIRE:
				str_copy(i->m_Text, "Hop", sizeof(i->m_Text));
				break;
			case SOUND_HAMMER_HIT:
				str_copy(i->m_Text, "Hit", sizeof(i->m_Text));
				i->m_Size = Z_MID;
				break;
			case SOUND_NINJA_FIRE:
				str_copy(i->m_Text, "KYaaaw", sizeof(i->m_Text));
				i->m_Size = Z_MID;
				break;
			case SOUND_PICKUP_NINJA:
				str_copy(i->m_Text, "KYaaaw", sizeof(i->m_Text));
				i->m_Speed = S_SLOW;
				i->m_Size = Z_LARG;
				break;
			case SOUND_NINJA_HIT:
				str_copy(i->m_Text, "SLash", sizeof(i->m_Text));
				i->m_Size = Z_LARG;
				break;
			case SOUND_LASER_FIRE:
				str_copy(i->m_Text, "Phew", sizeof(i->m_Text));
				break;
			case SOUND_LASER_BOUNCE:
				str_copy(i->m_Text, "Zap", sizeof(i->m_Text));
				break;
			case SOUND_WEAPON_SWITCH:
				str_copy(i->m_Text, "Wosh", sizeof(i->m_Text));
				break;
			case SOUND_PLAYER_PAIN_SHORT:
				if(rand()%2==0)
					str_copy(i->m_Text, "Aaa", sizeof(i->m_Text));
				else
					str_copy(i->m_Text, "Ouch", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_MID;
				break;
			case SOUND_PLAYER_PAIN_LONG:
				str_copy(i->m_Text, "AaAaa", sizeof(i->m_Text));
				i->m_Speed = S_SLOW;
				i->m_Size = Z_LARG;
				break;
			case SOUND_PLAYER_DIE:
				if(rand()%2==0)
					str_copy(i->m_Text, "Died", sizeof(i->m_Text));
				else
					str_copy(i->m_Text, "Crack", sizeof(i->m_Text));
				i->m_Speed = S_SLOW;
				i->m_Size = Z_LARG;
				break;
			case SOUND_PLAYER_SPAWN:
				str_copy(i->m_Text, "Yey!", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_LARG;
				break;
			case SOUND_PLAYER_SKID:
				str_copy(i->m_Text, "Shh", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_MID;
				break;
			case SOUND_PICKUP_HEALTH:
				str_copy(i->m_Text, "Whop", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_MID;
				break;
			case SOUND_WEAPON_NOAMMO:
				str_copy(i->m_Text, "Click", sizeof(i->m_Text));
				break;
			case SOUND_PICKUP_ARMOR:
				str_copy(i->m_Text, "Trick", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_MID;
				break;
			case SOUND_PICKUP_GRENADE:
			case SOUND_PICKUP_SHOTGUN:
				str_copy(i->m_Text, "Pick", sizeof(i->m_Text));
				i->m_Speed = S_MID;
				i->m_Size = Z_MID;
				break;
			case SOUND_WEAPON_SPAWN:
				str_copy(i->m_Text, "Whop", sizeof(i->m_Text));
				i->m_Speed = S_SLOW;

				i->m_Size = Z_MID;
				break;
			default:
				DestroyI(i);
				return;
			}

		i->m_Type = Type;
	}
}

void CBdadash::OnRender()
{
	static float s_LastLocalTime = Client()->LocalTime();
	for(int i = 0; i < m_NumItems;)
	{
		//if(i >= MAX_ITEMS)
		//	break;
		if(Client()->State() == IClient::STATE_DEMOPLAYBACK)
		{
			const IDemoPlayer::CInfo *pInfo = DemoPlayer()->BaseInfo();
			if(pInfo->m_Paused)
				m_aItems[i].m_StartTime += Client()->LocalTime()-s_LastLocalTime;
			else
				m_aItems[i].m_StartTime += (Client()->LocalTime()-s_LastLocalTime)*(1.0f-pInfo->m_Speed);
		}
		else
		{
			if(m_pClient->m_Snap.m_pGameData && m_pClient->m_Snap.m_pGameData->m_GameStateFlags&GAMESTATEFLAG_PAUSED)
				m_aItems[i].m_StartTime += Client()->LocalTime()-s_LastLocalTime;
		}

		float Speed;
		switch (m_aItems[i].m_Speed)
		{
		case S_SLOW:
			Speed = 0.75f;
			break;
		case S_MID:
			Speed = 0.50f;
			break;
		case S_FAST:
			Speed = 0.25f;
			break;
		default:
			Speed = 0.50f;
			break;
		}

		float Size;
		switch (m_aItems[i].m_Size)
		{
		case Z_SMAL:
			Size = 18.0f;
			break;
		case Z_MID:
			Size = 22.0f;
			break;
		case Z_LARG:
			Size = 26.0f;
			break;
		default:
			Size = 22.0f;
			break;
		}

		float Life = Speed - (Client()->LocalTime() - m_aItems[i].m_StartTime);
		if(Life < 0.0f)
			DestroyI(&m_aItems[i]);
		else
		{
			TextRender()->TextOutlineColor(0.0f, 0.0f, 0.0f, 0.5f*Life/0.1f);
			TextRender()->TextColor(1.0f, 1.0f, 1.0f, Life/0.1f);
			TextRender()->Text(0, m_aItems[i].m_StartPos.x, m_aItems[i].m_StartPos.y, Size, m_aItems[i].m_Text, -1);
			TextRender()->TextColor(1,1,1,1);
			TextRender()->TextOutlineColor(0.0f, 0.0f, 0.0f, 0.3f);
			if(m_aItems[i].m_StartPos.y > m_aItems[i].m_EndPos.y)
				m_aItems[i].m_StartPos.y--;
			if(m_aItems[i].m_StartPos.x > m_aItems[i].m_EndPos.x)
				m_aItems[i].m_StartPos.x--;
			if(m_aItems[i].m_StartPos.x < m_aItems[i].m_EndPos.x)
				m_aItems[i].m_StartPos.x++;
			i++;
		}
	}
	s_LastLocalTime = Client()->LocalTime();
}

