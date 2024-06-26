.set LOCALID_RIVAL, 1

LittlerootTown_BrendansHouse_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_BrendansHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_BrendansHouse_2F_OnWarp
	.byte 0

LittlerootTown_BrendansHouse_2F_OnTransition:
	call_if_lt VAR_LITTLEROOT_RIVAL_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan
	call_if_ge VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 4, PlayersHouse_2F_EventScript_BlockStairsUntilClockIsSet
	call SecretBase_EventScript_SetDecorationFlags
	setvar VAR_SECRET_BASE_INITIALIZED, 0
	call_if_eq VAR_WALDA_QUEST_STATE, 1, LittlerootTown_BrendansHouse_2F_EventScript_TrySetReadyForDarkrai
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckShouldUpdateBrendanPos::
	goto_if_set FLAG_MET_RIVAL_LILYCOVE, LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos
	goto_if_ge VAR_BIRCH_LAB_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_Ret
	goto LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos

LittlerootTown_BrendansHouse_2F_EventScript_TryUpdateBrendanPos::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_2F_EventScript_Ret
	@ Odd that the MaysHouse equivalent was used below instead
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_MaysHouse_2F_EventScript_Ret
	setobjectxyperm LOCALID_RIVAL, 0, 2
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_BrendansHouse_2F_EventScript_Ret::
	return

LittlerootTown_BrendansHouse_2F_EventScript_CheckSetReadyToMeetBrendan::
	checkplayergender
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan
	return

LittlerootTown_BrendansHouse_2F_EventScript_SetReadyToMeetBrendan::
	setvar VAR_LITTLEROOT_RIVAL_STATE, 2
	return

LittlerootTown_BrendansHouse_2F_EventScript_TrySetReadyForDarkrai::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_2F_EventScript_SetReadyForDarkrai
	return

LittlerootTown_BrendansHouse_2F_EventScript_SetReadyForDarkrai::
	setvar VAR_TEMP_7, 1
	return

LittlerootTown_BrendansHouse_2F_OnWarp:
	map_script_2 VAR_SECRET_BASE_INITIALIZED, 0, LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor
	.2byte 0

LittlerootTown_BrendansHouse_2F_EventScript_CheckInitDecor::
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, SecretBase_EventScript_InitDecorations
	end

LittlerootTown_BrendansHouse_2F_EventScript_RivalsPokeBall::
	lockall
	goto_if_eq VAR_LITTLEROOT_RIVAL_STATE, 2, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendan
	msgbox RivalsHouse_2F_Text_ItsRivalsPokeBall, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendan::
	delay 10
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanEnters
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 10
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	call_if_eq VAR_FACING, DIR_NORTH, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanNorth
	call_if_eq VAR_FACING, DIR_SOUTH, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanSouth
	call_if_eq VAR_FACING, DIR_WEST, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanWest
	call_if_eq VAR_FACING, DIR_EAST, LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanEast
	setvar VAR_LITTLEROOT_RIVAL_STATE, 3
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	setvar VAR_LITTLEROOT_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanNorth::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerNorth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanNorth
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCNorth
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanSouth::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerSouth
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanSouth
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCSouth
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanWest::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerWest
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanWest
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCWest
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_EventScript_MeetBrendanEast::
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerEast
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox RivalsHouse_2F_Text_BrendanWhoAreYou, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_RIVAL, LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCEast
	waitmovement 0
	return

LittlerootTown_BrendansHouse_2F_Movement_BrendanEnters:
	walk_down
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerNorth:
	walk_left
	walk_left
	walk_down
	walk_down
	walk_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCNorth:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanNorth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerSouth:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCSouth:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanSouth:
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerWest:
	walk_left
	walk_left
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCWest:
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanWest:
	delay_8
	delay_16
	walk_in_place_faster_up
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanApproachPlayerEast:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_BrendansHouse_2F_Movement_BrendanWalkToPCEast:
	walk_up
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

@ Unused, the player is already facing this direction so its unneeded
LittlerootTown_BrendansHouse_2F_Movement_PlayerWatchBrendanEast:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

LittlerootTown_BrendansHouse_2F_EventScript_PC::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_BrendansHouse_2F_EventScript_CheckPlayersPC
	goto_if_eq VAR_RESULT, FEMALE, LittlerootTown_BrendansHouse_2F_EventScript_CheckRivalsPC
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckPlayersPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	special DoPCTurnOnEffect
	playse SE_PC_ON
	msgbox gText_PlayerHouseBootPC, MSGBOX_DEFAULT
	special BedroomPC
	waitstate
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_TurnOffPlayerPC::
	setvar VAR_0x8004, PC_LOCATION_BRENDANS_HOUSE
	playse SE_PC_OFF
	special DoPCTurnOffEffect
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_CheckRivalsPC::
	msgbox gText_PokemonTrainerSchoolEmail, MSGBOX_DEFAULT
	releaseall
	end

LittlerootTown_BrendansHouse_2F_EventScript_Notebook::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PlayersHouse_2F_EventScript_ItsYourNotebook
	msgbox PlayersHouse_2F_Text_Notebook, MSGBOX_SIGN
	releaseall
	end

PlayersHouse_2F_EventScript_ItsYourNotebook::
	message PlayersHouse_2F_Text_ItsYourNotebook
	waitmessage
	multichoice 18, 0, MULTI_RANDOMISER_OPTIONS, FALSE
	switch VAR_RESULT
	case 0, PlayersHouse_2F_EventScript_ToggleWildRandom
	case 1, PlayersHouse_2F_EventScript_ToggleAbilityRandom
	case 2, PlayersHouse_2F_EventScript_ToggleTrainerRandom
	case 3, PlayersHouse_2F_EventScript_SeeRandomiserSeed
	case 4, PlayersHouse_2F_EventScript_SetRandomiserSeed
	case 5, PlayersHouse_2F_EventScriptCancelGameCube
	case MULTI_B_PRESSED, PlayersHouse_2F_EventScriptCancelGameCube
	end

PlayersHouse_2F_EventScript_ToggleWildRandom::
    goto_if_unset FLAG_SYS_ENCOUNTER_RANDOMISER, PlayersHouse_2F_EventScript_ToggleWildRandomOn
    clearflag FLAG_SYS_ENCOUNTER_RANDOMISER
    playse SE_PC_OFF
    message PlayersHouse_2F_Text_WildEncountersAreReset
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_ToggleWildRandomOn::
    setflag FLAG_SYS_ENCOUNTER_RANDOMISER
    playse SE_PC_LOGIN
    message PlayersHouse_2F_Text_WildEncountersAreRandom
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_ToggleAbilityRandom::
    goto_if_unset FLAG_SYS_ABILITY_RANDOMISER, PlayersHouse_2F_EventScript_ToggleAbilityRandomOn
    clearflag FLAG_SYS_ABILITY_RANDOMISER
    playse SE_PC_OFF
    message PlayersHouse_2F_Text_AbilitiesAreReset
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_ToggleAbilityRandomOn::
    setflag FLAG_SYS_ABILITY_RANDOMISER
    playse SE_PC_LOGIN
    message PlayersHouse_2F_Text_AbilitiesAreRandom
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_ToggleTrainerRandom::
    goto_if_unset FLAG_SYS_TRAINER_RANDOMISER, PlayersHouse_2F_EventScript_ToggleTrainerRandomOn
    clearflag FLAG_SYS_TRAINER_RANDOMISER
    playse SE_PC_OFF
    message PlayersHouse_2F_Text_TrainersAreReset
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_ToggleTrainerRandomOn::
    setflag FLAG_SYS_TRAINER_RANDOMISER
    playse SE_PC_LOGIN
    message PlayersHouse_2F_Text_TrainersAreRandom
    waitmessage
    waitbuttonpress
    goto PlayersHouse_2F_EventScript_ItsYourNotebook
    end

PlayersHouse_2F_EventScript_SeeRandomiserSeed::
	buffernumberstring STR_VAR_2, VAR_RANDOMISER_SEED
	message PlayersHouse_2F_Text_YourSeedIs
	waitmessage
	waitbuttonpress
	goto PlayersHouse_2F_EventScript_ItsYourNotebook
	end

PlayersHouse_2F_EventScript_SetRandomiserSeed::
	goto_if_set FLAG_SYS_INVALID_CHALLENGE, PlayersHouse_2F_EventScript_SetRandomiserSeedSkipWarning
	goto_if_set FLAG_SYS_ENFORCED_HARDMODE, PlayersHouse_2F_EventScript_RandomiserSeedWarning
PlayersHouse_2F_EventScript_SetRandomiserSeedSkipWarning::
	setvar VAR_0x8004, 9
	special EnterCode
	waitstate
	setvar VAR_0x8004, 0
	releaseall
	end

PlayersHouse_2F_EventScript_RandomiserSeedWarning::
	msgbox PlayersHouse_2F_Text_SeedWillInvalidateChallenge, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PlayersHouse_2F_EventScript_ItsYourNotebook
	goto PlayersHouse_2F_EventScript_SetRandomiserSeedSkipWarning
	end

LittlerootTown_BrendansHouse_2F_EventScript_GameCube::
	lockall
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, PlayersHouse_2F_EventScript_ItsYourGameCube
	msgbox PlayersHouse_2F_Text_ItsAGameCube, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

PlayersHouse_2F_EventScript_ItsYourGameCube::
	msgbox PlayersHouse_2F_Text_ItsYourGameCube, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PlayersHouse_2F_EventScriptCancelGameCube
	special EnterCode
	waitstate
PlayersHouse_2F_EventScriptCancelGameCube::
	releaseall
	end

PlayersHouse_2F_EventScript_DarkraiEvent::
	lock
	msgbox PlayersHouse_2F_Text_GoToSleep, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PlayersHouse_2F_EventScript_DarkraiEncounter
	release
	end

PlayersHouse_2F_EventScript_DarkraiEncounter::
	delay 8
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceDown
	delay 30
	fadescreen FADE_TO_BLACK
	delay 60
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PlayersHouse_2F_EventScript_ConjureDarkraiMale
	call_if_eq VAR_RESULT, FEMALE, PlayersHouse_2F_EventScript_ConjureDarkraiFemale
	delay 30
	setflag FLAG_BAG_DISABLED
	setflag FLAG_CATCHING_DISABLED
	message PlayersHouse_2F_Text_DarkraiCry
	playmoncry SPECIES_DARKRAI, CRY_MODE_ENCOUNTER
	waitmoncry
	closemessage
	seteventmon SPECIES_DARKRAI, 50
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, PlayersHouse_2F_EventScript_DarkraiDefeated
	goto PlayersHouse_2F_EventScript_EscapedDarkrai
	end

PlayersHouse_2F_EventScript_ConjureDarkraiMale::
	createvobject OBJ_EVENT_GFX_DARKRAI, 7, 1, 3
	return

PlayersHouse_2F_EventScript_ConjureDarkraiFemale::
	createvobject OBJ_EVENT_GFX_DARKRAI, 7, 7, 3
	return

PlayersHouse_2F_EventScript_DarkraiDefeated::
	clearflag FLAG_BAG_DISABLED
	clearflag FLAG_CATCHING_DISABLED
	setvar VAR_WALDA_QUEST_STATE, 2
	msgbox PlayersHouse_2F_Text_DispelledDarkrai, MSGBOX_DEFAULT
	delay 40
	checkplayergender
	call_if_eq VAR_RESULT, MALE, PlayersHouse_2F_EventScript_DoSparkleMale
	call_if_eq VAR_RESULT, FEMALE, PlayersHouse_2F_EventScript_DoSparkleFemale
	msgbox PlayersHouse_2F_Text_FoundAPhotograph, MSGBOX_DEFAULT
	giveitem ITEM_TATTERED_PHOTO
	release
	end

PlayersHouse_2F_EventScript_DoSparkleMale::
	playse SE_M_DETECT
	dofieldeffectsparkle 2, 4, 0
	waitfieldeffect FLDEFF_SPARKLE
	delay 8
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceRight
	return

PlayersHouse_2F_EventScript_DoSparkleFemale::
	playse SE_M_DETECT
	dofieldeffectsparkle 6, 4, 0
	waitfieldeffect FLDEFF_SPARKLE
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceLeft
	return

PlayersHouse_2F_EventScript_EscapedDarkrai::
	clearflag FLAG_BAG_DISABLED
	clearflag FLAG_CATCHING_DISABLED
	msgbox PlayersHouse_2F_Text_EscapedFromDarkrai, MSGBOX_DEFAULT
	release
	end

PlayersHouse_2F_Text_ClockIsStopped:
	.string "The clock is stopped…\p"
	.string "Better set it and start it!$"

PlayersHouse_2F_Text_HowDoYouLikeYourRoom:
	.string "MOM: {PLAYER}, how do you like your\n"
	.string "new room?\p"
	.string "Good! Everything's put away neatly!\p"
	.string "They finished moving everything in\n"
	.string "downstairs, too.\p"
	.string "Pokémon movers are so convenient!\p"
	.string "Oh, you should make sure that\n"
	.string "everything's all there on your desk.$"

PlayersHouse_2F_Text_Notebook:
	.string "{PLAYER} flipped open the notebook.\p"
	.string "ADVENTURE Rule No. 1\n"
	.string "Open the MENU with Start.\p"
	.string "ADVENTURE Rule NO. 2\n"
	.string "Record your progress with Save.\p"
	.string "The remaining pages are blank…$"

Common_Text_LookCloserAtMap:
	.string "{PLAYER} took a closer look at the\n"
	.string "HOENN region map.$"

PlayersHouse_2F_Text_ItsAGameCube:
	.string "It's a Nintendo GameCube.\p"
	.string "A Game Boy Advance is connected to\n"
	.string "serve as the Controller.$"

PlayersHouse_2F_Text_ItsYourNotebook:
	.string "It's your Diary.\n"
	.string "Randomise your story?$"

PlayersHouse_2F_Text_ItsYourGameCube:
	.string "It's your Nintendo GameCube.\p"
	.string "You have a cheat device connected.\n"
	.string "Input a cheat code?$"

PlayersHouse_2F_Text_WildEncountersAreReset:
	.string "Wild Encounters have been reset\n"
	.string "back to normal.$"

PlayersHouse_2F_Text_WildEncountersAreRandom:
	.string "Wild Encounters have been randomised.$"

PlayersHouse_2F_Text_AbilitiesAreReset:
	.string "Abilities have been reset\n"
	.string "back to normal.$"

PlayersHouse_2F_Text_AbilitiesAreRandom:
	.string "Abilities have been randomised.$"

PlayersHouse_2F_Text_TrainersAreReset:
	.string "Trainers have been reset\n"
	.string "back to normal.$"

PlayersHouse_2F_Text_TrainersAreRandom:
	.string "Trainers have been randomised.$"

PlayersHouse_2F_Text_YourSeedIs:
	.string "Your randomiser seed is:\n"
	.string "{STR_VAR_2}$"

PlayersHouse_2F_Text_SeedWillInvalidateChallenge:
	.string "WARNING: You are in challenge mode.\p"
	.string "Setting a seed will not take you out\n"
	.string "of challenge mode…\p"
	.string "But it will prevent you from recieving\n"
	.string "certain challenge mode rewards.\p"
	.string "Set your own seed anyways?$"

PlayersHouse_2F_Text_GoToSleep:
	.string "Go to sleep?$"

PlayersHouse_2F_Text_DarkraiCry:
	.string "Raaiiiii$"

PlayersHouse_2F_Text_DispelledDarkrai:
	.string "{PLAYER} dispelled the Nightmare.$"

PlayersHouse_2F_Text_FoundAPhotograph:
	.string "A tattered photograph was left at the\n"
	.string "foot of the bed.\p"
	.string "It depicts a small island with a crescent\n"
	.string "shaped pool of water at its center.$"

PlayersHouse_2F_Text_EscapedFromDarkrai:
	.string "{PLAYER} escaped from the Nightmare.$"
