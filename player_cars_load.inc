
new pSelectedCar[MAX_PLAYERS] = {-1,...};

CMD:car(playerid)
{
	if(GetPVarIntNew(playerid, "trucker_job") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	show_player_cars(playerid);

	return true;
}

CMD:park(playerid, params[])
{

	if(!get_player_in_p_car(playerid))
		return SendErr(playerid, !"Ви повинні сидіти в особистому транспорті!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(pGreenZone{playerid})
		return SendErr(playerid, !"Заборонено паркувати особистий транспорт у Зеленій Зоні!");

	if(GetPVarIntNew(playerid, "cooldown_park_car") > gettime())
		return SendErr(playerid, !"Паркувати транспортний засіб можна раз на 1 хвилину!");

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

				SendSucc(playerid, !"Ви перепаркували особистий транспортний засіб");
				break;
			}
		}
	}
	else
	{
		if(!GetPVarIntNew(playerid, "player_in_parking"))
			return SendErr(playerid, !"Оскільки у Вас немає майна, припаркувати автомобіль можна тільки на паркінгу!");

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

				SendSucc(playerid, !"Ви перепаркували особистий транспортний засіб");
				break;
			}
		}		
	}

	SendInf(playerid, !"Ви успішно припаркували свій транспортний засіб!");
	SendInf(playerid, !"Тепер при вході він буде з'являтися на цьому місці!");	

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
			"cWH"Назва: "LIME_GREEN"%s\n\n\
			"cWH"Модель: "LIME_GREEN"%d\n\
			"cWH"Стан: "LIME_GREEN"%d\n\
			"cWH"Пробіг: "LIME_GREEN"%d\n\
			"cWH"Паливо: "LIME_GREEN"%f\n\
			"cWH"Колір: "LIME_GREEN"ID %d, %d\n\
			"cWH"Держ.вартість: "LIME_GREEN"%d\n\
			"cWH"Номерні знаки: "LIME_GREEN"%s %s\n\
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
			format(string, sizeof string, ""LIME_GREEN"Документи на ТЗ №%d", sql_id); 
			SPD(playerid, 0x0, DIALOG_STYLE_MSGBOX, string, GlobalString, "Закрити", "");
			
			break;
		}
	}
	return 1;
}

// TODO: рефактор всіх Cache функцій
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
		return SendErr(playerid, !"Транспорт не знайдено"), SetPVarIntNew(playerid, "CarSellStatus", false);
	}

	new 
		sql_id, 
		modelid,
		tempcarData,
		tempunixData;

	format(GlobalString, sizeof(GlobalString), ""cGREY"Транспорт\t"cGREY"Стан\t"cGREY"Термін дії\n");

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

			if(gettime() < tempunixData) format(vehicleStatus, sizeof(vehicleStatus), ""cGR"[%dр.%dм.%dд %dг. %dх.]", year, month, day, hour, minute);
			else format(vehicleStatus, sizeof(vehicleStatus), ""cRED"[%dр.%dм.%dд %dг. %dх.]", year, month, day, hour, minute);
		}
		else format(vehicleStatus, sizeof(vehicleStatus), ""LIME_GREEN"[Без терміну дії]");

		format(GlobalString, sizeof(GlobalString), "%s"LIME_GREEN"%s\t"cGREY"%s\t%s\n",
			GlobalString, transport_config[modelid-400][transport_name],
			get_player_veh_status(sql_id) == 1 ? (""cGR"[Завантажено]") : (""cLRED"[Не завантажено]"),
			vehicleStatus);
	}

	SPD(playerid, DIALOG_PLAYER_VEHICLE_LIST, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"Особистий транспорт", GlobalString, !"Обрати", !"Закрити");

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

//тут
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
    format(text_mark, sizeof(text_mark), ""cWH"Особистий транспорт "LIME_GREEN"%s[%d]", transport_config[GetVehicleModel(vehicle_id)-400][transport_name], GetPVarIntNew(playerid, "player_vehicle_select_sql"));

	SPD(playerid, DIALOG_CAR_CHANGE_PANEL, DIALOG_STYLE_TABLIST_HEADERS, text_mark, "\
	    "cGREY"Пункт\t"cGREY"Дія\n\
	    "LIME_GREEN"1. "cWH"Позначити транспорт на GPS\t"cGR"300 гривень\n\
	    "LIME_GREEN"2. "cWH"Інформація про транспорт\t"LIME_GREEN"Вивчити\n\
	    "LIME_GREEN"3. "cWH"Буксирування транспорту в гараж\t"cGR"1500 гривень\n\
	    "LIME_GREEN"4. "cWH"Стан автомобіля\t"cGR"Вивчити\n\
		"LIME_GREEN"5. "cWH"Документи на транспорт\t"cGR"Вивчити\n\
	    "LIME_GREEN"6. "cWH"Припаркувати транспорт\t\n\
		"LIME_GREEN"7. "cWH"Вивантажити автомобіль з сервера", !"Обрати", !"Закрити");		

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

	if(tempcarstatus) return SendErr(playerid, !"Ви не можете продати тимчасовий транспортний засіб!");

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
				return SendErr(playerid, !"Сталася технічна помилка! Код: #100");
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
						return SendErr(playerid, !"У Вас недостатньо грошей для позначки транспорту по GPS!"); 
					}
					
					if(vw > 0)
					{
						pTemp[playerid][pGPS] = true;
						
						SetPlayerCheckpointEx(playerid, 2214.7146,-1967.1420,18.5226, 4.0);
						SendSucc(playerid, !"Штраф стоянка, де останній раз був автомобіль позначений на карті!");
					}
					else 
					{
						SetPlayerCheckpointEx(playerid, x, y, z, 4.0);
						pTemp[playerid][pGPS] = true;

						SendSucc(playerid, !"Ви позначили транспортний засіб на карті");
					}
						
					pSelectedCar[playerid] = -1;
					give_money(playerid, -300, "Плата за позначку авто");
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
						SendErr(playerid, !"Вам недоступний для завантаження інший транспорт!");
						SendErr(playerid, !"Для використання кількох видів транспорту потрібен гараж!");
						return show_player_cars(playerid);
					}*/
					
					if(GetPVarIntNew(playerid, "trucker_job") == 1)
					{
						pSelectedCar[playerid] = -1;
						return SendErr(playerid, !"Неможливо використовувати під час роботи!");
					}
					
					if(vehicle_player_count_car_load[playerid] > vehicle_player_max_user[playerid])
					{
						pSelectedCar[playerid] = -1;
						show_player_cars(playerid);
						return SendErr(playerid, !"Сталася технічна помилка! Код: #102");
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
						return SendErr(playerid, !"Ви знаходитесь на занадто далекій відстані від минулої парковки авто");
					}
					
					SendSucc(playerid, !"Ви завантажили особистий транспортний засіб");

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

			// TODO: зробити кешування на даному етапі

			mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT `id` FROM `player_vehicles` WHERE `userid` = '%i'", pData[playerid][pMysqlID]);
			new 
				Cache:result = mysql_query(g_sql, GlobalString, true),
				row_count = 0;

			cache_get_row_count(row_count);
			if(!row_count)
			{
				cache_delete(result);
				return SendErr(playerid, !"Сталася технічна помилка! Код: #100");
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
			
			return SPD(playerid, DIALOG_PLAYER_VEHICLE_PANEL, DIALOG_STYLE_LIST, ""LIME_GREEN"Транспорт", 
				""LIME_GREEN"1."cWH" Позначити транспорт на GPS {00ff00}(300 грн.)\n\
				"LIME_GREEN"2."cWH" Завантажити транспорт", "Обрати", "Скасувати");

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
					return SendErr(playerid, !"У Вас недостатньо грошей для позначки транспорту по GPS!"); 
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
		            return SendErr(playerid, !"Сталася технічна помилка! Код: #101");
						
				if(GetVehicleVirtualWorld(vehicle_id))
				{
					pTemp[playerid][pGPS] = true;
					SetPlayerCheckpointEx(playerid, 2214.7146,-1967.1420,18.5226, 4.0);

					SendSucc(playerid, !"Штраф стоянка, де знаходиться автомобіль позначено на карті!");
				}
				else 
				{
					new Float:x, Float:y, Float:z;

					GetVehiclePos(vehicle_id, x, y, z);
							
					SetPlayerCheckpointEx(playerid, x, y, z, 4.0);

					pTemp[playerid][pGPS] = true;

					SendSucc(playerid, !"Ви позначили транспортний засіб на карті");
				}
						
				give_money(playerid, -300, "Плата за позначку авто");
			}
				
			case 1: return show_vehicle_info(playerid, sql_id);
				
			case 2:
			{
				if(GetPlayerMoneyEx(playerid) < 1500)
				{
					show_player_vehicle_menu(playerid, sql_id);
					return SendErr(playerid, !"У Вас недостатньо грошей для буксирування транспортного засобу!");
				}

			    destroy_player_vehicle_id(playerid, sql_id);
				spawn_player_vehicle(playerid, sql_id);

			    give_money(playerid, -1500, "Спавн транспорту");

				return SendSucc(playerid, !"Ви зареспавнили особистий транспортний засіб!");
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

				    return SendSucc(playerid, !"Ви вивантажили авто з сервера!");
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

			printf("Вивантажено автомобіль з сервера! ID: %d | SQL ID: %d | №%d", vehicle_player_max[playerid][i], vehicle_player_max_sql[playerid][i], i);

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

	SPD(playerid, DIALOG_ACCEPT_CAR_FINAL, DIALOG_STYLE_MSGBOX, !""LIME_GREEN"Продаж авто в держ.вартість", !"\
	"cWH"Ви впевнені, що хочете продати автомобіль в держ.вартість?\n\n\
	Вам буде повернено 80% від вартості!", !"Так", !"Ні");
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

		give_money(playerid, final_money, "Продаж особистого транспорту");
	}

	new 
		query[256];

    format(query, sizeof(query), "DELETE FROM `player_vehicles` WHERE `id` = '%d'", sql_id);
    mysql_tquery(g_sql, query);	

    if(vehicle[vehicle_id][vehicle_prize] == -1)
    {
	    SendSucc(playerid, !"Ви успішно продали особистий транспорт в держ.вартість!");
		SendMessage(playerid, -1, "Ви отримали з продажу автомобіля в держ.вартість %d гривень", final_money);
		
		new text[256];
	    format(text, sizeof(text), "Продаж автомобіля SQL ID: %d | SERVER ID: %d | Марка: %s в держ.вартість %d гривень", sql_id, vehicle_id, transport_config[GetVehicleModel(vehicle_id)-400][transport_name], final_money);
	    logs_vehicle(playerid, pData[playerid][pMysqlID], text);
	}
	else
	{
	    SendSucc(playerid, !"Ви успішно продали особистий транспорт в держ.вартість!");
		SendMessage(playerid, -1, "Ви отримали з продажу автомобіля в держ.вартість 0 гривень, так як це акційний транспорт!");

		new text[256];
	    format(text, sizeof(text), "Продаж акційного автомобіля SQL ID: %d | SERVER ID: %d | Марка: %s в держ.вартість %d гривень", sql_id, vehicle_id, transport_config[GetVehicleModel(vehicle_id)-400][transport_name], 0);
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
        "cGREY"Пункт\t"cGREY"Інформація\n\
        "LIME_GREEN"- "cWH"Найменування моделі\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Держ.ціна автомобіля\t"cGR"%d гривень\n\
        "LIME_GREEN"- "cWH"Об'єм бензобака автомобіля\t"cGR"%d літрів\n\
        "LIME_GREEN"- "cWH"Клас автомобіля\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Можливість продажу\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Можливість таксувати\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Тип палива\t"LIME_GREEN"%s\n\
        "LIME_GREEN"- "cWH"Максимальна швидкість\t"LIME_GREEN"%d KM/Г", 
        transport_config[model_car][transport_name],
        transport_config[model_car][transport_price],
        transport_config[model_car][transport_tank],
        get_class_veh(model_car),
        (transport_config[model_car][transport_sell_active] == 1) ? (""cGR"Доступна") : (""cLRED"Відсутня"),
        (transport_config[model_car][transport_taxi_active] == 1) ? (""cGR"Доступна") : (""cLRED"Відсутня"),
       	get_fuel_type_veh(model_car),
       	transport_config[model_car][transport_max_speed]);
    return SPD(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"Інформація про автомобіль", GlobalString, !"Обрати", !"Закрити"); 
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
        "cGREY"Запчастина\t"cGREY"Стан\t"cGREY"Дата заміни\n\
        "LIME_GREEN"- "cWH"Кількість оливи\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан свічок\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан гальм\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан ременів\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан стартера\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан генератора\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан форсунок\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан насосів\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"\t\n\
        "LIME_GREEN"- "cWH"Пробіг автомобіля\t"cGR"%d км", 
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
    return SPD(playerid, DIALOG_ENGINE_STATUS, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"Стан автомобіля:", GlobalString, !"Обрати", !"Закрити"); 


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
        "cGREY"Запчастина\t"cGREY"Стан\t"cGREY"Дата заміни\n\
        "LIME_GREEN"- "cWH"Стан гальм\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан генератора\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"- "cWH"Стан батареї\t"cGR"%d%%\t"cWH"%s\n\
        "LIME_GREEN"\t\n\
        "LIME_GREEN"- "cWH"Пробіг автомобіля\t"cGR"%d км", 
		floatround(vehicle[vehicle_id][consumables_brake], floatround_round),
		vehicle[vehicle_id][consumables_brake_date],
		floatround(vehicle[vehicle_id][cGeneratorEnergy], floatround_round),
		vehicle[vehicle_id][consumables_generator_date],
		floatround(vehicle[vehicle_id][cBatteryEnergy], floatround_round),
		vehicle[vehicle_id][consumables_fuel_date],
		floatround(vehicle[vehicle_id][cMileage], floatround_round));
    return SPD(playerid, DIALOG_ENGINE_STATUS_ELECTRO, DIALOG_STYLE_TABLIST_HEADERS, !""LIME_GREEN"Стан автомобіля:", GlobalString, !"Обрати", !"Закрити"); 

}

CMD:sellcar(playerid) {
	if(GetPVarIntNew(playerid, "trucker_job") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	if(GetPVarIntNew(playerid, "active_player_gruz_taxi_p") == 1)
		return SendErr(playerid, !"Неможливо використовувати під час роботи!");

	SetPVarIntNew(playerid, "CarSellStatus", true);
	show_player_cars(playerid);

	return true;
}