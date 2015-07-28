/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <game/server/gamecontext.h>
#include <game/server/entity.h>
#include "projectile.h"
#include "airstrike.h"

void CAirstrike::CreateAirstrike(CGameWorld *pWorld, vec2 Pos, int From)
{
	const int Num = 15;
	const int Dist = 100;
	vec2 DropPos(Pos.x - Num*Dist, 0);

	for(int i = 0; i < Num*2; i++)
	{
		new CProjectile(pWorld, WEAPON_GRENADE, From, DropPos, vec2(0, 1),
				pWorld->Server()->TickSpeed()*pWorld->GameServer()->Tuning()->m_GrenadeLifetime,
				1, true, 0, SOUND_GRENADE_EXPLODE, WEAPON_GRENADE);
		DropPos.x += Dist;
	}
}
