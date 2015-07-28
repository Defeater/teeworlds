/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_WALL_H
#define GAME_SERVER_ENTITIES_WALL_H
#include <game/server/entity.h>

class CWall : public CEntity
{
	int m_IDEnd;
	vec2 m_From;
	int m_Owner;
	int m_SpawnTick;
	bool m_Active;
	int FindCharacters(vec2 Pos0, vec2 Pos1, float Radius, CCharacter **pChars, int Max);

public:
	CWall(CGameWorld *pGameWorld, vec2 Pos1, vec2 Pos2, int Owner);

	virtual void Tick();
	virtual void Snap(int SnappingClient);
	virtual void Reset();

protected:
	void HitCharacter(vec2 From, vec2 To);
};

#endif
