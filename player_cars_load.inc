
new pSelectedCar[MAX_PLAYERS] = {-1,...};

CMD:car(playerid)
{
	if(GetPVarIntNew(playerid, "trucker_job") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	show_player_cars(playerid);

	return true;
}

CMD:park(playerid, params[])
{

	if(!get_player_in_p_car(playerid))
		return SendErr(playerid, !"Р’Рё РїРѕРІРёРЅРЅС– СЃРёРґС–С‚Рё РІ РѕСЃРѕР±РёСЃС‚РѕРјСѓ С‚СЂР°РЅСЃРїРѕСЂС‚С–!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	if(pGreenZone{playerid})
		return SendErr(playerid, !"Р—Р°Р±РѕСЂРѕРЅРµРЅРѕ РїР°СЂРєСѓРІР°С‚Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚ Сѓ Р—РµР»РµРЅС–Р№ Р—РѕРЅС–!");

	if(GetPVarIntNew(playerid, "cooldown_park_car") > gettime())
		return SendErr(playerid, !"РџР°СЂРєСѓРІР°С‚Рё С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р± РјРѕР¶РЅР° СЂР°Р· РЅР° 1 С…РІРёР»РёРЅСѓ!");

	if(isAnyHouseInPlayerList(playerid) || pData[playerid][pGarage] != -1)
	{	
		for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
		{
			if(GetPlayerVehicleID(playerid) == vehicle_player_max[playerid][i])
			{
				new 
					Float:x, Float:y, Float:z, Float:r;

				GetVehiclePos(vehicle_player_max[playerid][i],x,y,z);
				GetVehicleZAngle(vehicle_player_max[playerid][i],r);

				new 
					car_vw = GetVehicleVirtualWorld(vehicle_player_max[playerid][i]);

			    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
			    	parking_x = '%.4f',\
			    	parking_y = '%.4f',\
			    	parking_z = '%.4f',\
			    	parking_a = '%.4f',\
			    	parking_vw = '%d'\
			    	WHERE id = '%d' AND userid = '%d'",
					x,
					y,
					z,
					r,
					car_vw,

			    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

				mysql_tquery(g_sql, GlobalString, !"", !"");

				new
					Float:ac_health;

				GetVehicleHealth(vehicle_player_max[playerid][i], ac_health);

			    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
			    	number = '%s',\
			    	lock_status = '%d',\
			    	parking_garage = '%d',\
			    	parking_hotel = '%d',\
			    	shtraf_car = '%d',\
			    	parking_police = '%d',\
			    	energy_car = '%f',\
			    	mileage = '%f',\
			    	fuel = '%f',\
			    	health = '%f',\
			    	consumables_candles = '%f',\
			    	consumables_oil = '%f',\
			    	consumables_brake = '%f',\
			    	consumables_belt = '%f',\
			    	consumables_starter = '%f',\
			    	consumables_generator = '%f',\
			    	consumables_forsunki = '%f',\
			    	consumables_fuel = '%f',\
			    	generator_energy = '%f',\
			    	battery_energy = '%f',\
			    	number_region = '%s',\
			    	number_type = '%d'\
			    	WHERE id = '%d' AND userid = '%d'",

			    	vehicle[vehicle_player_max[playerid][i]][cPlate],
					vehicle[vehicle_player_max[playerid][i]][cLock],
					vehicle[vehicle_player_max[playerid][i]][parking_garage],
					vehicle[vehicle_player_max[playerid][i]][parking_hotel],
					vehicle[vehicle_player_max[playerid][i]][shtraf_car],
					vehicle[vehicle_player_max[playerid][i]][parking_police],
					vehicle[vehicle_player_max[playerid][i]][cEnergy],
					vehicle[vehicle_player_max[playerid][i]][cMileage],
					vehicle[vehicle_player_max[playerid][i]][cFuel],
					ac_health,
					vehicle[vehicle_player_max[playerid][i]][consumables_candles],
					vehicle[vehicle_player_max[playerid][i]][consumables_oil],
					vehicle[vehicle_player_max[playerid][i]][consumables_brake],
					vehicle[vehicle_player_max[playerid][i]][consumables_belt],
					vehicle[vehicle_player_max[playerid][i]][consumables_starter],
					vehicle[vehicle_player_max[playerid][i]][consumables_generator],
					vehicle[vehicle_player_max[playerid][i]][consumables_forsunki],
					vehicle[vehicle_player_max[playerid][i]][consumables_fuel],


					vehicle[vehicle_player_max[playerid][i]][cGeneratorEnergy],
					vehicle[vehicle_player_max[playerid][i]][cBatteryEnergy],

					vehicle[vehicle_player_max[playerid][i]][cPlateRegion],
					vehicle[vehicle_player_max[playerid][i]][cPlateType],

			    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

				mysql_tquery(g_sql, GlobalString, !"", !"");

				SendSucc(playerid, !"Р’Рё РїРµСЂРµРїР°СЂРєСѓРІР°Р»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±");
				break;
			}
		}
	}
	else
	{
		if(!GetPVarIntNew(playerid, "player_in_parking"))
			return SendErr(playerid, !"РћСЃРєС–Р»СЊРєРё Сѓ Р’Р°СЃ РЅРµРјР°С” РјР°Р№РЅР°, РїСЂРёРїР°СЂРєСѓРІР°С‚Рё Р°РІС‚РѕРјРѕР±С–Р»СЊ РјРѕР¶РЅР° С‚С–Р»СЊРєРё РЅР° РїР°СЂРєС–РЅРіСѓ!");

		for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
		{
			if(GetPlayerVehicleID(playerid) == vehicle_player_max[playerid][i])
			{
				new 
					Float:x, Float:y, Float:z, Float:r;

				GetVehiclePos(vehicle_player_max[playerid][i],x,y,z);
				GetVehicleZAngle(vehicle_player_max[playerid][i],r);

				new 
					car_vw = GetVehicleVirtualWorld(vehicle_player_max[playerid][i]);

			    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
			    	parking_x = '%.4f',\
			    	parking_y = '%.4f',\
			    	parking_z = '%.4f',\
			    	parking_a = '%.4f',\
			    	parking_vw = '%d'\
			    	WHERE id = '%d' AND userid = '%d'",
					x,
					y,
					z,
					r,
					car_vw,

			    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

				mysql_tquery(g_sql, GlobalString, !"", !"");

				new
					Float:ac_health;

				GetVehicleHealth(vehicle_player_max[playerid][i], ac_health);


			    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
			    	number = '%s',\
			    	lock_status = '%d',\
			    	parking_garage = '%d',\
			    	parking_hotel = '%d',\
			    	shtraf_car = '%d',\
			    	parking_police = '%d',\
			    	energy_car = '%f',\
			    	mileage = '%f',\
			    	fuel = '%f',\
			    	health = '%f',\
			    	consumables_candles = '%f',\
			    	consumables_oil = '%f',\
			    	consumables_brake = '%f',\
			    	consumables_belt = '%f',\
			    	consumables_starter = '%f',\
			    	consumables_generator = '%f',\
			    	consumables_forsunki = '%f',\
			    	consumables_fuel = '%f',\
			    	generator_energy = '%f',\
			    	battery_energy = '%f',\
			    	number_region = '%s',\
			    	number_type = '%d'\
			    	WHERE id = '%d' AND userid = '%d'",

			    	vehicle[vehicle_player_max[playerid][i]][cPlate],
					vehicle[vehicle_player_max[playerid][i]][cLock],
					vehicle[vehicle_player_max[playerid][i]][parking_garage],
					vehicle[vehicle_player_max[playerid][i]][parking_hotel],
					vehicle[vehicle_player_max[playerid][i]][shtraf_car],
					vehicle[vehicle_player_max[playerid][i]][parking_police],
					vehicle[vehicle_player_max[playerid][i]][cEnergy],
					vehicle[vehicle_player_max[playerid][i]][cMileage],
					vehicle[vehicle_player_max[playerid][i]][cFuel],
					ac_health,
					vehicle[vehicle_player_max[playerid][i]][consumables_candles],
					vehicle[vehicle_player_max[playerid][i]][consumables_oil],
					vehicle[vehicle_player_max[playerid][i]][consumables_brake],
					vehicle[vehicle_player_max[playerid][i]][consumables_belt],
					vehicle[vehicle_player_max[playerid][i]][consumables_starter],
					vehicle[vehicle_player_max[playerid][i]][consumables_generator],
					vehicle[vehicle_player_max[playerid][i]][consumables_forsunki],
					vehicle[vehicle_player_max[playerid][i]][consumables_fuel],


					vehicle[vehicle_player_max[playerid][i]][cGeneratorEnergy],
					vehicle[vehicle_player_max[playerid][i]][cBatteryEnergy],

					vehicle[vehicle_player_max[playerid][i]][cPlateRegion],
					vehicle[vehicle_player_max[playerid][i]][cPlateType],

			    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

				mysql_tquery(g_sql, GlobalString, !"", !"");

				SendSucc(playerid, !"Р’Рё РїРµСЂРµРїР°СЂРєСѓРІР°Р»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±");
				break;
			}
		}		
	}

	SendInf(playerid, !"Р’Рё СѓСЃРїС–С€РЅРѕ РїСЂРёРїР°СЂРєСѓРІР°Р»Рё СЃРІС–Р№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±!");
	SendInf(playerid, !"РўРµРїРµСЂ РїСЂРё РІС…РѕРґС– РІС–РЅ Р±СѓРґРµ Р·'СЏРІР»СЏС‚РёСЃСЏ РЅР° С†СЊРѕРјСѓ РјС–СЃС†С–!");	

	SetPVarIntNew(playerid, "cooldown_park_car", gettime()+60);

	return true;
}

stock show_car_docs(playerid, sql_id)
{
	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{
			new veh 		= vehicle_player_max[playerid][i];
			new model 		= GetVehicleModel(veh);
			new transport 	= model-400;
			new Float: health;
			GetVehicleHealth(veh, health);
			
			format(GlobalString, sizeof GlobalString, "\
			"cWH"РќР°Р·РІР°: "LIME_GREEN"%s\n\n\
			"cWH"РњРѕРґРµР»СЊ: "LIME_GREEN"%d\n\
			"cWH"РЎС‚Р°РЅ: "LIME_GREEN"%d\n\
			"cWH"РџСЂРѕР±С–Рі: "LIME_GREEN"%d\n\
			"cWH"РџР°Р»РёРІРѕ: "LIME_GREEN"%f\n\
			"cWH"РљРѕР»С–СЂ: "LIME_GREEN"ID %d, %d\n\
			"cWH"Р”РµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ: "LIME_GREEN"%d\n\
			"cWH"РќРѕРјРµСЂРЅС– Р·РЅР°РєРё: "LIME_GREEN"%s %s\n\
			",
			transport_config[transport][transport_name],
			model,
			floatround(health, floatround_round),
			floatround(vehicle[veh][cMileage], floatround_round),
			floatround(vehicle[veh][cFuel], floatround_round),
			vehicle[veh][cColor1],
			vehicle[veh][cColor2],
			transport_config[transport][transport_price],
			vehicle[veh][cPlate],
			vehicle[veh][cPlateRegion]
			);
			
			new string[128];
			format(string, sizeof string, ""LIME_GREEN"Р”РѕРєСѓРјРµРЅС‚Рё РЅР° РўР— в„–%d", sql_id); 
			SPD(playerid, 0x0, DIALOG_STYLE_MSGBOX, string, GlobalString, "Р—Р°РєСЂРёС‚Рё", "");
			
			break;
		}
	}
	return 1;
}

// TODO: СЂРµС„Р°РєС‚РѕСЂ РІСЃС–С… Cache С„СѓРЅРєС†С–Р№
stock show_player_cars(playerid)
{
	mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT * FROM player_vehicles WHERE userid = '%d'", pData[playerid][pMysqlID]);
	
	new 
		Cache: result = mysql_query(g_sql, GlobalString, true),
		row_count = 0;

	cache_get_row_count(row_count);
	if(!row_count)
	{
		cache_delete(result);
		return SendErr(playerid, !"РўСЂР°РЅСЃРїРѕСЂС‚ РЅРµ Р·РЅР°Р№РґРµРЅРѕ"), SetPVarIntNew(playerid, "CarSellStatus", false);
	}

	new 
		sql_id, 
		modelid,
		tempcarData,
		tempunixData;

	format(GlobalString, sizeof(GlobalString), ""cGREY"РўСЂР°РЅСЃРїРѕСЂС‚\t"cGREY"РЎС‚Р°РЅ\t"cGREY"РўРµСЂРјС–РЅ РґС–С—\n");

	new vehicleStatus[32];

 	for(new i; i < row_count; i++)
	{
		cache_get_value_name_int(i, "id", sql_id);
		cache_get_value_name_int(i, "model", modelid);
		cache_get_value_name_int(i, "tempcar", tempcarData);
		cache_get_value_name_int(i, "tempunix", tempunixData);

		if(tempcarData)
		{
			new year, month, day, hour, minute;
			gmtime(tempunixData, year, month, day, hour, minute, _);

			if(gettime() < tempunixData) format(vehicleStatus, sizeof(vehicleStatus), ""cGR"[%dСЂ.%dРј.%dРґ %dРі. %dС….]", year, month, day, hour, minute);
			else format(vehicleStatus, sizeof(vehicleStatus), ""cRED"[%dСЂ.%dРј.%dРґ %dРі. %dС….]", year, month, day, hour, minute);
		}
		else format(vehicleStatus, sizeof(vehicleStatus), ""LIME_GREEN"[Р‘РµР· С‚РµСЂРјС–РЅСѓ РґС–С—]");

		format(GlobalString, sizeof(GlobalString), "%s"LIME_GREEN"%s\t"cGREY"%s\t%s\n",
			GlobalString, transport_config[modelid-400][transport_name],
			get_player_veh_status(sql_id) == 1 ? (""cGR"[Р—Р°РІР°РЅС‚Р°Р¶РµРЅРѕ]") : (""cLRED"[РќРµ Р·Р°РІР°РЅС‚Р°Р¶РµРЅРѕ]"),
			vehicleStatus);
	}

	SPD(playerid, DIALOG_PLAYER_VEHICLE_LIST, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"РћСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚", GlobalString, !"РћР±СЂР°С‚Рё", !"Р—Р°РєСЂРёС‚Рё");

	cache_delete(result);

	return true;
}

stock get_player_veh_status(id)
{
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(vehicle[i][v_vehicle] == id)
			return true;
	}
	return false;
}

stock get_player_in_p_car(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid)) 
		return false;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(GetPlayerVehicleID(playerid) == vehicle_player_max[playerid][i])
			return true;
	}
	return false;
}

//С‚СѓС‚
stock show_player_vehicle_menu(playerid, sql_id)
{
	SetPVarIntNew(playerid, "player_vehicle_select_sql", sql_id);

	new 
		vehicle_id;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];
		}
	}

    new text_mark[100];
    format(text_mark, sizeof(text_mark), ""cWH"РћСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚ "LIME_GREEN"%s[%d]", transport_config[GetVehicleModel(vehicle_id)-400][transport_name], GetPVarIntNew(playerid, "player_vehicle_select_sql"));

	SPD(playerid, DIALOG_CAR_CHANGE_PANEL, DIALOG_STYLE_TABLIST_HEADERS, text_mark, "\
	    "cGREY"РџСѓРЅРєС‚\t"cGREY"Р”С–СЏ\n\
	    "LIME_GREEN"1. "cWH"РџРѕР·РЅР°С‡РёС‚Рё С‚СЂР°РЅСЃРїРѕСЂС‚ РЅР° GPS\t"cGR"300 РіСЂРёРІРµРЅСЊ\n\
	    "LIME_GREEN"2. "cWH"Р†РЅС„РѕСЂРјР°С†С–СЏ РїСЂРѕ С‚СЂР°РЅСЃРїРѕСЂС‚\t"LIME_GREEN"Р’РёРІС‡РёС‚Рё\n\
	    "LIME_GREEN"3. "cWH"Р‘СѓРєСЃРёСЂСѓРІР°РЅРЅСЏ С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ РІ РіР°СЂР°Р¶\t"cGR"1500 РіСЂРёРІРµРЅСЊ\n\
	    "LIME_GREEN"4. "cWH"РЎС‚Р°РЅ Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"cGR"Р’РёРІС‡РёС‚Рё\n\
		"LIME_GREEN"5. "cWH"Р”РѕРєСѓРјРµРЅС‚Рё РЅР° С‚СЂР°РЅСЃРїРѕСЂС‚\t"cGR"Р’РёРІС‡РёС‚Рё\n\
	    "LIME_GREEN"6. "cWH"РџСЂРёРїР°СЂРєСѓРІР°С‚Рё С‚СЂР°РЅСЃРїРѕСЂС‚\t\n\
		"LIME_GREEN"7. "cWH"Р’РёРІР°РЅС‚Р°Р¶РёС‚Рё Р°РІС‚РѕРјРѕР±С–Р»СЊ Р· СЃРµСЂРІРµСЂР°", !"РћР±СЂР°С‚Рё", !"Р—Р°РєСЂРёС‚Рё");		

	return true;
}


callback:: spawn_player_vehicle(playerid, sql_id)
{
	mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT * FROM `player_vehicles` WHERE `id` = '%i'", sql_id);

	new 
		Cache: result = mysql_query(g_sql, GlobalString, true),
		row_count = 0;

	cache_get_row_count(row_count);
	if(!row_count)
	{
		cache_delete(result);
		return true;
	}

	new
		Float:x, Float:y, Float:z, Float:a, Float:ac_health,
		model,
		color1,
		color2,
		vw,
		veh_id,
		sqlid = -1;

	cache_get_value_name_int(0, "id", sqlid);
	cache_get_value_name_int(0, "model", model);
	cache_get_value_name_int(0, "color_1", color1); 
	cache_get_value_name_int(0, "color_2", color2); 
    cache_get_value_name_int(0, "parking_vw", vw);
	cache_get_value_name_float(0, "parking_x", x);
	cache_get_value_name_float(0, "parking_y", y);
	cache_get_value_name_float(0, "parking_z", z);
	cache_get_value_name_float(0, "parking_a", a);

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max[playerid][i] == 0)
		{
			veh_id = CreateVehicle(model, x, y, z, a, color1,color2, -1);
			vehicle_player_max_sql[playerid][i] = sql_id;
			vehicle_player_max[playerid][i] = veh_id;

			//vehicle[vehicle_player_max[playerid][i]][cOwnTo] = sql_id; EDIT 12.07.2021
			vehicle[vehicle_player_max[playerid][i]][cOwnTo] = -2;

			SetVehicleVirtualWorld(veh_id, vw);
			LinkVehicleToInterior(veh_id, 0);
			break;
		}
	}

	if(!veh_id)
		return 1;

	cache_get_value_name_int(0, "parking_garage", vehicle[veh_id][parking_garage]);
	cache_get_value_name_int(0, "vehicle_prize",vehicle[veh_id][vehicle_prize]);

	vehicle[veh_id][vehicle_world] = vw;

	if(vehicle[veh_id][parking_garage] == 1)
	{
		SetVehicleVirtualWorld(veh_id, vw);
		LinkVehicleToInterior(veh_id, 0);
	}

	cache_get_value_name(0, "number", vehicle[veh_id][cPlate], 24);
	cache_get_value_name(0, "number_region", vehicle[veh_id][cPlateRegion], 24);
	cache_get_value_name_int(0, "number_type", vehicle[veh_id][cPlateType]);
	cache_get_value_name_int(0, "id", vehicle[veh_id][v_vehicle]);
	cache_get_value_name(0, "date_buy_car", vehicle[veh_id][buy_date_car], 24); 

	cache_get_value_name_int(0, "tempunix", vehicle[veh_id][tempunix]);
	cache_get_value_name_int(0, "tempcar", vehicle[veh_id][tempcar]);

	if(vehicle[veh_id][cPlateType] == NUMBER_REGION_UA)
	{
		format(vehicle[veh_id][cPlate], 12, vehicle[veh_id][cPlate]);
		format(vehicle[veh_id][cPlateRegion], 12, vehicle[veh_id][cPlateRegion]);

		SetVehicleUaNumberPlate(veh_id, vehicle[veh_id][cPlate]);
	}
	else if(vehicle[veh_id][cPlateType] == 0)
	{
		format(vehicle[veh_id][cPlate], 12, "");
		format(vehicle[veh_id][cPlateRegion], 12, "");				
		SetVehicleNoPlateNumberPlate(veh_id, "-----", "---");
	}



    vehicle[veh_id][parking_x] = x;
    vehicle[veh_id][parking_y] = y;
    vehicle[veh_id][parking_z] = z;
    vehicle[veh_id][parking_a] = a;

	GetVehiclePos(veh_id, x, y, z);

	cache_get_value_name_int(0, "lock_status", vehicle[veh_id][cLock]);
	cache_get_value_name_int(0, "parking_hotel", vehicle[veh_id][parking_hotel]);
	cache_get_value_name_int(0, "shtraf_car", vehicle[veh_id][shtraf_car]);
	cache_get_value_name_int(0, "parking_police", vehicle[veh_id][parking_police]);
	cache_get_value_name_float(0, "mileage", vehicle[veh_id][cMileage]);
    cache_get_value_name_float(0, "fuel", vehicle[veh_id][cFuel]);
    cache_get_value_name_float(0, "health", ac_health);

    cache_get_value_name_float(0, "consumables_candles", vehicle[veh_id][consumables_candles]);
    cache_get_value_name_float(0, "consumables_oil", vehicle[veh_id][consumables_oil]);
    cache_get_value_name_float(0, "consumables_brake", vehicle[veh_id][consumables_brake]);
    cache_get_value_name_float(0, "consumables_belt", vehicle[veh_id][consumables_belt]);
    cache_get_value_name_float(0, "consumables_starter", vehicle[veh_id][consumables_starter]);
    cache_get_value_name_float(0, "consumables_generator",vehicle[veh_id][consumables_generator]);
    cache_get_value_name_float(0, "consumables_forsunki",vehicle[veh_id][consumables_forsunki]);
    cache_get_value_name_float(0, "consumables_fuel", vehicle[veh_id][consumables_fuel]);
	cache_get_value_name_float(0, "energy_car", vehicle[veh_id][cEnergy]);
    cache_get_value_name_float(0, "generator_energy", vehicle[veh_id][cGeneratorEnergy]);
    cache_get_value_name_float(0, "battery_energy", vehicle[veh_id][cBatteryEnergy]);

	pData[playerid][car_id] = GetPlayerVehicleID(playerid);

    cache_get_value_name(0, "consumables_candles_date", vehicle[veh_id][consumables_candles_date], 32);
    cache_get_value_name(0, "consumables_oil_date", vehicle[veh_id][consumables_oil_date], 32);
    cache_get_value_name(0, "consumables_brake_date", vehicle[veh_id][consumables_brake_date], 32);
    cache_get_value_name(0, "consumables_belt_date", vehicle[veh_id][consumables_belt_date], 32);
    cache_get_value_name(0, "consumables_starter_date", vehicle[veh_id][consumables_starter_date], 32);
    cache_get_value_name(0, "consumables_generator_date", vehicle[veh_id][consumables_generator_date], 32);
    cache_get_value_name(0, "consumables_forsunki_date", vehicle[veh_id][consumables_forsunki_date], 32);
    cache_get_value_name(0, "consumables_fuel_date", vehicle[veh_id][consumables_fuel_date], 32);

	SetVehicleHealth(veh_id, ac_health);

	RepairVehicle(veh_id);
	vehicle_lock_status(veh_id, vehicle[veh_id][cLock]);

	cache_delete(result);
	return true;
}

callback:: MYSQL_SellCar(playerid, car_num)
{
	new rows;
	cache_get_row_count(rows);
	if(!rows) return false;

	new sql_id = -1, tempcarstatus = 0;
	cache_get_value_name_int(car_num, "id", sql_id);
	cache_get_value_name_int(car_num, "tempcar", tempcarstatus);

	if(tempcarstatus) return SendErr(playerid, !"Р’Рё РЅРµ РјРѕР¶РµС‚Рµ РїСЂРѕРґР°С‚Рё С‚РёРјС‡Р°СЃРѕРІРёР№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±!");

	dialog_accept_sell_car_gos(playerid, sql_id);
	return true;
}

stock dialog_all_player_vehicle(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext

	switch(dialogid)
	{
		case DIALOG_PLAYER_VEHICLE_PANEL:
		{
			if(!response)
			{
				pSelectedCar[playerid] = -1;
				return true;
			}
			
			new 
				car_num = pSelectedCar[playerid];
				
			mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT * FROM `player_vehicles` WHERE `userid` = '%i'", pData[playerid][pMysqlID]);
			new 
				Cache:result = mysql_query(g_sql, GlobalString, true),
				row_count = 0;

			cache_get_row_count(row_count);
			if(!row_count)
			{
				cache_delete(result);
				return SendErr(playerid, !"РЎС‚Р°Р»Р°СЃСЏ С‚РµС…РЅС–С‡РЅР° РїРѕРјРёР»РєР°! РљРѕРґ: #100");
			}

			new 	
				sql_id = 0,
				models = 0,
				Float:x,
				Float:y,
				Float:z,
				Float:a,
				vw;

			cache_get_value_name_int(car_num, "id", sql_id);
			cache_get_value_name_int(car_num, "model", models);

			cache_get_value_name_float(car_num, "parking_x", x);
			cache_get_value_name_float(car_num, "parking_y", y);
			cache_get_value_name_float(car_num, "parking_z", z);
			cache_get_value_name_float(car_num, "parking_a", a);
			cache_get_value_name_int(car_num, "parking_vw", vw);


			cache_delete(result);
				
			switch(listitem)
			{
				case 0:
				{
					if(GetPlayerMoneyEx(playerid) < 300)
					{
						pSelectedCar[playerid] = -1;
						return SendErr(playerid, !"РЈ Р’Р°СЃ РЅРµРґРѕСЃС‚Р°С‚РЅСЊРѕ РіСЂРѕС€РµР№ РґР»СЏ РїРѕР·РЅР°С‡РєРё С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ РїРѕ GPS!"); 
					}
					
					if(vw > 0)
					{
						pTemp[playerid][pGPS] = true;
						
						SetPlayerCheckpointEx(playerid, 2214.7146,-1967.1420,18.5226, 4.0);
						SendSucc(playerid, !"РЁС‚СЂР°С„ СЃС‚РѕСЏРЅРєР°, РґРµ РѕСЃС‚Р°РЅРЅС–Р№ СЂР°Р· Р±СѓРІ Р°РІС‚РѕРјРѕР±С–Р»СЊ РїРѕР·РЅР°С‡РµРЅРёР№ РЅР° РєР°СЂС‚С–!");
					}
					else 
					{
						SetPlayerCheckpointEx(playerid, x, y, z, 4.0);
						pTemp[playerid][pGPS] = true;

						SendSucc(playerid, !"Р’Рё РїРѕР·РЅР°С‡РёР»Рё С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р± РЅР° РєР°СЂС‚С–");
					}
						
					pSelectedCar[playerid] = -1;
					give_money(playerid, -300, "РџР»Р°С‚Р° Р·Р° РїРѕР·РЅР°С‡РєСѓ Р°РІС‚Рѕ");
				}
				
				case 1:
				{
					/*if(car_num > 0 && vehicle_player_max_user[playerid] == 1 ||
						car_num > 1 && vehicle_player_max_user[playerid] == 2 ||
						car_num > 3 && vehicle_player_max_user[playerid] == 4 ||
						car_num > 7 && vehicle_player_max_user[playerid] == 8
					)
					{
						pSelectedCar[playerid] = -1;
						SendErr(playerid, !"Р’Р°Рј РЅРµРґРѕСЃС‚СѓРїРЅРёР№ РґР»СЏ Р·Р°РІР°РЅС‚Р°Р¶РµРЅРЅСЏ С–РЅС€РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚!");
						SendErr(playerid, !"Р”Р»СЏ РІРёРєРѕСЂРёСЃС‚Р°РЅРЅСЏ РєС–Р»СЊРєРѕС… РІРёРґС–РІ С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ РїРѕС‚СЂС–Р±РµРЅ РіР°СЂР°Р¶!");
						return show_player_cars(playerid);
					}*/
					
					if(GetPVarIntNew(playerid, "trucker_job") == 1)
					{
						pSelectedCar[playerid] = -1;
						return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");
					}
					
					if(vehicle_player_count_car_load[playerid] > vehicle_player_max_user[playerid])
					{
						pSelectedCar[playerid] = -1;
						show_player_cars(playerid);
						return SendErr(playerid, !"РЎС‚Р°Р»Р°СЃСЏ С‚РµС…РЅС–С‡РЅР° РїРѕРјРёР»РєР°! РљРѕРґ: #102");
					}
					
					if(get_player_veh_status(sql_id) == 1)
					{
						pSelectedCar[playerid] = -1;
						cache_delete(result);
						SetPVarIntNew(playerid, "vehicle_preload_models", models);
						return show_player_vehicle_menu(playerid, sql_id);
					}
					
					new Float: distance = 0.0;
					
					if(vw > 0)
						distance = GetPlayerDistanceFromPoint(playerid,2214.7146,-1967.1420,18.5226);
					else 
						distance = GetPlayerDistanceFromPoint(playerid,x,y,z);
					
					if(floatcmp(distance, 20.0) == 1)
					{
						pSelectedCar[playerid] = -1;
						return SendErr(playerid, !"Р’Рё Р·РЅР°С…РѕРґРёС‚РµСЃСЊ РЅР° Р·Р°РЅР°РґС‚Рѕ РґР°Р»РµРєС–Р№ РІС–РґСЃС‚Р°РЅС– РІС–Рґ РјРёРЅСѓР»РѕС— РїР°СЂРєРѕРІРєРё Р°РІС‚Рѕ");
					}
					
					SendSucc(playerid, !"Р’Рё Р·Р°РІР°РЅС‚Р°Р¶РёР»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±");

					vehicle_player_count_car_load[playerid]++;

					spawn_player_vehicle(playerid, sql_id);
					cache_delete(result);
					pSelectedCar[playerid] = -1;
				}
			}
		}	
		case DIALOG_PLAYER_VEHICLE_LIST:
		{
			if(!response)
			{
				pSelectedCar[playerid] = -1;
				return true;
			}

			if(GetPVarIntNew(playerid, "CarSellStatus"))
			{
				SetPVarIntNew(playerid, "CarSellStatus", false);

				mysql_format(g_sql, GlobalString, sizeof(GlobalString),
					"SELECT * FROM `player_vehicles` WHERE `userid` = '%i'",
					pData[playerid][pMysqlID]);

				mysql_tquery(g_sql, GlobalString, "MYSQL_SellCar", "dd", playerid, listitem);
				return true;	
			}

			// TODO: Р·СЂРѕР±РёС‚Рё РєРµС€СѓРІР°РЅРЅСЏ РЅР° РґР°РЅРѕРјСѓ РµС‚Р°РїС–

			mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT `id` FROM `player_vehicles` WHERE `userid` = '%i'", pData[playerid][pMysqlID]);
			new 
				Cache:result = mysql_query(g_sql, GlobalString, true),
				row_count = 0;

			cache_get_row_count(row_count);
			if(!row_count)
			{
				cache_delete(result);
				return SendErr(playerid, !"РЎС‚Р°Р»Р°СЃСЏ С‚РµС…РЅС–С‡РЅР° РїРѕРјРёР»РєР°! РљРѕРґ: #100");
			}

			new sql_id = 0, models = 0;
			cache_get_value_name_int(listitem, "id", sql_id);
			cache_get_value_name_int(listitem, "model", models);
			cache_delete(result);

			if(get_player_veh_status(sql_id) == 1)
			{
				SetPVarIntNew(playerid, "vehicle_preload_models", models);
				return show_player_vehicle_menu(playerid, sql_id);
			}

			pSelectedCar[playerid] = listitem;
			
			return SPD(playerid, DIALOG_PLAYER_VEHICLE_PANEL, DIALOG_STYLE_LIST, ""LIME_GREEN"РўСЂР°РЅСЃРїРѕСЂС‚", 
				""LIME_GREEN"1."cWH" РџРѕР·РЅР°С‡РёС‚Рё С‚СЂР°РЅСЃРїРѕСЂС‚ РЅР° GPS {00ff00}(300 РіСЂРЅ.)\n\
				"LIME_GREEN"2."cWH" Р—Р°РІР°РЅС‚Р°Р¶РёС‚Рё С‚СЂР°РЅСЃРїРѕСЂС‚", "РћР±СЂР°С‚Рё", "РЎРєР°СЃСѓРІР°С‚Рё");

		}
	    case DIALOG_CAR_CHANGE_PANEL:
	    {
	    	if(!response)
	    		return true;

	    	new 
	    		sql_id = GetPVarIntNew(playerid, "player_vehicle_select_sql");

	    	switch(listitem)
	    	{

			//case 0: return show_player_vehicle_menu(playerid, sql_id);
			case 0:
			{
				if(GetPlayerMoneyEx(playerid) < 300)
				{
					show_player_vehicle_menu(playerid, sql_id);
					return SendErr(playerid, !"РЈ Р’Р°СЃ РЅРµРґРѕСЃС‚Р°С‚РЅСЊРѕ РіСЂРѕС€РµР№ РґР»СЏ РїРѕР·РЅР°С‡РєРё С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ РїРѕ GPS!"); 
				}
					
				new vehicle_id = -1;

				for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
				{
					if(vehicle_player_max_sql[playerid][i] == sql_id)
					{	
					 	vehicle_id = vehicle_player_max[playerid][i];

						break;
					}
				}
						
				if(vehicle_id == -1)
		            return SendErr(playerid, !"РЎС‚Р°Р»Р°СЃСЏ С‚РµС…РЅС–С‡РЅР° РїРѕРјРёР»РєР°! РљРѕРґ: #101");
						
				if(GetVehicleVirtualWorld(vehicle_id))
				{
					pTemp[playerid][pGPS] = true;
					SetPlayerCheckpointEx(playerid, 2214.7146,-1967.1420,18.5226, 4.0);

					SendSucc(playerid, !"РЁС‚СЂР°С„ СЃС‚РѕСЏРЅРєР°, РґРµ Р·РЅР°С…РѕРґРёС‚СЊСЃСЏ Р°РІС‚РѕРјРѕР±С–Р»СЊ РїРѕР·РЅР°С‡РµРЅРѕ РЅР° РєР°СЂС‚С–!");
				}
				else 
				{
					new Float:x, Float:y, Float:z;

					GetVehiclePos(vehicle_id, x, y, z);
							
					SetPlayerCheckpointEx(playerid, x, y, z, 4.0);

					pTemp[playerid][pGPS] = true;

					SendSucc(playerid, !"Р’Рё РїРѕР·РЅР°С‡РёР»Рё С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р± РЅР° РєР°СЂС‚С–");
				}
						
				give_money(playerid, -300, "РџР»Р°С‚Р° Р·Р° РїРѕР·РЅР°С‡РєСѓ Р°РІС‚Рѕ");
			}
				
			case 1: return show_vehicle_info(playerid, sql_id);
				
			case 2:
			{
				if(GetPlayerMoneyEx(playerid) < 1500)
				{
					show_player_vehicle_menu(playerid, sql_id);
					return SendErr(playerid, !"РЈ Р’Р°СЃ РЅРµРґРѕСЃС‚Р°С‚РЅСЊРѕ РіСЂРѕС€РµР№ РґР»СЏ Р±СѓРєСЃРёСЂСѓРІР°РЅРЅСЏ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРѕРіРѕ Р·Р°СЃРѕР±Сѓ!");
				}

			    destroy_player_vehicle_id(playerid, sql_id);
				spawn_player_vehicle(playerid, sql_id);

			    give_money(playerid, -1500, "РЎРїР°РІРЅ С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ");

				return SendSucc(playerid, !"Р’Рё Р·Р°СЂРµСЃРїР°РІРЅРёР»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚РЅРёР№ Р·Р°СЃС–Р±!");
			}
			case 3:
			{
				return show_engine_car_cmd(playerid, sql_id);
			}
				case 4:
				{
					return show_car_docs(playerid, sql_id);
				}
				case 5:
				{
				    PC_EmulateCommand(playerid, "/park");
				}
				case 6:
				{
					destroy_player_vehicle_id(playerid, sql_id);

				    return SendSucc(playerid, !"Р’Рё РІРёРІР°РЅС‚Р°Р¶РёР»Рё Р°РІС‚Рѕ Р· СЃРµСЂРІРµСЂР°!");
				}
		}
	    }

	    case DIALOG_ACCEPT_CAR_FINAL:
	    {
	    	new 
	    		sql_id = GetPVarIntNew(playerid, "player_vehicle_select_sql");

	    	if(!response)
	    		return show_player_vehicle_menu(playerid, sql_id);

	    	sell_car_gos_final(playerid);
	    }
	}
	return true;
}

callback:: remove_player_vehicle_server(playerid)
{

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max[playerid][i] != 0)
		{

			if(CMarketInfo[playerid][mID] == vehicle_player_max[playerid][i])
			{
				stop_sell_car_player(playerid);
			}

			new
				Float:ac_health;

			GetVehicleHealth(vehicle_player_max[playerid][i], ac_health);


		    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
		    	number = '%s',\
		    	lock_status = '%d',\
		    	parking_garage = '%d',\
		    	parking_hotel = '%d',\
		    	shtraf_car = '%d',\
		    	parking_police = '%d',\
		    	energy_car = '%f',\
		    	mileage = '%f',\
		    	fuel = '%f',\
		    	health = '%f',\
		    	consumables_candles = '%f',\
		    	consumables_oil = '%f',\
		    	consumables_brake = '%f',\
		    	consumables_belt = '%f',\
		    	consumables_starter = '%f',\
		    	consumables_generator = '%f',\
		    	consumables_forsunki = '%f',\
		    	consumables_fuel = '%f',\
		    	generator_energy = '%f',\
		    	battery_energy = '%f',\
		    	number_region = '%s',\
		    	number_type = '%d'\
		    	WHERE id = '%d' AND userid = '%d'",

			vehicle[vehicle_player_max[playerid][i]][cPlate],
				vehicle[vehicle_player_max[playerid][i]][cLock],
				vehicle[vehicle_player_max[playerid][i]][parking_garage],
				vehicle[vehicle_player_max[playerid][i]][parking_hotel],
				vehicle[vehicle_player_max[playerid][i]][shtraf_car],
				vehicle[vehicle_player_max[playerid][i]][parking_police],
				vehicle[vehicle_player_max[playerid][i]][cEnergy],
				vehicle[vehicle_player_max[playerid][i]][cMileage],
				vehicle[vehicle_player_max[playerid][i]][cFuel],
				ac_health,
				vehicle[vehicle_player_max[playerid][i]][consumables_candles],
				vehicle[vehicle_player_max[playerid][i]][consumables_oil],
				vehicle[vehicle_player_max[playerid][i]][consumables_brake],
				vehicle[vehicle_player_max[playerid][i]][consumables_belt],
				vehicle[vehicle_player_max[playerid][i]][consumables_starter],
				vehicle[vehicle_player_max[playerid][i]][consumables_generator],
				vehicle[vehicle_player_max[playerid][i]][consumables_forsunki],
				vehicle[vehicle_player_max[playerid][i]][consumables_fuel],


				vehicle[vehicle_player_max[playerid][i]][cGeneratorEnergy],
				vehicle[vehicle_player_max[playerid][i]][cBatteryEnergy],

				vehicle[vehicle_player_max[playerid][i]][cPlateRegion],
				vehicle[vehicle_player_max[playerid][i]][cPlateType],

		    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

			mysql_tquery(g_sql, GlobalString, !"", !"");

			DestroyVehicle(vehicle_player_max[playerid][i]);

			printf("Р’РёРІР°РЅС‚Р°Р¶РµРЅРѕ Р°РІС‚РѕРјРѕР±С–Р»СЊ Р· СЃРµСЂРІРµСЂР°! ID: %d | SQL ID: %d | в„–%d", vehicle_player_max[playerid][i], vehicle_player_max_sql[playerid][i], i);

			vehicle_player_max[playerid][i] = 0;
			vehicle_player_max_sql[playerid][i] = 0;

			vehicle_player_count_car_load[playerid] = 0;
		}
	}

	return true;
}

callback:: destroy_player_vehicle_id(playerid, sql_id)
{
	mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT * FROM `player_vehicles` WHERE `id` = '%i'", sql_id);
	
	new
		Cache:result 	= mysql_query(g_sql, GlobalString, true),
		row_count		= 0;

	cache_get_row_count(row_count);
	if(!row_count)
	{
		cache_delete(result);
		return true;
	}
	cache_delete(result);

	new 
		vehicle_id;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{

		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];

			if(CMarketInfo[playerid][mID] == vehicle_id)
			{
				stop_sell_car_player(playerid);
			}

			new
				Float:ac_health;

			GetVehicleHealth(vehicle_player_max[playerid][i], ac_health);


		    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
		    	number = '%s',\
		    	lock_status = '%d',\
		    	parking_garage = '%d',\
		    	parking_hotel = '%d',\
		    	shtraf_car = '%d',\
		    	parking_police = '%d',\
		    	energy_car = '%f',\
		    	mileage = '%f',\
		    	fuel = '%f',\
		    	health = '%f',\
		    	consumables_candles = '%f',\
		    	consumables_oil = '%f',\
		    	consumables_brake = '%f',\
		    	consumables_belt = '%f',\
		    	consumables_starter = '%f',\
		    	consumables_generator = '%f',\
		    	consumables_forsunki = '%f',\
		    	consumables_fuel = '%f',\
		    	generator_energy = '%f',\
		    	battery_energy = '%f',\
		    	number_region = '%s',\
		    	number_type = '%d'\
		    	WHERE id = '%d' AND userid = '%d'",
		    	
		    	vehicle[vehicle_player_max[playerid][i]][cPlate],
				vehicle[vehicle_player_max[playerid][i]][cLock],
				vehicle[vehicle_player_max[playerid][i]][parking_garage],
				vehicle[vehicle_player_max[playerid][i]][parking_hotel],
				vehicle[vehicle_player_max[playerid][i]][shtraf_car],
				vehicle[vehicle_player_max[playerid][i]][parking_police],
				vehicle[vehicle_player_max[playerid][i]][cEnergy],
				vehicle[vehicle_player_max[playerid][i]][cMileage],
				vehicle[vehicle_player_max[playerid][i]][cFuel],
				ac_health,
				vehicle[vehicle_player_max[playerid][i]][consumables_candles],
				vehicle[vehicle_player_max[playerid][i]][consumables_oil],
				vehicle[vehicle_player_max[playerid][i]][consumables_brake],
				vehicle[vehicle_player_max[playerid][i]][consumables_belt],
				vehicle[vehicle_player_max[playerid][i]][consumables_starter],
				vehicle[vehicle_player_max[playerid][i]][consumables_generator],
				vehicle[vehicle_player_max[playerid][i]][consumables_forsunki],
				vehicle[vehicle_player_max[playerid][i]][consumables_fuel],


				vehicle[vehicle_player_max[playerid][i]][cGeneratorEnergy],
				vehicle[vehicle_player_max[playerid][i]][cBatteryEnergy],

				vehicle[vehicle_player_max[playerid][i]][cPlateRegion],
				vehicle[vehicle_player_max[playerid][i]][cPlateType],

		    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

			mysql_tquery(g_sql, GlobalString, !"", !"");
			DestroyVehicle(vehicle_id);

			vehicle_player_max[playerid][i] = 0;
			vehicle_player_max_sql[playerid][i] = 0;
			vehicle_player_count_car_load[playerid]--;

			break;
		}
	}
	return true;
}

callback:: destroy_player_vehicle_death(playerid, vehicleid)
{
	if(vehicle_player_count_car_load[playerid] == 0)
		return true;

	if(vehicleid == 0 || vehicleid == INVALID_VEHICLE_ID)
		return true;


	new 
		sql_id = vehicle[vehicleid][cOwnTo];


	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{

		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{
		
			if(CMarketInfo[playerid][mID] == vehicleid)
			{
				stop_sell_car_player(playerid);
			}
			new
				Float:ac_health;

			GetVehicleHealth(vehicle_player_max[playerid][i], ac_health);

		    mysql_format(g_sql, GlobalString, sizeof(GlobalString), "UPDATE `player_vehicles` SET \
		    	number = '%s',\
		    	lock_status = '%d',\
		    	parking_garage = '%d',\
		    	parking_hotel = '%d',\
		    	shtraf_car = '%d',\
		    	parking_police = '%d',\
		    	energy_car = '%f',\
		    	mileage = '%f',\
		    	fuel = '%f',\
		    	health = '%f',\
		    	consumables_candles = '%f',\
		    	consumables_oil = '%f',\
		    	consumables_brake = '%f',\
		    	consumables_belt = '%f',\
		    	consumables_starter = '%f',\
		    	consumables_generator = '%f',\
		    	consumables_forsunki = '%f',\
		    	consumables_fuel = '%f',\
		    	generator_energy = '%f',\
		    	battery_energy = '%f',\
		    	number_region = '%s',\
		    	number_type = '%d'\
		    	WHERE id = '%d' AND userid = '%d'",
		    	
		    	vehicle[vehicle_player_max[playerid][i]][cPlate],
				vehicle[vehicle_player_max[playerid][i]][cLock],
				vehicle[vehicle_player_max[playerid][i]][parking_garage],
				vehicle[vehicle_player_max[playerid][i]][parking_hotel],
				vehicle[vehicle_player_max[playerid][i]][shtraf_car],
				vehicle[vehicle_player_max[playerid][i]][parking_police],
				vehicle[vehicle_player_max[playerid][i]][cEnergy],
				vehicle[vehicle_player_max[playerid][i]][cMileage],
				vehicle[vehicle_player_max[playerid][i]][cFuel],
				ac_health,
				vehicle[vehicle_player_max[playerid][i]][consumables_candles],
				vehicle[vehicle_player_max[playerid][i]][consumables_oil],
				vehicle[vehicle_player_max[playerid][i]][consumables_brake],
				vehicle[vehicle_player_max[playerid][i]][consumables_belt],
				vehicle[vehicle_player_max[playerid][i]][consumables_starter],
				vehicle[vehicle_player_max[playerid][i]][consumables_generator],
				vehicle[vehicle_player_max[playerid][i]][consumables_forsunki],
				vehicle[vehicle_player_max[playerid][i]][consumables_fuel],


				vehicle[vehicle_player_max[playerid][i]][cGeneratorEnergy],
				vehicle[vehicle_player_max[playerid][i]][cBatteryEnergy],

				vehicle[vehicle_player_max[playerid][i]][cPlateRegion],
				vehicle[vehicle_player_max[playerid][i]][cPlateType],

		    	vehicle_player_max_sql[playerid][i], pData[playerid][pMysqlID]);

			mysql_tquery(g_sql, GlobalString, !"", !"");

			vehicle_player_max[playerid][i] = 0;
			vehicle_player_max_sql[playerid][i] = 0;


			DestroyVehicle(vehicleid);

			break;
		}
	}
	return true;
}



stock dialog_accept_sell_car_gos(playerid, sql_id)
{
	SetPVarIntNew(playerid, "player_vehicle_select_sql", sql_id);

	SPD(playerid, DIALOG_ACCEPT_CAR_FINAL, DIALOG_STYLE_MSGBOX, !""LIME_GREEN"РџСЂРѕРґР°Р¶ Р°РІС‚Рѕ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ", !"\
	"cWH"Р’Рё РІРїРµРІРЅРµРЅС–, С‰Рѕ С…РѕС‡РµС‚Рµ РїСЂРѕРґР°С‚Рё Р°РІС‚РѕРјРѕР±С–Р»СЊ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ?\n\n\
	Р’Р°Рј Р±СѓРґРµ РїРѕРІРµСЂРЅРµРЅРѕ 80% РІС–Рґ РІР°СЂС‚РѕСЃС‚С–!", !"РўР°Рє", !"РќС–");
	return true;
}

stock sell_car_gos_final(playerid)
{
	new 
		sql_id = GetPVarIntNew(playerid, "player_vehicle_select_sql");

	new 
		vehicle_id, vehicle_i_pos;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];
			vehicle_i_pos = i;
			break;
		}
	}

	new 
		final_money;

	if(vehicle[vehicle_id][vehicle_prize] == -1)
	{
		final_money = floatround(transport_config[GetVehicleModel(vehicle_id)-400][transport_price]*0.8);

		give_money(playerid, final_money, "РџСЂРѕРґР°Р¶ РѕСЃРѕР±РёСЃС‚РѕРіРѕ С‚СЂР°РЅСЃРїРѕСЂС‚Сѓ");
	}

	new 
		query[256];

    format(query, sizeof(query), "DELETE FROM `player_vehicles` WHERE `id` = '%d'", sql_id);
    mysql_tquery(g_sql, query);	

    if(vehicle[vehicle_id][vehicle_prize] == -1)
    {
	    SendSucc(playerid, !"Р’Рё СѓСЃРїС–С€РЅРѕ РїСЂРѕРґР°Р»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ!");
		SendMessage(playerid, -1, "Р’Рё РѕС‚СЂРёРјР°Р»Рё Р· РїСЂРѕРґР°Р¶Сѓ Р°РІС‚РѕРјРѕР±С–Р»СЏ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ %d РіСЂРёРІРµРЅСЊ", final_money);
		
		new text[256];
	    format(text, sizeof(text), "РџСЂРѕРґР°Р¶ Р°РІС‚РѕРјРѕР±С–Р»СЏ SQL ID: %d | SERVER ID: %d | РњР°СЂРєР°: %s РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ %d РіСЂРёРІРµРЅСЊ", sql_id, vehicle_id, transport_config[GetVehicleModel(vehicle_id)-400][transport_name], final_money);
	    logs_vehicle(playerid, pData[playerid][pMysqlID], text);
	}
	else
	{
	    SendSucc(playerid, !"Р’Рё СѓСЃРїС–С€РЅРѕ РїСЂРѕРґР°Р»Рё РѕСЃРѕР±РёСЃС‚РёР№ С‚СЂР°РЅСЃРїРѕСЂС‚ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ!");
		SendMessage(playerid, -1, "Р’Рё РѕС‚СЂРёРјР°Р»Рё Р· РїСЂРѕРґР°Р¶Сѓ Р°РІС‚РѕРјРѕР±С–Р»СЏ РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ 0 РіСЂРёРІРµРЅСЊ, С‚Р°Рє СЏРє С†Рµ Р°РєС†С–Р№РЅРёР№ С‚СЂР°РЅСЃРїРѕСЂС‚!");

		new text[256];
	    format(text, sizeof(text), "РџСЂРѕРґР°Р¶ Р°РєС†С–Р№РЅРѕРіРѕ Р°РІС‚РѕРјРѕР±С–Р»СЏ SQL ID: %d | SERVER ID: %d | РњР°СЂРєР°: %s РІ РґРµСЂР¶.РІР°СЂС‚С–СЃС‚СЊ %d РіСЂРёРІРµРЅСЊ", sql_id, vehicle_id, transport_config[GetVehicleModel(vehicle_id)-400][transport_name], 0);
	    logs_vehicle(playerid, pData[playerid][pMysqlID], text);
	}

    DestroyVehicle(vehicle_id);

	vehicle_player_max_sql[playerid][vehicle_i_pos] = 0;
	vehicle_player_max[playerid][vehicle_i_pos] = 0;

	vehicle_player_count_car_load[playerid]--;

	return true;
}

stock show_vehicle_info(playerid, sql_id)
{

	new 
		vehicle_id;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];

			break;
		}
	}

	new 
		model_car = GetVehicleModel(vehicle_id)-400;

    format(GlobalString, sizeof(GlobalString), "\
        "cGREY"РџСѓРЅРєС‚\t"cGREY"Р†РЅС„РѕСЂРјР°С†С–СЏ\n\
        "LIME_GREEN"- "cWH"РќР°Р№РјРµРЅСѓРІР°РЅРЅСЏ РјРѕРґРµР»С–\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Р”РµСЂР¶.С†С–РЅР° Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"cGR"%d РіСЂРёРІРµРЅСЊ\n\
        "LIME_GREEN"- "cWH"РћР±'С”Рј Р±РµРЅР·РѕР±Р°РєР° Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"cGR"%d Р»С–С‚СЂС–РІ\n\
        "LIME_GREEN"- "cWH"РљР»Р°СЃ Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"РњРѕР¶Р»РёРІС–СЃС‚СЊ РїСЂРѕРґР°Р¶Сѓ\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"РњРѕР¶Р»РёРІС–СЃС‚СЊ С‚Р°РєСЃСѓРІР°С‚Рё\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"РўРёРї РїР°Р»РёРІР°\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"РњР°РєСЃРёРјР°Р»СЊРЅР° С€РІРёРґРєС–СЃС‚СЊ\t"LIME_GREEN"%d KM/Р“", 
        transport_config[model_car][transport_name],
        transport_config[model_car][transport_price],
        transport_config[model_car][transport_tank],
        get_class_veh(model_car),
        (transport_config[model_car][transport_sell_active] == 1) ? (""cGR"Р”РѕСЃС‚СѓРїРЅР°") : (""cLRED"Р’С–РґСЃСѓС‚РЅСЏ"),
        (transport_config[model_car][transport_taxi_active] == 1) ? (""cGR"Р”РѕСЃС‚СѓРїРЅР°") : (""cLRED"Р’С–РґСЃСѓС‚РЅСЏ"),
       	get_fuel_type_veh(model_car),
       	transport_config[model_car][transport_max_speed]);
    return SPD(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"Р†РЅС„РѕСЂРјР°С†С–СЏ РїСЂРѕ Р°РІС‚РѕРјРѕР±С–Р»СЊ", GlobalString, !"РћР±СЂР°С‚Рё", !"Р—Р°РєСЂРёС‚Рё"); 
}

stock show_engine_car_cmd(playerid, sql_id)
{
	new 
		vehicle_id;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];

			break;
		}
	}

	if(GetVehicleModel(vehicle_id) == TYPE_TESLA_1)
		return show_electrocar_engine_cmd(playerid, sql_id);

    format(GlobalString, sizeof(GlobalString), "\
        "cGREY"Р—Р°РїС‡Р°СЃС‚РёРЅР°\t"cGREY"РЎС‚Р°РЅ\t"cGREY"Р”Р°С‚Р° Р·Р°РјС–РЅРё\n\
        "LIME_GREEN"- "cWH"РљС–Р»СЊРєС–СЃС‚СЊ РѕР»РёРІРё\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ СЃРІС–С‡РѕРє\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ РіР°Р»СЊРј\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ СЂРµРјРµРЅС–РІ\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ СЃС‚Р°СЂС‚РµСЂР°\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ РіРµРЅРµСЂР°С‚РѕСЂР°\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ С„РѕСЂСЃСѓРЅРѕРє\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ РЅР°СЃРѕСЃС–РІ\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"\t\n\
        "LIME_GREEN"- "cWH"РџСЂРѕР±С–Рі Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"cGR"%d РєРј", 
        floatround(vehicle[vehicle_id][consumables_oil], floatround_round),
        vehicle[vehicle_id][consumables_candles_date],
        floatround(vehicle[vehicle_id][consumables_candles], floatround_round),
        vehicle[vehicle_id][consumables_oil_date],
		floatround(vehicle[vehicle_id][consumables_brake], floatround_round),
		vehicle[vehicle_id][consumables_brake_date],
		floatround(vehicle[vehicle_id][consumables_belt], floatround_round),
		vehicle[vehicle_id][consumables_belt_date],
		floatround(vehicle[vehicle_id][consumables_starter], floatround_round),
		vehicle[vehicle_id][consumables_starter_date],
		floatround(vehicle[vehicle_id][consumables_generator], floatround_round),
		vehicle[vehicle_id][consumables_generator_date],
		floatround(vehicle[vehicle_id][consumables_forsunki], floatround_round),
		vehicle[vehicle_id][consumables_forsunki_date],
		floatround(vehicle[vehicle_id][consumables_fuel], floatround_round),
		vehicle[vehicle_id][consumables_fuel_date],
		floatround(vehicle[vehicle_id][cMileage], floatround_round));
    return SPD(playerid, DIALOG_ENGINE_STATUS, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"РЎС‚Р°РЅ Р°РІС‚РѕРјРѕР±С–Р»СЏ:", GlobalString, !"РћР±СЂР°С‚Рё", !"Р—Р°РєСЂРёС‚Рё"); 


}

stock show_electrocar_engine_cmd(playerid, sql_id)
{

	new 
		vehicle_id;

	for(new i; i < MAX_PLAYERS_VEHICLE_SL; i++)
	{
		if(vehicle_player_max_sql[playerid][i] == sql_id)
		{	
			vehicle_id = vehicle_player_max[playerid][i];
			break;
		}
	}

    format(GlobalString, sizeof(GlobalString), "\
        "cGREY"Р—Р°РїС‡Р°СЃС‚РёРЅР°\t"cGREY"РЎС‚Р°РЅ\t"cGREY"Р”Р°С‚Р° Р·Р°РјС–РЅРё\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ РіР°Р»СЊРј\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ РіРµРЅРµСЂР°С‚РѕСЂР°\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"РЎС‚Р°РЅ Р±Р°С‚Р°СЂРµС—\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"\t\n\
        "LIME_GREEN"- "cWH"РџСЂРѕР±С–Рі Р°РІС‚РѕРјРѕР±С–Р»СЏ\t"cGR"%d РєРј", 
		floatround(vehicle[vehicle_id][consumables_brake], floatround_round),
		vehicle[vehicle_id][consumables_brake_date],
		floatround(vehicle[vehicle_id][cGeneratorEnergy], floatround_round),
		vehicle[vehicle_id][consumables_generator_date],
		floatround(vehicle[vehicle_id][cBatteryEnergy], floatround_round),
		vehicle[vehicle_id][consumables_fuel_date],
		floatround(vehicle[vehicle_id][cMileage], floatround_round));
    return SPD(playerid, DIALOG_ENGINE_STATUS_ELECTRO, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"РЎС‚Р°РЅ Р°РІС‚РѕРјРѕР±С–Р»СЏ:", GlobalString, !"РћР±СЂР°С‚Рё", !"Р—Р°РєСЂРёС‚Рё"); 

}

CMD:sellcar(playerid) {
	if(GetPVarIntNew(playerid, "trucker_job") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

    new klaus = lox;
    new lox = klaus;
    sex=go;
	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"РќРµРјРѕР¶Р»РёРІРѕ РІРёРєРѕСЂРёСЃС‚РѕРІСѓРІР°С‚Рё РїС–Рґ С‡Р°СЃ СЂРѕР±РѕС‚Рё!");

	SetPVarIntNew(playerid, "CarSellStatus", true);
	show_player_cars(playerid);

	return true;
}