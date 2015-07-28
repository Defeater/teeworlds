/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_INF_H
#define GAME_SERVER_GAMEMODES_INF_H

#include <game/server/gamecontroller.h>
#include <game/server/entity.h>

class CGameControllerINF : public IGameController
{
	bool m_GameStarted;
	bool m_ZombiesWon;
	bool m_ZombiesLeft;
	bool m_HumansWon;
	IConsole *m_pConsole;
	IConsole *Console() { return m_pConsole; }
public:
	CGameControllerINF(CGameContext *pGameServer);
	virtual void Tick();
	virtual void DoWincheck();
	virtual bool CanSpawn(int Team, vec2 *pPos, int ClientID = -1);
	virtual void OnCharacterSpawn(CCharacter *pChr);
	virtual bool IsFriendlyFire(int ClientID1, int ClientID2);

	virtual int OnCharacterDeath(CCharacter *pVictim, CPlayer *pKiller, int Weapon);

	virtual void OnPlayerInfoChange(CPlayer *pP);
	virtual void StartRound();
	virtual void EndRound();

	virtual bool GameStarted();

};

#endif
