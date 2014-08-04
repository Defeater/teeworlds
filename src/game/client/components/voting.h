/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_CLIENT_COMPONENTS_VOTING_H
#define GAME_CLIENT_COMPONENTS_VOTING_H

#include <engine/shared/memheap.h>

#include <game/voting.h>
#include <game/client/component.h>
#include <game/client/ui.h>

class CVoting : public CComponent
{
	CHeap m_Heap;
	
    int m_LastVote;
    int m_State; 

	static void ConVote(IConsole::IResult *pResult, void *pUserData);

	int64 m_Closetime;
	char m_aDescription[VOTE_DESC_LENGTH];
	char m_aReason[VOTE_REASON_LENGTH];
	int m_Voted;
	int m_Yes, m_No, m_Pass, m_Total;
	int m_CallvoteBlockTick;

	void ClearOptions();
	void Callvote(const char *pType, const char *pValue, const char *pReason, bool ForceVote);

public:
	
enum {
        STATE_NORMAL=0,
        STATE_SMALL
     };
    
    int m_NumVoteOptions;
	CVoteOptionClient *m_pFirst;
	CVoteOptionClient *m_pLast;

	CVoteOptionClient *m_pRecycleFirst;
	CVoteOptionClient *m_pRecycleLast;

	CVoting();
	virtual void OnReset();
	virtual void OnConsoleInit();
	virtual void OnMessage(int Msgtype, void *pRawMsg);
	virtual void OnRender();

	void RenderBars(CUIRect Bars, bool Text);

	void CallvoteSpectate(int ClientID, const char *pReason, bool ForceVote = false);
	void CallvoteKick(int ClientID, const char *pReason, bool ForceVote = false);
	void CallvoteOption(int OptionID, const char *pReason, bool ForceVote = false);
	void AddOption(const char *pDescription);
	void RemovevoteOption(int OptionID);
	void AddvoteOption(const char *pDescription, const char *pCommand);

	void Vote(int v); // -1 = no, 1 = yes

	int SecondsLeft() { return (m_Closetime - time_get())/time_freq(); }
	bool IsVoting() { return m_Closetime != 0; }
	int TakenChoice() const { return m_Voted; }
	const char *VoteDescription() const { return m_aDescription; }
	const char *VoteReason() const { return m_aReason; }
	int CallvoteBlockTime() const { return m_CallvoteBlockTick > Client()->GameTick() ? (m_CallvoteBlockTick-Client()->GameTick())/Client()->GameTickSpeed() : 0; }
    float m_offSetX;
    int GetLastVote() const { return m_LastVote; }
    void SetState(int state) { m_State = state; }
    int GetState() const { return m_State; }

    int GetNumVotes(int type) const { if (type==1) { return m_Yes; } else if (type==2) { return m_No; } else { return m_Pass; } }

};

#endif
