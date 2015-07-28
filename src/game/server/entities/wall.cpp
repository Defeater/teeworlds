/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <base/tl/base.h>
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <engine/shared/config.h>
#include "character.h"
#include "wall.h"

CWall::CWall(CGameWorld *pGameWorld, vec2 Pos1, vec2 Pos2, int Owner)
: CEntity(pGameWorld, NETOBJTYPE_LASER)
{
	m_From = Pos1;
	m_Pos = Pos2;
	m_Owner = Owner;
	m_IDEnd = Server()->SnapNewID();
	GameWorld()->InsertEntity(this);
	m_SpawnTick = Server()->Tick();

	if(g_Config.m_SvWallDelay == 0)
		m_Active = true;
}

void CWall::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
	if(GameServer()->GetPlayerChar(m_Owner))
		GameServer()->GetPlayerChar(m_Owner)->m_pWall = 0;
}

int CWall::FindCharacters(vec2 Pos0, vec2 Pos1, float Radius, CCharacter **ppChars, int Max)
{        
	int Num = 0;

	CCharacter *pCh = (CCharacter *)GameWorld()->FindFirst(CGameWorld::ENTTYPE_CHARACTER);
	for(; pCh; pCh = (CCharacter *)pCh->TypeNext())
	{
		vec2 IntersectPos = Pos0;
		if(!equals(Pos0, Pos1))
			IntersectPos = closest_point_on_line(Pos0, Pos1, pCh->m_Pos);
		float Len = distance(pCh->m_Pos, IntersectPos);
		if(Len < pCh->m_ProximityRadius+Radius)
		{
			if(ppChars)
				ppChars[Num] = pCh;
			Num++;
			if(Num == Max)
				break;
		}
	}

	return Num;
}

void CWall::HitCharacter(vec2 From, vec2 To)
{	 
    CCharacter *apEnts[MAX_CLIENTS];
	int Num = FindCharacters(From, To, 2.5f, apEnts, MAX_CLIENTS);

	for(int i = 0; i < Num; i++)
	{        
    	if(apEnts[i]->GetPlayer()->m_Infected)
			apEnts[i]->Die(m_Owner, WEAPON_WORLD);
	}
}

void CWall::Tick()
{
	if(!m_Active)
	{
		if(Server()->Tick() > m_SpawnTick+Server()->TickSpeed()*g_Config.m_SvWallDelay)
		{
			m_SpawnTick = Server()->Tick();
			m_Active = true;
		}

		return;
	}

	if(Server()->Tick() > m_SpawnTick+Server()->TickSpeed()*g_Config.m_SvWallLife)
	{
		Reset();
		return;
	}

	   HitCharacter(m_From, m_Pos);
}

void CWall::Snap(int SnappingClient)
{
	vec2 StartPos = m_Pos, EndPos = m_From;

	if(NetworkClipped(SnappingClient, StartPos))
	{
		if(NetworkClipped(SnappingClient, EndPos))
			return;
		else
		{
			swap(StartPos, EndPos);
		}
	}


	CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_ID, sizeof(CNetObj_Laser)));
	CNetObj_Laser *pEnd = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_IDEnd, sizeof(CNetObj_Laser)));
	if(!pObj || !pEnd)
		return;

	if(m_Active)
	{
		pObj->m_X = (int) StartPos.x;
		pObj->m_Y = (int) StartPos.y;
		pObj->m_FromX = (int) EndPos.x;
		pObj->m_FromY = (int) EndPos.y;
		pObj->m_StartTick = Server()->Tick();
		//
		pEnd->m_FromY = (int) EndPos.y;
		pEnd->m_FromX = (int) EndPos.x;
		pEnd->m_Y = (int) EndPos.y;
		pEnd->m_X = (int) EndPos.x;
		pEnd->m_StartTick = Server()->Tick();
	}
	else
	{
		pObj->m_Y = (int) StartPos.y;
		pObj->m_X = (int) StartPos.x;
		pObj->m_FromY = (int) StartPos.y;
		pObj->m_FromX = (int) StartPos.x;
		pObj->m_StartTick = Server()->Tick();
		//
		pEnd->m_FromY = (int) EndPos.y;
		pEnd->m_FromX = (int) EndPos.x;
		pEnd->m_Y = (int) EndPos.y;
		pEnd->m_X = (int) EndPos.x;
		pEnd->m_StartTick = Server()->Tick();
	}
}
