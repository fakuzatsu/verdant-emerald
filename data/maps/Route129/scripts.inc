Route129_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route129_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route129_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route129_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, Route129_OnResume
	.byte 0

Route129_OnResume_Night:
	setweather WEATHER_RAIN
	return

Route129_OnResume_Day:
	setweather WEATHER_SUNNY
	return

Route129_OnResume:
	call_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, Route129_EventScript_CheckSetAbnormalWeather
	goto_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_WEST, AbnormalWeather_StartKyogreWeather
	goto_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_EAST, AbnormalWeather_StartKyogreWeather
	special GetDayOrNight
	goto_if_eq VAR_RESULT, 1, Route129_OnResume_Night
	goto_if_eq VAR_RESULT, 0, Route129_OnResume_Day
	end

Route129_OnLoad:
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_WEST, AbnormalWeather_EventScript_PlaceTilesRoute129West
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_EAST, AbnormalWeather_EventScript_PlaceTilesRoute129East
	end

Route129_OnTransition:
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, Route129_EventScript_CheckSetAbnormalWeather
	goto_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_WEST, AbnormalWeather_StartKyogreWeather
	goto_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_EAST, AbnormalWeather_StartKyogreWeather
	special GetDayOrNight
	goto_if_eq VAR_RESULT, 1, Route129_OnResume_Night
	goto_if_eq VAR_RESULT, 0, Route129_OnResume_Day
	end

Route129_EventScript_CheckSetAbnormalWeather::
	goto_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	return

Route129_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	.2byte 0

Route129_EventScript_Chase::
	trainerbattle_single TRAINER_CHASE, Route129_Text_ChaseIntro, Route129_Text_ChaseDefeat
	msgbox Route129_Text_ChasePostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Allison::
	trainerbattle_single TRAINER_ALLISON, Route129_Text_AllisonIntro, Route129_Text_AllisonDefeat
	msgbox Route129_Text_AllisonPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Reed::
	trainerbattle_single TRAINER_REED, Route129_Text_ReedIntro, Route129_Text_ReedDefeat
	msgbox Route129_Text_ReedPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Tisha::
	trainerbattle_single TRAINER_TISHA, Route129_Text_TishaIntro, Route129_Text_TishaDefeat
	msgbox Route129_Text_TishaPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Clarence::
	trainerbattle_single TRAINER_CLARENCE, Route129_Text_ClarenceIntro, Route129_Text_ClarenceDefeat
	msgbox Route129_Text_ClarencePostBattle, MSGBOX_AUTOCLOSE
	end

