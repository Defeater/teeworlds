/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H
#undef GAME_VARIABLES_H // this file will be included several times


// client
MACRO_CONFIG_INT(ClPredict, cl_predict, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Predict client movements")
MACRO_CONFIG_INT(ClNameplates, cl_nameplates, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show name plates")
MACRO_CONFIG_INT(ClNameplatesAlways, cl_nameplates_always, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Always show name plates disregarding of distance")
MACRO_CONFIG_INT(ClNameplatesTeamcolors, cl_nameplates_teamcolors, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Use team colors for name plates")
MACRO_CONFIG_INT(ClNameplatesSize, cl_nameplates_size, 50, 0, 100, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Size of the name plates from 0 to 100%")
MACRO_CONFIG_INT(ClAutoswitchWeapons, cl_autoswitch_weapons, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Auto switch weapon on pickup")

MACRO_CONFIG_INT(ClShowhud, cl_showhud, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show ingame HUD")
MACRO_CONFIG_INT(ClShowChatFriends, cl_show_chat_friends, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show only chat messages from friends")
MACRO_CONFIG_INT(ClShowfps, cl_showfps, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show ingame FPS counter")

MACRO_CONFIG_INT(ClAirjumpindicator, cl_airjumpindicator, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClThreadsoundloading, cl_threadsoundloading, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Load sound files threaded")

MACRO_CONFIG_INT(ClWarningTeambalance, cl_warning_teambalance, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Warn about team balance")

MACRO_CONFIG_INT(ClMouseDeadzone, cl_mouse_deadzone, 300, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMouseFollowfactor, cl_mouse_followfactor, 60, 0, 200, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMouseMaxDistance, cl_mouse_max_distance, 800, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

MACRO_CONFIG_INT(ClCustomizeSkin, cl_customize_skin, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

MACRO_CONFIG_INT(EdZoomTarget, ed_zoom_target, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Zoom to the current mouse target")
MACRO_CONFIG_INT(EdShowkeys, ed_showkeys, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorGridInner, ed_color_grid_inner, 0xFFFFFF26, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorGridOuter, ed_color_grid_outer, 0xFF4C4C4C, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPoint, ed_color_quad_point, 0xFF0000FF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPointHover, ed_color_quad_point_hover, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPointActive, ed_color_quad_point_active, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPivot, ed_color_quad_pivot, 0x00FF00FF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPivotHover, ed_color_quad_pivot_hover, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorQuadPivotActive, ed_color_quad_pivot_Active, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorSelectionQuad, ed_color_selection_quad, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(EdColorSelectionTile, ed_color_selection_tile, 0xFFFFFF66, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

//MACRO_CONFIG_INT(ClFlow, cl_flow, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

MACRO_CONFIG_INT(ClShowWelcome, cl_show_welcome, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMotdTime, cl_motd_time, 10, 0, 100, CFGFLAG_CLIENT|CFGFLAG_SAVE, "How long to show the server message of the day")

MACRO_CONFIG_STR(ClVersionServer, cl_version_server, 100, "version.teeworlds.com", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Server to use to check for new versions")

MACRO_CONFIG_STR(ClFontfile, cl_fontfile, 255, "DejaVuSans.ttf", CFGFLAG_CLIENT|CFGFLAG_SAVE, "What font file to use")
MACRO_CONFIG_STR(ClLanguagefile, cl_languagefile, 255, "", CFGFLAG_CLIENT|CFGFLAG_SAVE, "What language file to use")

MACRO_CONFIG_INT(PlayerColorBody, player_color_body, 0x1B6F74, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player body color")
MACRO_CONFIG_INT(PlayerColorMarking, player_color_marking, 0xFF0000FF, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player marking color")
MACRO_CONFIG_INT(PlayerColorDecoration, player_color_decoration, 0x1B6F74, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player decoration color")
MACRO_CONFIG_INT(PlayerColorHands, player_color_hands, 0x1B759E, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player hands color")
MACRO_CONFIG_INT(PlayerColorFeet, player_color_feet, 0x1C873E, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player feet color")
MACRO_CONFIG_INT(PlayerColorEyes, player_color_eyes, 0x0000FF, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player eyes color")
MACRO_CONFIG_INT(PlayerUseCustomColorBody, player_use_custom_color_body, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for body")
MACRO_CONFIG_INT(PlayerUseCustomColorMarking, player_use_custom_color_marking, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for marking")
MACRO_CONFIG_INT(PlayerUseCustomColorDecoration, player_use_custom_color_decoration, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for decoration")
MACRO_CONFIG_INT(PlayerUseCustomColorHands, player_use_custom_color_hands, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for hands")
MACRO_CONFIG_INT(PlayerUseCustomColorFeet, player_use_custom_color_feet, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for feet")
MACRO_CONFIG_INT(PlayerUseCustomColorEyes, player_use_custom_color_eyes, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors for eyes")
MACRO_CONFIG_STR(PlayerSkin, player_skin, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin")
MACRO_CONFIG_STR(PlayerSkinBody, player_skin_body, 24, "standard", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin body")
MACRO_CONFIG_STR(PlayerSkinMarking, player_skin_marking, 24, "", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin marking")
MACRO_CONFIG_STR(PlayerSkinDecoration, player_skin_decoration, 24, "", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin decoration")
MACRO_CONFIG_STR(PlayerSkinHands, player_skin_hands, 24, "standard", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin hands")
MACRO_CONFIG_STR(PlayerSkinFeet, player_skin_feet, 24, "standard", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin feet")
MACRO_CONFIG_STR(PlayerSkinEyes, player_skin_eyes, 24, "standard", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin eyes")

//MACRO_CONFIG_INT(UiPage, ui_page, 6, 0, 10, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface page")
MACRO_CONFIG_INT(UiBrowserPage, ui_browser_page, 5, 5, 8, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface serverbrowser page")
MACRO_CONFIG_INT(UiSettingsPage, ui_settings_page, 0, 0, 5, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface settings page")
//MACRO_CONFIG_INT(UiToolboxPage, ui_toolbox_page, 0, 0, 2, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toolbox page")
MACRO_CONFIG_STR(UiServerAddress, ui_server_address, 64, "localhost:8303", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface server address")
MACRO_CONFIG_INT(UiMousesens, ui_mousesens, 100, 5, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Mouse sensitivity for menus/editor")

MACRO_CONFIG_INT(GfxNoclip, gfx_noclip, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Disable clipping")

MACRO_CONFIG_STR(ClBackgroundMap, cl_background_map, 64, "menu_night", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Background map")
MACRO_CONFIG_INT(ClRotationRadius, cl_rotation_radius, 30, 1, 500, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Camera rotation radius")
MACRO_CONFIG_INT(ClRotationSpeed, cl_rotation_speed, 40, 1, 120, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Camera rotations in seconds")

MACRO_CONFIG_INT(ClShowStartMenuImages, cl_show_start_menu_images, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show start menu images")

// server
MACRO_CONFIG_INT(SvWarmup, sv_warmup, 0, -1, 1000, CFGFLAG_SERVER, "Number of seconds to do warmup before match starts (0 disables, -1 all players ready)")
MACRO_CONFIG_STR(SvMotd, sv_motd, 900, "", CFGFLAG_SERVER, "Message of the day to display for the clients")
MACRO_CONFIG_INT(SvTeamdamage, sv_teamdamage, 0, 0, 1, CFGFLAG_SERVER, "Team damage")
MACRO_CONFIG_STR(SvMaprotation, sv_maprotation, 768, "", CFGFLAG_SERVER, "Maps to rotate between")
MACRO_CONFIG_INT(SvMatchesPerMap, sv_matches_per_map, 1, 1, 100, CFGFLAG_SERVER, "Number of matches on each map before rotating")
MACRO_CONFIG_INT(SvMatchSwap, sv_match_swap, 1, 0, 1, CFGFLAG_SERVER, "Swap teams between matches")
MACRO_CONFIG_INT(SvPowerups, sv_powerups, 1, 0, 1, CFGFLAG_SERVER, "Allow powerups like ninja")
MACRO_CONFIG_INT(SvScorelimit, sv_scorelimit, 20, 0, 1000, CFGFLAG_SERVER, "Score limit (0 disables)")
MACRO_CONFIG_INT(SvTimelimit, sv_timelimit, 0, 0, 1000, CFGFLAG_SERVER, "Time limit in minutes (0 disables)")
MACRO_CONFIG_STR(SvGametype, sv_gametype, 32, "dm", CFGFLAG_SERVER, "Game type (dm, tdm, ctf, lms, sur)")
MACRO_CONFIG_INT(SvTournamentMode, sv_tournament_mode, 0, 0, 1, CFGFLAG_SERVER, "Tournament mode. When enabled, players joins the server as spectator")
MACRO_CONFIG_INT(SvPlayerReadyMode, sv_player_ready_mode, 0, 0, 1, CFGFLAG_SERVER, "When enabled, players can pause/unpause the game and start the game on warmup via their ready state")
MACRO_CONFIG_INT(SvSpamprotection, sv_spamprotection, 1, 0, 1, CFGFLAG_SERVER, "Spam protection")

MACRO_CONFIG_INT(SvRespawnDelayTDM, sv_respawn_delay_tdm, 3, 0, 10, CFGFLAG_SERVER, "Time needed to respawn after death in tdm gametype")

MACRO_CONFIG_INT(SvSpectatorSlots, sv_spectator_slots, 0, 0, MAX_CLIENTS, CFGFLAG_SERVER, "Number of slots to reserve for spectators")
MACRO_CONFIG_INT(SvSkillLevel, sv_skill_level, 1, SERVERINFO_LEVEL_MIN, SERVERINFO_LEVEL_MAX, CFGFLAG_SERVER, "Supposed player skill level")
MACRO_CONFIG_INT(SvTeambalanceTime, sv_teambalance_time, 1, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before autobalancing teams")
MACRO_CONFIG_INT(SvInactiveKickTime, sv_inactivekick_time, 3, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before taking care of inactive players")
MACRO_CONFIG_INT(SvInactiveKick, sv_inactivekick, 1, 0, 2, CFGFLAG_SERVER, "How to deal with inactive players (0=move to spectator, 1=move to free spectator slot/kick, 2=kick)")

MACRO_CONFIG_INT(SvStrictSpectateMode, sv_strict_spectate_mode, 0, 0, 1, CFGFLAG_SERVER, "Restricts information in spectator mode")
MACRO_CONFIG_INT(SvVoteSpectate, sv_vote_spectate, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to move players to spectators")
MACRO_CONFIG_INT(SvVoteSpectateRejoindelay, sv_vote_spectate_rejoindelay, 3, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before a player can rejoin after being moved to spectators by vote")
MACRO_CONFIG_INT(SvVoteKick, sv_vote_kick, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to kick players")
MACRO_CONFIG_INT(SvVoteKickMin, sv_vote_kick_min, 0, 0, MAX_CLIENTS, CFGFLAG_SERVER, "Minimum number of players required to start a kick vote")
MACRO_CONFIG_INT(SvVoteKickBantime, sv_vote_kick_bantime, 5, 0, 1440, CFGFLAG_SERVER, "The time to ban a player if kicked by vote. 0 makes it just use kick")


/* Bla-Client */

// Blood
MACRO_CONFIG_INT(Blood, cl_blood, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Simple bloodmod")
MACRO_CONFIG_INT(BloodDamage, cl_blood_damage, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Simple bloodmod damage")

// Radar stuff
MACRO_CONFIG_INT(XPos, cl_radar_x_pos, 450, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Radar x position")
MACRO_CONFIG_INT(YPos, cl_radar_y_pos, 80, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Radar y position")
MACRO_CONFIG_INT(ClRadar, cl_enable_radar, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Radar on / off")
MACRO_CONFIG_INT(UseXY, cl_radar_use_xy, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Use radar y/x axis")

// texture stuff
MACRO_CONFIG_INT(Texture, texture_page, 4, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Texture page")
MACRO_CONFIG_STR(GameTexture, game_texture, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Gameskin texture")
MACRO_CONFIG_STR(GameParticles, particle_texture, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Particle texture")
MACRO_CONFIG_STR(GameEmoticons, emoticons_texture, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Emoticons texture")
MACRO_CONFIG_STR(GameCursor, cursor_texture, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Cursor texture")

// chat stuff
MACRO_CONFIG_INT(ClTextColors, cl_text_colors, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Render text colors") 
MACRO_CONFIG_INT(ClChatFeatures, cl_chat_features, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Eye candy chat features")

// other stuff
MACRO_CONFIG_INT(Bdadash, cl_bdadash, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClHealthBar, cl_health_bar, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Health & ammobar over tee") 
MACRO_CONFIG_INT(ClShowQuads, cl_show_quads, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show quads")
MACRO_CONFIG_STR(ClUpdateServer, cl_update_server, 100, "def.pf-control.de/bla/", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Server to use to update new versions")
MACRO_CONFIG_INT(ClYoda, cl_yoda, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClGhud, cl_ghud, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Gamer HUD") 

// sounds
MACRO_CONFIG_INT(ClGSound, cl_gsound, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Gamer sounds")
MACRO_CONFIG_INT(ClAnnouncers, cl_announcers, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Announcers")
MACRO_CONFIG_INT(ClAnnouncersShadows, cl_announcers_shadows, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Announcers outline shadows")
MACRO_CONFIG_INT(ClAnnouncersLegend, cl_announcers_legend, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")

// rainbow
MACRO_CONFIG_INT(ClRainbowFeet, cl_rainbow_feet, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")
MACRO_CONFIG_INT(ClRainbowHands, cl_rainbow_hands, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")
MACRO_CONFIG_INT(ClRainbowBody, cl_rainbow_body, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")
MACRO_CONFIG_INT(ClRainbowDecoration, cl_rainbow_decoration, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")
MACRO_CONFIG_INT(ClRainbowMarking, cl_rainbow_marking, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Legend under the announcers")


// debug
#ifdef CONF_DEBUG // this one can crash the server if not used correctly
	MACRO_CONFIG_INT(DbgDummies, dbg_dummies, 0, 0, 15, CFGFLAG_SERVER, "")
#endif

MACRO_CONFIG_INT(DbgFocus, dbg_focus, 0, 0, 1, CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(DbgTuning, dbg_tuning, 0, 0, 1, CFGFLAG_CLIENT, "")
#endif
