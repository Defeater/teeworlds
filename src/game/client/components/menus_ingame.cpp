/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <base/math.h>
#include <stdio.h>

#include <engine/config.h>
#include <engine/demo.h>
#include <engine/friends.h>
#include <engine/graphics.h>
#include <engine/serverbrowser.h>
#include <engine/textrender.h>
#include <engine/shared/config.h>

#include <generated/protocol.h>
#include <generated/client_data.h>

#include <game/client/animstate.h>
#include <game/client/gameclient.h>
#include <game/client/render.h>
#include <game/client/ui.h>

#include "menus.h"
#include "motd.h"
#include "voting.h"

void CMenus::RenderGame(CUIRect MainView)
{
	if(m_pClient->m_LocalClientID == -1)
		return;

	char aBuf[128];
	const char *pNotification = 0;
	int TeamMod = m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team != TEAM_SPECTATORS ? -1 : 0;
	bool AllowSpec = true;
	int TimeLeft = 0;

	if(TeamMod+m_pClient->m_GameInfo.m_aTeamSize[TEAM_RED]+m_pClient->m_GameInfo.m_aTeamSize[TEAM_BLUE] >= m_pClient->m_ServerSettings.m_PlayerSlots)
	{
		str_format(aBuf, sizeof(aBuf), Localize("Only %d active players are allowed"), m_pClient->m_ServerSettings.m_PlayerSlots);
		pNotification = aBuf;
	}
	else if(m_pClient->m_ServerSettings.m_TeamLock)
		pNotification = Localize("Teams are locked");
	else if(m_pClient->m_TeamCooldownTick+1 >= Client()->GameTick())
	{
		TimeLeft = (m_pClient->m_TeamCooldownTick-Client()->GameTick())/Client()->GameTickSpeed()+1;
		str_format(aBuf, sizeof(aBuf), Localize("Teams are locked. Time to wait before changing team: %02d:%02d"), TimeLeft/60, TimeLeft%60);
		pNotification = aBuf;
		AllowSpec = false;
	}

	CUIRect Button, ButtonBar;
	MainView.HSplitTop(45.0f, &ButtonBar, &MainView);
	RenderTools()->DrawUIRect(&ButtonBar, vec4(0.0f, 0.0f, 0.0f, 0.25f), pNotification!=0?CUI::CORNER_T:CUI::CORNER_ALL, 10.0f);

	// button bar
	ButtonBar.HSplitTop(10.0f, 0, &ButtonBar);
	ButtonBar.HSplitTop(25.0f, &ButtonBar, 0);
	ButtonBar.VMargin(10.0f, &ButtonBar);

	ButtonBar.VSplitRight(150.0f, &ButtonBar, &Button);
	static CButtonContainer s_DisconnectButton;
	if(DoButton_MenuTabTop(&s_DisconnectButton, Localize("Disconnect"), 0, &Button))
		Client()->Disconnect();

	if(m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team != TEAM_SPECTATORS && AllowSpec)
	{
		ButtonBar.VSplitLeft(10.0f, 0, &ButtonBar);
		ButtonBar.VSplitLeft(120.0f, &Button, &ButtonBar);
		static CButtonContainer s_SpectateButton;
		if(DoButton_MenuTabTop(&s_SpectateButton, Localize("Spectate"), 0, &Button))
		{
			m_pClient->SendSwitchTeam(TEAM_SPECTATORS);
			SetActive(false);
		}
    }

	if(pNotification != 0)
	{
		// print notice
		CUIRect Bar;
		MainView.HSplitTop(45.0f, &Bar, &MainView);
		RenderTools()->DrawUIRect(&Bar, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_B, 10.0f);
		Bar.HMargin(15.0f, &Bar);
		UI()->DoLabelScaled(&Bar, pNotification, 14.0f, CUI::ALIGN_CENTER);
	}
	else
	{
		if(m_pClient->m_GameInfo.m_GameFlags&GAMEFLAG_TEAMS)
		{
			if(m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team != TEAM_RED &&
				absolute((m_pClient->m_GameInfo.m_aTeamSize[TEAM_RED]+1)-(m_pClient->m_GameInfo.m_aTeamSize[TEAM_BLUE]+TeamMod)) < NUM_TEAMS)
			{
				ButtonBar.VSplitLeft(10.0f, 0, &ButtonBar);
				ButtonBar.VSplitLeft(120.0f, &Button, &ButtonBar);
				static CButtonContainer s_SpectateButton;
				if(DoButton_MenuTabTop(&s_SpectateButton, Localize("^rRed"), 0, &Button))
				{
					m_pClient->SendSwitchTeam(TEAM_RED);
					SetActive(false);
				}
			}
			if(m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team != TEAM_BLUE &&
				absolute((m_pClient->m_GameInfo.m_aTeamSize[TEAM_RED]+TeamMod)-(m_pClient->m_GameInfo.m_aTeamSize[TEAM_BLUE]+1)) < NUM_TEAMS)
			{
			    ButtonBar.VSplitLeft(10.0f, 0, &ButtonBar);
				ButtonBar.VSplitLeft(120.0f, &Button, &ButtonBar);
				static CButtonContainer s_SpectateButton;
				if(DoButton_MenuTabTop(&s_SpectateButton, Localize("^bBlue"), 0, &Button))
				{
					m_pClient->SendSwitchTeam(TEAM_BLUE);
					SetActive(false);
				}
			}
		}
		else
		{
            if(m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team != 0)
            {
                ButtonBar.VSplitLeft(10.0f, 0, &ButtonBar);
                ButtonBar.VSplitLeft(100.0f, &Button, &ButtonBar);
                static CButtonContainer s_SpectateButton;
                if(DoButton_MenuTabTop(&s_SpectateButton, Localize("Join"), 0, &Button))
                {
                    m_pClient->SendSwitchTeam(0);
                    SetActive(false);
                }
            }
        }
	}

	// Record button
	ButtonBar.VSplitRight(50.0f, &ButtonBar, 0);
	ButtonBar.VSplitRight(120.0f, &ButtonBar, &Button);
    static CButtonContainer s_TestButton;
	if(DoButton_MenuTabTop(&s_TestButton, Localize("LAN Test"), 0, &Button))
	{
		TestMap();
		Client()->Connect("127.0.0.1:8303");
		Client()->SendInitialRconPassword("default");
	}
	ButtonBar.VSplitRight(50.0f, &ButtonBar, 0);
	ButtonBar.VSplitRight(120.0f, &ButtonBar, &Button);

	static CButtonContainer s_DemoButton;
	bool Recording = DemoRecorder()->IsRecording();
	if(DoButton_MenuTabTop(&s_DemoButton, Localize(Recording ? "Stop" : "Record"), 0, &Button))
	{
		if(!Recording)
			Client()->DemoRecorder_Start("demo", true);
		else
			Client()->DemoRecorder_Stop();
	}
}

void CMenus::RenderPlayers(CUIRect MainView)
{
	CUIRect Button, ButtonBar, Options, Player;
	RenderTools()->DrawUIRect(&MainView, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_ALL, 10.0f);

	// player options
	MainView.Margin(10.0f, &Options);
	RenderTools()->DrawUIRect(&Options, vec4(1.0f, 1.0f, 1.0f, 0.25f), CUI::CORNER_ALL, 10.0f);
	Options.Margin(10.0f, &Options);
	Options.HSplitTop(50.0f, &Button, &Options);
	UI()->DoLabelScaled(&Button, Localize("Player options"), 34.0f, CUI::ALIGN_LEFT);

	// headline
	Options.HSplitTop(34.0f, &ButtonBar, &Options);
	ButtonBar.VSplitRight(220.0f, &Player, &ButtonBar);
	UI()->DoLabelScaled(&Player, Localize("Player"), 24.0f, CUI::ALIGN_LEFT);

	ButtonBar.HMargin(1.0f, &ButtonBar);
	float Width = ButtonBar.h*2.0f;
	ButtonBar.VSplitLeft(Width, &Button, &ButtonBar);
	Graphics()->TextureSet(g_pData->m_aImages[IMAGE_GUIICONS].m_Id);
	Graphics()->QuadsBegin();
	RenderTools()->SelectSprite(SPRITE_GUIICON_MUTE);
	IGraphics::CQuadItem QuadItem(Button.x, Button.y, Button.w, Button.h);
	Graphics()->QuadsDrawTL(&QuadItem, 1);
	Graphics()->QuadsEnd();

	ButtonBar.VSplitLeft(20.0f, 0, &ButtonBar);
	ButtonBar.VSplitLeft(Width, &Button, &ButtonBar);
	Graphics()->TextureSet(g_pData->m_aImages[IMAGE_GUIICONS].m_Id);
	Graphics()->QuadsBegin();
	RenderTools()->SelectSprite(SPRITE_GUIICON_FRIEND);
	QuadItem = IGraphics::CQuadItem(Button.x, Button.y, Button.w, Button.h);
	Graphics()->QuadsDrawTL(&QuadItem, 1);
	Graphics()->QuadsEnd();

	// options
	static int s_aPlayerIDs[MAX_CLIENTS][2] = {{0}};
	int Teams[3] = { TEAM_RED, TEAM_BLUE, TEAM_SPECTATORS };
	for(int Team = 0; Team < 3; ++Team)
	{
		for(int i = 0, Count = 0; i < MAX_CLIENTS; ++i)
		{
			if(i == m_pClient->m_LocalClientID || !m_pClient->m_aClients[i].m_Active || m_pClient->m_aClients[i].m_Team != Teams[Team])
				continue;

			Options.HSplitTop(28.0f, &ButtonBar, &Options);
			if(Count++%2 == 0)
				RenderTools()->DrawUIRect(&ButtonBar, vec4(1.0f, 1.0f, 1.0f, 0.25f), CUI::CORNER_ALL, 10.0f);
			ButtonBar.VSplitRight(220.0f, &Player, &ButtonBar);

			// player info
			Player.VSplitLeft(28.0f, &Button, &Player);
			CTeeRenderInfo Info = m_pClient->m_aClients[i].m_RenderInfo;
			Info.m_Size = Button.h;
			RenderTools()->RenderTee(CAnimState::GetIdle(), &Info, EMOTE_NORMAL, vec2(1.0f, 0.0f), vec2(Button.x+Button.h/2, Button.y+Button.h/2));

			Player.HSplitTop(1.5f, 0, &Player);
			Player.VSplitMid(&Player, &Button);
			CTextCursor Cursor;
			TextRender()->SetCursor(&Cursor, Player.x, Player.y, 14.0f, TEXTFLAG_RENDER|TEXTFLAG_STOP_AT_END);
			Cursor.m_LineWidth = Player.w;
			char aBuf[64];
			str_format(aBuf, sizeof(aBuf), "%2d: %s", i, g_Config.m_ClShowsocial ? m_pClient->m_aClients[i].m_aName : "");
			TextRender()->TextEx(&Cursor, aBuf, -1);

			TextRender()->SetCursor(&Cursor, Button.x,Button.y, 14.0f, TEXTFLAG_RENDER|TEXTFLAG_STOP_AT_END);
			Cursor.m_LineWidth = Button.w;
			TextRender()->TextEx(&Cursor, m_pClient->m_aClients[i].m_aClan, -1);

			// ignore button
			ButtonBar.HMargin(2.0f, &ButtonBar);
			ButtonBar.VSplitLeft(Width, &Button, &ButtonBar);
			Button.VSplitLeft((Width-Button.h)/4.0f, 0, &Button);
			Button.VSplitLeft(Button.h, &Button, 0);
			if(g_Config.m_ClShowChatFriends && !m_pClient->m_aClients[i].m_Friend)
				DoButton_Toggle(&s_aPlayerIDs[i][0], 1, &Button, false);
			else
				if(DoButton_Toggle(&s_aPlayerIDs[i][0], m_pClient->m_aClients[i].m_ChatIgnore, &Button, true))
					m_pClient->m_aClients[i].m_ChatIgnore ^= 1;

			// friend button
			ButtonBar.VSplitLeft(20.0f, &Button, &ButtonBar);
			ButtonBar.VSplitLeft(Width, &Button, &ButtonBar);
			Button.VSplitLeft((Width-Button.h)/4.0f, 0, &Button);
			Button.VSplitLeft(Button.h, &Button, 0);
			if(DoButton_Toggle(&s_aPlayerIDs[i][1], m_pClient->m_aClients[i].m_Friend, &Button, true))
			{
				if(m_pClient->m_aClients[i].m_Friend)
					m_pClient->Friends()->RemoveFriend(m_pClient->m_aClients[i].m_aName, m_pClient->m_aClients[i].m_aClan);
				else
					m_pClient->Friends()->AddFriend(m_pClient->m_aClients[i].m_aName, m_pClient->m_aClients[i].m_aClan);

				m_pClient->m_aClients[i].m_Friend ^= 1;
			}
		}
	}
}

void CMenus::RenderServerInfo(CUIRect MainView)
{
	if(!m_pClient->m_Snap.m_pLocalInfo)
		return;

	// fetch server info
	CServerInfo CurrentServerInfo;
	Client()->GetServerInfo(&CurrentServerInfo);

	// render background
	RenderTools()->DrawUIRect(&MainView, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_ALL, 10.0f);

	CUIRect View, ServerInfo, GameInfo, Motd;

	float x = 0.0f;
	float y = 0.0f;

	char aBuf[1024];

	// set view to use for all sub-modules
	MainView.Margin(10.0f, &View);

	// serverinfo
	View.HSplitTop(View.h/2/UI()->Scale()-5.0f, &ServerInfo, &Motd);
	ServerInfo.VSplitLeft(View.w/2/UI()->Scale()-5.0f, &ServerInfo, &GameInfo);
	RenderTools()->DrawUIRect(&ServerInfo, vec4(1,1,1,0.25f), CUI::CORNER_ALL, 10.0f);

	ServerInfo.Margin(5.0f, &ServerInfo);

	x = 5.0f;
	y = 0.0f;

	TextRender()->Text(0, ServerInfo.x+x, ServerInfo.y+y, 32, Localize("Server info"), 250);
	y += 32.0f+5.0f;

	mem_zero(aBuf, sizeof(aBuf));
	str_format(
		aBuf,
		sizeof(aBuf),
		"%s\n\n"
		"%s: %s\n"
		"%s: %d\n"
		"%s: %s\n"
		"%s: %s\n",
		CurrentServerInfo.m_aName,
		Localize("Address"), g_Config.m_UiServerAddress,
		Localize("Ping"), m_pClient->m_Snap.m_pLocalInfo->m_Latency,
		Localize("Version"), CurrentServerInfo.m_aVersion,
		Localize("Password"), CurrentServerInfo.m_Flags&IServerBrowser::FLAG_PASSWORD ? Localize("Yes") : Localize("No")
	);

	TextRender()->Text(0, ServerInfo.x+x, ServerInfo.y+y, 20, aBuf, 250);

	{
		CUIRect Button;
		bool IsFavorite = ServerBrowser()->IsFavorite(CurrentServerInfo.m_NetAddr);
		ServerInfo.HSplitBottom(20.0f, &ServerInfo, &Button);
		static int s_AddFavButton = 0;
		if(DoButton_CheckBox(&s_AddFavButton, Localize("Favorite"), IsFavorite, &Button))
		{
			if(IsFavorite)
				ServerBrowser()->RemoveFavorite(&CurrentServerInfo);
			else
				ServerBrowser()->AddFavorite(&CurrentServerInfo);
		}
	}

	// gameinfo
	GameInfo.VSplitLeft(10.0f, 0x0, &GameInfo);
	RenderTools()->DrawUIRect(&GameInfo, vec4(1,1,1,0.25f), CUI::CORNER_ALL, 10.0f);

	GameInfo.Margin(5.0f, &GameInfo);

	x = 5.0f;
	y = 0.0f;

	TextRender()->Text(0, GameInfo.x+x, GameInfo.y+y, 32, Localize("Game info"), 250);
	y += 32.0f+5.0f;

	mem_zero(aBuf, sizeof(aBuf));
	str_format(
		aBuf,
		sizeof(aBuf),
		"\n\n"
		"%s: %s\n"
		"%s: %s\n"
		"%s: %d\n"
		"%s: %d\n"
		"\n"
		"%s: %d/%d\n",
		Localize("Game type"), CurrentServerInfo.m_aGameType,
		Localize("Map"), CurrentServerInfo.m_aMap,
		Localize("Score limit"), m_pClient->m_GameInfo.m_ScoreLimit,
		Localize("Time limit"), m_pClient->m_GameInfo.m_TimeLimit,
		Localize("Players"), m_pClient->m_GameInfo.m_NumPlayers, CurrentServerInfo.m_MaxClients
	);
	TextRender()->Text(0, GameInfo.x+x, GameInfo.y+y, 20, aBuf, 250);

	// motd
	Motd.HSplitTop(10.0f, 0, &Motd);
	RenderTools()->DrawUIRect(&Motd, vec4(1,1,1,0.25f), CUI::CORNER_ALL, 10.0f);
	Motd.Margin(5.0f, &Motd);
	y = 0.0f;
	x = 5.0f;
	TextRender()->Text(0, Motd.x+x, Motd.y+y, 32, Localize("MOTD"), -1);
	y += 32.0f+5.0f;
	TextRender()->Text(0, Motd.x+x, Motd.y+y, 16, m_pClient->m_pMotd->m_aServerMotd, (int)Motd.w);
}

void CMenus::RenderInGameServerBrowser(CUIRect MainView)
{
	static int s_ControlPage = 0;
	// render background
	CUIRect Bottom, TabBar, Button;
	MainView.HSplitTop(20.0f, &Bottom, &MainView);
	RenderTools()->DrawUIRect(&Bottom, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_T, 10.0f);
	MainView.HSplitTop(20.0f, &TabBar, &MainView);
	// tab bar
	{
		TabBar.VSplitLeft(TabBar.w/3, &Button, &TabBar);
		static CButtonContainer s_ButtonGlobal;
		if(DoButton_MenuTabTop(&s_ButtonGlobal, Localize("Global"), s_ControlPage == 0, &Button, 0, 0) && s_ControlPage != 0)
		{
			ServerBrowser()->Refresh(IServerBrowser::TYPE_INTERNET);
			s_ControlPage = IServerBrowser::TYPE_INTERNET;
		}
		TabBar.VSplitMid(&Button, &TabBar);
		static CButtonContainer s_ButtonLocal;
		if(DoButton_MenuTabTop(&s_ButtonLocal, Localize("Local"), s_ControlPage == 1, &Button, 0, 0) && s_ControlPage != 1)
		{
			ServerBrowser()->Refresh(IServerBrowser::TYPE_LAN);
			s_ControlPage = IServerBrowser::TYPE_LAN;
		}

		static CButtonContainer s_ButtonRecent;
		if(DoButton_MenuTabTop(&s_ButtonRecent, Localize("Recent"), s_ControlPage == 2, &TabBar, 0, 0) && s_ControlPage != 2)
		{
            //todo:
            //recent server-list
		}
	}
	RenderServerbrowser(MainView);
}

void CMenus::RenderServerControlServer(CUIRect MainView)
{
	static int s_VoteList = 0;
	static float s_ScrollValue = 0;
	CUIRect List = MainView;
	UiDoListboxHeader(&List, "", 20.0f, 2.0f);
	UiDoListboxStart(&s_VoteList, 24.0f, "", m_pClient->m_pVoting->m_NumVoteOptions, 1, m_CallvoteSelectedOption, s_ScrollValue);

	for(CVoteOptionClient *pOption = m_pClient->m_pVoting->m_pFirst; pOption; pOption = pOption->m_pNext)
	{
		CListboxItem Item = UiDoListboxNextItem(pOption);

		if(Item.m_Visible)
			UI()->DoLabelScaled(&Item.m_Rect, pOption->m_aDescription, 16.0f, CUI::ALIGN_LEFT);
	}

	m_CallvoteSelectedOption = UiDoListboxEnd(&s_ScrollValue, 0);
}

void CMenus::RenderServerControlKick(CUIRect MainView, bool FilterSpectators)
{
	int NumOptions = 0;
	int Selected = -1;
	static int aPlayerIDs[MAX_CLIENTS];
	int Teams[3] = { TEAM_RED, TEAM_BLUE, TEAM_SPECTATORS };
	for(int Team = 0; Team < 3; ++Team)
	{
		for(int i = 0; i < MAX_CLIENTS; i++)
		{
			if(i == m_pClient->m_LocalClientID || !m_pClient->m_aClients[i].m_Active || m_pClient->m_aClients[i].m_Team != Teams[Team] ||
				(FilterSpectators && m_pClient->m_aClients[i].m_Team == TEAM_SPECTATORS) ||
				(!FilterSpectators && m_pClient->m_Snap.m_paPlayerInfos[i] && m_pClient->m_Snap.m_paPlayerInfos[i]->m_PlayerFlags&PLAYERFLAG_ADMIN))
				continue;
			if(m_CallvoteSelectedPlayer == i)
				Selected = NumOptions;
			aPlayerIDs[NumOptions++] = i;
		}
	}

	static int s_VoteList = 0;
	static float s_ScrollValue = 0;
	CUIRect List = MainView;
	UiDoListboxHeader(&List, "", 20.0f, 2.0f);
	UiDoListboxStart(&s_VoteList, 24.0f, "", NumOptions, 1, Selected, s_ScrollValue);

	for(int i = 0; i < NumOptions; i++)
	{
		CListboxItem Item = UiDoListboxNextItem(&aPlayerIDs[i]);

		if(Item.m_Visible)
		{
			CTeeRenderInfo Info = m_pClient->m_aClients[aPlayerIDs[i]].m_RenderInfo;
			Info.m_Size = Item.m_Rect.h;
			Item.m_Rect.HSplitTop(5.0f, 0, &Item.m_Rect); // some margin from the top
			RenderTools()->RenderTee(CAnimState::GetIdle(), &Info, EMOTE_NORMAL, vec2(1,0), vec2(Item.m_Rect.x+Item.m_Rect.h/2, Item.m_Rect.y+Item.m_Rect.h/2));
			Item.m_Rect.x +=Info.m_Size;
			char aBuf[64];
			str_format(aBuf, sizeof(aBuf), "%2d: %s", aPlayerIDs[i], g_Config.m_ClShowsocial ? m_pClient->m_aClients[aPlayerIDs[i]].m_aName : "");
			UI()->DoLabelScaled(&Item.m_Rect, aBuf, 16.0f, CUI::ALIGN_LEFT);
		}
	}

	Selected = UiDoListboxEnd(&s_ScrollValue, 0);
	m_CallvoteSelectedPlayer = Selected != -1 ? aPlayerIDs[Selected] : -1;
}

void CMenus::HandleCallvote(int Page, bool Force)
{
	if(Page == 0)
		m_pClient->m_pVoting->CallvoteOption(m_CallvoteSelectedOption, m_aCallvoteReason, Force);
	else if(Page == 1)
	{
		if(m_CallvoteSelectedPlayer >= 0 && m_CallvoteSelectedPlayer < MAX_CLIENTS &&
			m_pClient->m_aClients[m_CallvoteSelectedPlayer].m_Active)
		{
			m_pClient->m_pVoting->CallvoteKick(m_CallvoteSelectedPlayer, m_aCallvoteReason, Force);
			SetActive(false);
		}
	}
	else if(Page == 2)
	{
		if(m_CallvoteSelectedPlayer >= 0 && m_CallvoteSelectedPlayer < MAX_CLIENTS &&
			m_pClient->m_aClients[m_CallvoteSelectedPlayer].m_Active)
		{
			m_pClient->m_pVoting->CallvoteSpectate(m_CallvoteSelectedPlayer, m_aCallvoteReason, Force);
			SetActive(false);
		}
	}
}

void CMenus::RenderServerControl(CUIRect MainView)
{
	if(m_pClient->m_LocalClientID == -1)
		return;

	static int s_ControlPage = 0;
	const char *pNotification = 0;
	char aBuf[64];

	if(m_pClient->m_aClients[m_pClient->m_LocalClientID].m_Team == TEAM_SPECTATORS)
		pNotification = Localize("Spectators aren't allowed to start a vote.");
	else if(m_pClient->m_pVoting->IsVoting())
		pNotification = Localize("Wait for current vote to end before calling a new one.");
	else if(m_pClient->m_pVoting->CallvoteBlockTime() != 0)
	{
		str_format(aBuf, sizeof(aBuf), Localize("You must wait %d seconds before making another vote"), m_pClient->m_pVoting->CallvoteBlockTime());
		pNotification = aBuf;
	}

	bool Authed = Client()->RconAuthed();
	if(pNotification && !Authed)
	{
		// only print notice
		CUIRect Bar;
		MainView.HSplitTop(45.0f, &Bar, &MainView);
		RenderTools()->DrawUIRect(&Bar, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_ALL, 10.0f);
		Bar.HMargin(15.0f, &Bar);
		UI()->DoLabelScaled(&Bar, pNotification, 14.0f, CUI::ALIGN_CENTER);
		return;
	}

	// tab bar
	CUIRect Bottom, Extended, TabBar, Button;
	MainView.HSplitTop(20.0f, &Bottom, &MainView);
	RenderTools()->DrawUIRect(&Bottom, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_T, 10.0f);
	MainView.HSplitTop(20.0f, &TabBar, &MainView);
	{
		TabBar.VSplitLeft(TabBar.w/3, &Button, &TabBar);
		static int s_Button0 = 0;
		if(DoButton_MenuTab(&s_Button0, Localize("Change settings"), s_ControlPage == 0, &Button, 0))
			s_ControlPage = 0;

		TabBar.VSplitMid(&Button, &TabBar);
		static int s_Button1 = 0;
		if(DoButton_MenuTab(&s_Button1, Localize("Kick player"), s_ControlPage == 1, &Button, 0))
			s_ControlPage = 1;

		static int s_Button2 = 0;
		if(DoButton_MenuTab(&s_Button2, Localize("Move player to spectators"), s_ControlPage == 2, &TabBar, 0))
			s_ControlPage = 2;
	}

	if(s_ControlPage == 1)
	{
		if(!m_pClient->m_ServerSettings.m_KickVote)
			pNotification = Localize("Server does not allow voting to kick players");
		else if(m_pClient->m_GameInfo.m_aTeamSize[TEAM_RED]+m_pClient->m_GameInfo.m_aTeamSize[TEAM_BLUE] < m_pClient->m_ServerSettings.m_KickMin)
		{
			str_format(aBuf, sizeof(aBuf), Localize("Kick voting requires %d players on the server"), m_pClient->m_ServerSettings.m_KickMin);
			pNotification = aBuf;
		}
	}
	else if(s_ControlPage == 2 && !m_pClient->m_ServerSettings.m_SpecVote)
		pNotification = Localize("Server does not allow voting to move players to spectators");

	if(pNotification && !Authed)
	{
		// only print notice
		CUIRect Bar;
		MainView.HSplitTop(45.0f, &Bar, &MainView);
		RenderTools()->DrawUIRect(&Bar, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_B, 10.0f);
		Bar.HMargin(15.0f, &Bar);
		UI()->DoLabelScaled(&Bar, pNotification, 14.0f, CUI::ALIGN_CENTER);
		return;
	}

	// render background
	RenderTools()->DrawUIRect(&MainView, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_B, 10.0f);
	MainView.Margin(10.0f, &MainView);
	MainView.HSplitBottom(90.0f, &MainView, &Extended);

	// render page
	MainView.HSplitBottom(ms_ButtonHeight + 5*2, &MainView, &Bottom);
	Bottom.HMargin(5.0f, &Bottom);

	if(s_ControlPage == 0)
		RenderServerControlServer(MainView);
	else if(s_ControlPage == 1)
		RenderServerControlKick(MainView, false);
	else if(s_ControlPage == 2)
		RenderServerControlKick(MainView, true);

	// vote menu
	{
		Bottom.VSplitRight(120.0f, &Bottom, &Button);

		// render kick reason
		CUIRect Reason, ClearButton;
		Bottom.VSplitRight(40.0f, &Bottom, 0);
		Bottom.VSplitRight(160.0f, &Bottom, &Reason);
		Reason.HSplitTop(5.0f, 0, &Reason);
		Reason.VSplitRight(Reason.h, &Reason, &ClearButton);
		const char *pLabel = Localize("Reason:");
		UI()->DoLabelScaled(&Reason, pLabel, 14.0f, CUI::ALIGN_LEFT);
		float w = TextRender()->TextWidth(0, 14.0f, pLabel, -1);
		Reason.VSplitLeft(w+10.0f, 0, &Reason);
		static float s_Offset = 0.0f;
		DoEditBox(&m_aCallvoteReason, &Reason, m_aCallvoteReason, sizeof(m_aCallvoteReason), 14.0f, &s_Offset, false, CUI::CORNER_L);

		// clear button
		{
			static CButtonContainer s_ClearButton;
			float Fade = ButtonFade(&s_ClearButton, 0.6f);
			RenderTools()->DrawUIRect(&ClearButton, vec4(1.0f, 1.0f, 1.0f, 0.33f+(Fade/0.6f)*0.165f), CUI::CORNER_R, 3.0f);
			UI()->DoLabel(&ClearButton, "x", ClearButton.h*ms_FontmodHeight, CUI::ALIGN_CENTER);
			if(UI()->DoButtonLogic(s_ClearButton.GetID(), "x", 0, &ClearButton))
				m_aCallvoteReason[0] = 0;
		}

		if(pNotification == 0)
		{
			// call vote
			static CButtonContainer s_CallVoteButton;
			if(DoButton_Menu(&s_CallVoteButton, Localize("Call vote"), 0, &Button))
				HandleCallvote(s_ControlPage, false);
		}
		else
		{
			// print notice
			UI()->DoLabelScaled(&Bottom, pNotification, 14.0f, CUI::ALIGN_LEFT, Bottom.w);
		}

		// extended features (only available when authed in rcon)
		if(Authed)
		{
			// background
			Extended.Margin(10.0f, &Extended);
			Extended.HSplitTop(20.0f, &Bottom, &Extended);
			Extended.HSplitTop(5.0f, 0, &Extended);

			// force vote
			Bottom.VSplitLeft(5.0f, 0, &Bottom);
			Bottom.VSplitLeft(120.0f, &Button, &Bottom);
			static CButtonContainer s_ForceVoteButton;
			if(DoButton_Menu(&s_ForceVoteButton, Localize("Force vote"), 0, &Button))
				HandleCallvote(s_ControlPage, true);

			if(s_ControlPage == 0)
			{
				// remove vote
				Bottom.VSplitRight(10.0f, &Bottom, 0);
				Bottom.VSplitRight(120.0f, 0, &Button);
				static CButtonContainer s_RemoveVoteButton;
				if(DoButton_Menu(&s_RemoveVoteButton, Localize("Remove"), 0, &Button))
					m_pClient->m_pVoting->RemovevoteOption(m_CallvoteSelectedOption);


				// add vote
				Extended.HSplitTop(20.0f, &Bottom, &Extended);
				Bottom.VSplitLeft(5.0f, 0, &Bottom);
				Bottom.VSplitLeft(250.0f, &Button, &Bottom);
				UI()->DoLabelScaled(&Button, Localize("Vote description:"), 14.0f, CUI::ALIGN_LEFT);

				Bottom.VSplitLeft(20.0f, 0, &Button);
				UI()->DoLabelScaled(&Button, Localize("Vote command:"), 14.0f, CUI::ALIGN_LEFT);

				static char s_aVoteDescription[64] = {0};
				static char s_aVoteCommand[512] = {0};
				Extended.HSplitTop(20.0f, &Bottom, &Extended);
				Bottom.VSplitRight(10.0f, &Bottom, 0);
				Bottom.VSplitRight(120.0f, &Bottom, &Button);
				static CButtonContainer s_AddVoteButton;
				if(DoButton_Menu(&s_AddVoteButton, Localize("Add"), 0, &Button))
					if(s_aVoteDescription[0] != 0 && s_aVoteCommand[0] != 0)
						m_pClient->m_pVoting->AddvoteOption(s_aVoteDescription, s_aVoteCommand);

				Bottom.VSplitLeft(5.0f, 0, &Bottom);
				Bottom.VSplitLeft(250.0f, &Button, &Bottom);
				static float s_OffsetDesc = 0.0f;
				DoEditBox(&s_aVoteDescription, &Button, s_aVoteDescription, sizeof(s_aVoteDescription), 14.0f, &s_OffsetDesc, false, CUI::CORNER_ALL);

				Bottom.VMargin(20.0f, &Button);
				static float s_OffsetCmd = 0.0f;
				DoEditBox(&s_aVoteCommand, &Button, s_aVoteCommand, sizeof(s_aVoteCommand), 14.0f, &s_OffsetCmd, false, CUI::CORNER_ALL);
			}
		}
	}
}

void CMenus::TestMap()
{
#if defined(CONF_FAMILY_WINDOWS)
	FILE *pFile;
	char aServerExe[512], aCfgGametype[512];
	char aBuf[1024];
	int Crc;
	int IsInLocalFolder;
	CServerInfo CurrentServerInfo;
	Client()->GetServerInfo(&CurrentServerInfo);
	char aGametype[64], aMapName[128];
	str_copy(aGametype, CurrentServerInfo.m_aGameType, sizeof(aGametype));
	str_copy(aMapName, CurrentServerInfo.m_aMap, sizeof(aMapName));
	if(!str_comp(aGametype, "DM") || !str_comp(aGametype, "TDM") || !str_comp(aGametype, "CTF"))
	{
		str_copy(aServerExe, "teeworlds_srv.exe", sizeof(aServerExe));
		if(!str_comp(aGametype, "CTF"))
			str_copy(aCfgGametype, "ctf", sizeof(aCfgGametype));
		else str_copy(aCfgGametype, "dm", sizeof(aCfgGametype));
	}
	else // Try with custom binaries
	{
		int i = 0;
		 // Removes weird character and replaces them with whitespaces
		str_sanitize_strong(aGametype);
		// Now let's replace whitespaces with _
		while(aGametype[i])
		{
			if(aGametype[i] == ' ')
				aGametype[i] = '_';
			i++;
		}
		str_format(aServerExe, sizeof(aServerExe), "teeworlds_srv_%s.exe", aGametype);
		str_copy(aCfgGametype, aGametype, sizeof(aCfgGametype));
	}
	/* First, try to open the right .exe */
	str_format(aBuf, sizeof(aBuf), "Trying to open %s", aServerExe);
	Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "servercreation", aBuf);
		pFile = fopen(aServerExe, "r");
		if(!pFile)
		{
			str_copy(aServerExe, "teeworlds_srv.exe", sizeof(aServerExe)); // Finally, use the pure server
			Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "servercreation", "Failed, trying with the pure");
		}
		else
			fclose(pFile);
	pFile = fopen("server/map_test.cfg", "w+");
	if(!pFile)
	{
		system("md server");
		pFile = fopen("server/map_test.cfg", "w+");
		if(!pFile) // Critical error : denying access
			return;
	}
	fprintf(pFile, "sv_name [%s] %s's test server\n", g_Config.m_PlayerClan, g_Config.m_PlayerName);
	fprintf(pFile, "sv_rcon_password default\nsv_gametype %s\nsv_scorelimit 0\nsv_timelimit 0\nsv_infinite_ammo 1\n", aCfgGametype);
	fprintf(pFile, "sv_map %s\nsv_register 1\nsv_port 8303\n", aMapName);
	fclose(pFile);
	// Generating the crc
	Crc = Client()->GetCurrentMapCrc();
	IsInLocalFolder = 0;
	char aOldPath[1024], aNewPath[1024], aAppPath[1024];
	// We must copy the map in the right folder
	str_format(aBuf, sizeof(aBuf), "data/maps/%s.map", aMapName);
	str_copy(aAppPath, ClientUserDirectory(), sizeof(aAppPath));
	pFile = fopen(aBuf, "r");
	if(pFile)
	{
		fclose(pFile);
		IsInLocalFolder = 1;
	}
	else
	{
		str_format(aBuf, sizeof(aBuf), "%s\\maps\\%s.map", aAppPath, aMapName);
		pFile = fopen(aBuf, "r");
		if(pFile)
		{
			fclose(pFile);
			IsInLocalFolder = 2;
		}
	}
	if(IsInLocalFolder == 1)
		str_format(aOldPath, sizeof(aOldPath), "data\\maps\\%s.map", aMapName);
	else if(IsInLocalFolder == 2)
		str_format(aOldPath, sizeof(aOldPath), "%s\\maps\\%s.map", aAppPath, aMapName);
	else
		str_format(aOldPath, sizeof(aOldPath), "%s\\downloadedmaps\\%s_%08x.map", aAppPath, aMapName, Crc);
	str_format(aNewPath, sizeof(aNewPath), "%s\\maps\\%s.map", aAppPath, aMapName);
	str_format(aBuf, sizeof(aBuf), "copy \"%s\" \"%s\"", aOldPath, aNewPath);
	system(aBuf);
	system("taskkill /F /IM teeworlds_srv.exe");
	str_format(aBuf, sizeof(aBuf), "start %s -f server\\map_test.cfg", aServerExe);
	system(aBuf);
#endif
}

