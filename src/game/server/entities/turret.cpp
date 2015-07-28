/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "turret.h"
#include "laser.h"

CTurret::CTurret(CGameWorld *pGameWorld, vec2 Pos, vec2 Direction, float StartEnergy, int Owner)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_LASER)
{
	m_Pos = Pos;
	m_Owner = Owner;
	m_Energy = StartEnergy;
	m_Dir = Direction;
	m_Bounces = 0;
	m_EvalTick = Server()->Tick(); 
	GameWorld()->InsertEntity(this);
    
    for(int i = 0; i < 7; i++)
	{
		m_IDs[i] = Server()->SnapNewID();
	}
    
}

void CTurret::Reset()
{
	
    for(int i = 0; i < 7; i++)
	{
		Server()->SnapFreeID(m_IDs[i]);
	}
    
    GameServer()->m_World.DestroyEntity(this); 
}

void CTurret::Tick()
{
	CCharacter *OwnerChar = GameServer()->GetPlayerChar(m_Owner);
	if(OwnerChar && !OwnerChar->IsAlive())
	{
		Reset();
		return;
	}

    if(Server()->Tick() < m_EvalTick + Server()->TickSpeed() * 10)
	{
		if(Server()->Tick() < m_ReloadTimer)
			return;

         m_Vel.y += GameWorld()->m_Core.m_Tuning.m_Gravity;
         m_Vel.x*=0.97f;

         if(m_Vel.x < 0.01f && m_Vel.x > -0.01f)
         m_Vel.x = 0;

         GameServer()->Collision()->MoveBox(&m_Pos,&m_Vel, vec2(0, -40.0f), 0.5f);

		CCharacter *pChr = GameServer()->m_World.ClosestCharacter(m_Pos, 16.0f, 0);
		if(pChr && pChr->IsAlive() && pChr->GetPlayer()->GetCID() != m_Owner)
		{
			pChr->TakeDamage(vec2(0.f, 0.f), 15, m_Owner, WEAPON_RIFLE);
			GameServer()->CreateSound(m_Pos, SOUND_RIFLE_FIRE);
			Reset();
		}

		pChr = GameServer()->m_World.ClosestCharacter(m_Pos, 186.0f, 0);
		if(pChr && pChr->IsAlive() && pChr != OwnerChar && pChr->GetLastSpawn() < Server()->Tick() + 3 && pChr->GetPlayer()->m_Infected)
		{
			vec2 Direction = normalize(pChr->m_Pos - m_Pos);
			new CLaser(GameWorld(), m_Pos, Direction, GameServer()->Tuning()->m_LaserReach, m_Owner);
			GameServer()->CreateSound(m_Pos, SOUND_RIFLE_FIRE);

			m_ReloadTimer = Server()->Tick() + 25;
		}
	}
    else
	{
		Reset();
	}
	
	static const int SIZE = 16;
	m_From[0] = m_Pos + vec2(SIZE, -(SIZE*2));
	m_To[0] = m_Pos + vec2(SIZE*2, 0);

	m_From[1] = m_To[0];
	m_To[1] = m_Pos + vec2(SIZE, SIZE*2);

	m_From[2] = m_To[1];
	m_To[2] = m_Pos + vec2(-SIZE, SIZE*2);

	m_From[3] = m_To[2];
	m_To[3] = m_Pos + vec2(-(SIZE*2), 0);

	m_From[4] = m_To[3];
	m_To[4] = m_Pos + vec2(-SIZE, -(SIZE*2));

	m_From[5] = m_To[4];
	m_To[5] = m_Pos + vec2(SIZE, (-SIZE*2)); 
	
}

void CTurret::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;

	for(int i = 0; i < 6; i++)
	{
		CNetObj_Laser *pObj = static_cast<CNetObj_Laser *>(Server()->SnapNewItem(NETOBJTYPE_LASER, m_IDs[i], sizeof(CNetObj_Laser)));
		if(!pObj)
			continue;

		pObj->m_X = (int)m_From[i].x;
		pObj->m_Y = (int)m_From[i].y;
		pObj->m_FromX = (int)m_To[i].x;
		pObj->m_FromY = (int)m_To[i].y;
		pObj->m_StartTick = Server()->Tick()-1;
	}

	CNetObj_Pickup *pP = static_cast<CNetObj_Pickup *>(Server()->SnapNewItem(NETOBJTYPE_PICKUP, m_IDs[6], sizeof(CNetObj_Pickup)));
	pP->m_X = (int)m_Pos.x;
	pP->m_Y = (int)m_Pos.y;
	pP->m_Type = POWERUP_HEALTH;
	pP->m_Subtype = 0;

}
