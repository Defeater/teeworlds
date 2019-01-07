/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <base/color.h>
#include <base/math.h>

#include <engine/engine.h>
#include <engine/graphics.h>
#include <engine/storage.h>
#include <engine/textrender.h>
#include <engine/external/json-parser/json.h>
#include <engine/shared/config.h>

#include <generated/protocol.h>
#include <generated/client_data.h>

#include <game/client/components/sounds.h>
#include <game/client/ui.h>
#include <game/client/render.h>
#include <game/client/gameclient.h>
#include <game/client/animstate.h>

#include "binds.h"
#include "countryflags.h"
#include "menus.h"
void CMenus::RenderBlaSettingsGeneral(CUIRect MainView)
{
    CUIRect Label, Button, Functions, Effect, BottomView;
	// cut view
	MainView.HSplitBottom(80.0f, &MainView, &BottomView);
	BottomView.HSplitTop(20.f, 0, &BottomView);
	// render game menu backgrounds
	int NumOptions = 8.0f;
	float ButtonHeight = 20.0f;
	float Spacing = 2.0f;
	float BackgroundHeight = (float)(NumOptions+1)*ButtonHeight+(float)NumOptions*Spacing;
	MainView.HSplitTop(20.0f, 0, &MainView);
	MainView.HSplitTop(BackgroundHeight, &Functions, &MainView);
	RenderTools()->DrawUIRect(&Functions, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_ALL, 5.0f);

	MainView.HSplitTop(10.0f, 0, &MainView);
	MainView.HSplitTop(BackgroundHeight, &Effect, &MainView);
	RenderTools()->DrawUIRect(&Effect, vec4(0.0f, 0.0f, 0.0f, 0.25f), CUI::CORNER_ALL, 5.0f);
	// render game menu
	Functions.HSplitTop(ButtonHeight, &Label, &Functions);
	Label.y += 2.0f;
	UI()->DoLabel(&Label, Localize("Functions"), ButtonHeight*ms_FontmodHeight*0.8f, CUI::ALIGN_CENTER);
    Functions.HSplitTop(Spacing, 0, &Functions);
	Functions.HSplitTop(ButtonHeight, &Button, &Functions);
	static CButtonContainer s_Bdadash;
	if(DoButton_CheckBox(&s_Bdadash, Localize("Bdadash feature (Pew Pew!)"), g_Config.m_Bdadash, &Button))
		g_Config.m_Bdadash ^= 1;
	Functions.HSplitTop(Spacing, 0, &Functions);
	Functions.HSplitTop(ButtonHeight, &Button, &Functions);

	// render effect menu
	Effect.HSplitTop(ButtonHeight, &Label, &Effect);
	Label.y += 2.0f;
	UI()->DoLabel(&Label, Localize("Effects"), ButtonHeight*ms_FontmodHeight*0.8f, CUI::ALIGN_CENTER);
	Effect.HSplitTop(Spacing, 0, &Effect);
	Effect.HSplitTop(ButtonHeight, &Button, &Effect);
	static CButtonContainer s_Blood;
	if(DoButton_CheckBox(&s_Blood, Localize("Bloodmod"), g_Config.m_Blood, &Button))
		g_Config.m_Blood ^= 1;
	if(g_Config.m_Blood)
	{
        Effect.HSplitTop(Spacing, 0, &Effect);
        Effect.HSplitTop(ButtonHeight, &Button, &Effect);
        static CButtonContainer s_BloodDamage;
        if(DoButton_CheckBox(&s_BloodDamage, Localize("Damage blood"), g_Config.m_BloodDamage, &Button))
            g_Config.m_BloodDamage ^= 1;
	}
	MainView.HSplitTop(10.0f, 0, &MainView);
}
 void CMenus::RenderBlaSettingsExtras(CUIRect MainView)
{

}

void CMenus::RenderBlaSettingsHud(CUIRect MainView)
{
}
void CMenus::RenderBlaSettingsDummy(CUIRect MainView)
{
}
void CMenus::RenderBlaSettingsTexture(CUIRect MainView)
{

}
void CMenus::RenderBlaSettingsInfo(CUIRect MainView)
{

}
void CMenus::RenderBla(CUIRect MainView)
{
	// handle which page should be rendered
	if(g_Config.m_UiSettingsPage == BLA_SETTINGS_GENERAL)
		RenderBlaSettingsGeneral(MainView);
	else if(g_Config.m_UiSettingsPage == BLA_SETTINGS_EXTRAS)
		RenderBlaSettingsExtras(MainView);
	else if(g_Config.m_UiSettingsPage == BLA_SETTINGS_HUD)
		RenderBlaSettingsHud(MainView);
	else if(g_Config.m_UiSettingsPage == BLA_SETTINGS_DUMMY)
		RenderBlaSettingsDummy(MainView);
	else if(g_Config.m_UiSettingsPage == BLA_SETTINGS_TEXTURE)
		RenderBlaSettingsTexture(MainView);
	else if(g_Config.m_UiSettingsPage == BLA_SETTINGS_INFO)
		RenderBlaSettingsInfo(MainView);
	MainView.HSplitBottom(60.0f, 0, &MainView);
	RenderBackButton(MainView);
}
