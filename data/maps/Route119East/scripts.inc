Route119East_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route119East_OnResume
	map_script MAP_SCRIPT_ON_RESUME, Route119East_OnResume
	map_script MAP_SCRIPT_ON_LOAD, Route119East_OnLoad
	.byte 0

Route119East_OnLoad:
	call_if_set FLAG_HIDDEN_ITEM_ALTARIANITE, Route119East_Hide_Altarianite
	end

Route119East_Hide_Altarianite::
    setmetatile 24, 51, METATILE_General_Grass, FALSE
    return

Route119East_Altarianite::
	goto_if_set FLAG_HIDDEN_ITEM_ALTARIANITE, Route119East_End_Altarianite
	checkitemspace ITEM_ALTARIANITE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	call Route119East_Hide_Altarianite
	special DrawWholeMapView
	giveitem ITEM_ALTARIANITE
	setflag FLAG_HIDDEN_ITEM_ALTARIANITE
Route119East_End_Altarianite::
	release
	end	

Route119East_OnResume:
	setstepcallback STEP_CB_FORTREE_BRIDGE
	special SetRoute119Weather
	call Route119East_CheckWeather
	end

Route119East_CheckWeather::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 14, Route119East_StopCheckingWeather
	goto_if_gt VAR_TEMP_1, 2000, Route119East_StopCheckingWeather
Route119East_DoSpecialWeather::
	special GetDayOrNight
	goto_if_eq VAR_RESULT, 1, Route119East_SpecialWeatherNight
	goto_if_eq VAR_RESULT, 0, Route119East_SpecialWeatherDay
	doweather
	return

Route119East_SpecialWeatherNight::
	setweather WEATHER_RAIN
	return

Route119East_SpecialWeatherDay::
	setweather WEATHER_ROUTE119_CYCLE
	return

Route119East_StopCheckingWeather::
	special GetDayOrNight
	goto_if_eq VAR_RESULT, 1, Route119East_OnResume_Night
	goto_if_eq VAR_RESULT, 0, Route119East_OnResume_Day
	doweather
	end

Route119East_OnResume_Night:
	setweather WEATHER_SHADE
	return

Route119East_OnResume_Day:
	setweather WEATHER_SUNNY
	return

Route119East_EventScript_StopSpecialWeather::
	special GetDayOrNight
	call_if_eq VAR_RESULT, 1, Route119East_OnResume_Night
	call_if_eq VAR_RESULT, 0, Route119East_OnResume_Day
	doweather
	end

Route119East_EventScript_StartSpecialWeather::
	special GetDayOrNight
	call_if_eq VAR_RESULT, 1, Route119East_SpecialWeatherNight
	call_if_eq VAR_RESULT, 0, Route119East_SpecialWeatherDay
	doweather
	end

