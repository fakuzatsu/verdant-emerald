VerdantIsle_VictiniRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdantIsle_VictiniRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, VerdantIsle_VictiniRoom_OnResume
	.byte 0

VerdantIsle_VictiniRoom_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, VerdantIsle_VictiniRoom_EventScript_TryRemoveVictini
	end

VerdantIsle_VictiniRoom_EventScript_TryRemoveVictini::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

VerdantIsle_VictiniRoom_OnTransition:
	goto VerdantIsle_VictiniRoom_EventScript_TryHideOrShowVictini
	end

VerdantIsle_VictiniRoom_EventScript_TryHideOrShowVictini::
	goto_if_set FLAG_CAUGHT_VICTINI, VerdantIsle_VictiniRoom_EventScript_HideVictini
	goto_if_set FLAG_DEFEATED_VICTINI, VerdantIsle_VictiniRoom_EventScript_HideVictini
	clearflag FLAG_TEMP_4
	end

VerdantIsle_VictiniRoom_EventScript_HideVictini::
	setflag FLAG_TEMP_4
	end

VerdantIsle_VictiniRoom_EventScript_Victini::
	lock
	faceplayer
	message VerdantIsle_VictiniRoom_Text_VictiniCry
	playmoncry SPECIES_VICTINI, CRY_MODE_ENCOUNTER
	waitmoncry
	closemessage
	seteventmon SPECIES_VICTINI, 30
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, VerdantIsle_VictiniRoom_EventScript_VictiniDefeated
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, VerdantIsle_VictiniRoom_EventScript_PlayerOrVictiniRan
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, VerdantIsle_VictiniRoom_EventScript_PlayerOrVictiniRan
	goto_if_eq VAR_RESULT, B_OUTCOME_MON_TELEPORTED, VerdantIsle_VictiniRoom_EventScript_PlayerOrVictiniRan
	setflag FLAG_CAUGHT_VICTINI
	release
	end

VerdantIsle_VictiniRoom_EventScript_VictiniDefeated::
	setflag FLAG_DEFEATED_VICTINI
	setvar VAR_0x8004, SPECIES_VICTINI
	goto Common_EventScript_LegendaryRanAway
	release
	end

VerdantIsle_VictiniRoom_EventScript_PlayerOrVictiniRan::
	setvar VAR_0x8004, SPECIES_VICTINI
	goto Common_EventScript_LegendaryRanAway
	release
	end

VerdantIsle_VictiniRoom_Text_VictiniCry:
	.string "Ta-ta-ta-tah$"
