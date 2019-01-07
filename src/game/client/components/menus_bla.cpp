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
