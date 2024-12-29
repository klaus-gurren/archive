new Max_rouleteID = 0; //макс кількість призів
enum PrizCat
{
    rouleteName[120],
    rouleteID,
    rouletePriz
};
new category_name[40][PrizCat];

enum site_prize
{
    sID[15],
    sCategory[15],
    sValue[15],
    sPrice[15]
};
new prize_info[MAX_PLAYERS][site_prize];

new Float:position_spawn_auto_rl[][] =
{
	{496.2794,2258.6084,11.7864,331.0653},
	{491.8055,2260.8484,11.7943,333.1315},
	{487.6313,2263.0676,11.7870,332.1187},
	{483.2168,2265.4224,11.7925,331.1891},
	{478.8703,2267.6929,11.7871,331.8698},
	{474.2588,2270.1711,11.7943,331.1767},
	{470.0360,2272.3164,11.7868,332.5841},
	{466.3938,2265.9226,11.7933,152.0414},
	{470.5729,2263.6736,11.7977,151.6321},
	{475.2416,2261.0933,11.7947,150.7318}
};
cmd:pryz(playerid)
{
    new RouletteMysql[130];
    format(RouletteMysql, sizeof(RouletteMysql), "SELECT * FROM `ucp_drop_roulette` WHERE `p_user` = '%s' AND `p_status` = 0 LIMIT 10", pData[playerid][pNickname]);

    mysql_tquery(g_sql, RouletteMysql, "OnCheckRoulette", "d", playerid);
    return 1;
}
stock LoadRouletteMysql()
{
    mysql_tquery(g_sql, !"SELECT * FROM `ucp_item_roulette` ORDER BY `id`", !"LoadRoulette", !"");
    return 1;
}
callback::LoadRoulette()
{
    cache_get_row_count(Max_rouleteID);
    if(Max_rouleteID)
    {
        for(new i=0; i <= Max_rouleteID; i++)
        {
            cache_get_value_name_int(i, "i_start_rand", category_name[i][rouleteID]);
            cache_get_value_name_int(i, "sell_price", category_name[i][rouletePriz]);
            cache_get_value_name(i, "i_name", category_name[i][rouleteName], 120);
        }
    }
    else 
    {
        print("Error: Помилка загрузки списка призів рулетки!");
    }
    return 1;
}
callback::OnCheckRoulette(playerid)
{
    new fmt_str[164],big_fmt[568];

    new rows;
    cache_get_row_count(rows);

    if(rows)
    {
        for(new i=0; i < rows; i++)
        {
            cache_get_value_name_int(i, "p_id", prize_info[playerid][sCategory][i]); 
            cache_get_value_name_int(i, "p_value", prize_info[playerid][sValue][i]);
            cache_get_value_name_int(i, "p_number", prize_info[playerid][sID][i]);
            
            new vlrl = ValidRoulette(playerid, i);
            if(vlrl != -1)
            {
                prize_info[playerid][sPrice][i] = category_name[vlrl][rouletePriz];
                if(prize_info[playerid][sCategory][i] < 3) format(fmt_str, sizeof(fmt_str), "{ffffff}%d. %s(%d)\n",i+1, category_name[vlrl][rouleteName], prize_info[playerid][sValue][i]);
                else format(fmt_str, sizeof(fmt_str), "{ffffff}%d. %s(id:%d)\n",i+1, category_name[vlrl][rouleteName], prize_info[playerid][sValue][i]);
                strcat(big_fmt, fmt_str);
            }
            else
            {
                printf("Error: помилка загрузки рулетки %s. Причина: невідомий ID приза", pData[playerid][pNickname]);
                return SendClientMessage(playerid, -1, "Помилка! Зверніться на форум проекта!");
            }
        }
        OpenDialog(playerid,
		    "Dialog_Roulete", DIALOG_STYLE_LIST,
			!"Рулетка",
            big_fmt,
			!"Обрати", !"Закрити"
		);
    }
    else SendClientMessage(playerid, -1, "Призів не знайдено!");
    return 1;
}
stock ValidRoulette(playerid, id)
{
    for(new d = 0; d < Max_rouleteID; d++)
    {
        if(prize_info[playerid][sCategory][id] == 1) return 0;
        if(prize_info[playerid][sCategory][id] == 2) return 1;
        if(category_name[d][rouleteID] == prize_info[playerid][sValue][id])
        {
            return d;
        }
    }
    return -1;
}
DialogResponse:Dialog_Roulete(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;
    SetPVarInt(playerid, "prize_id", listitem);
    new strprize[218];

    switch(prize_info[playerid][sCategory][listitem])
    {
        case 1:
        {
            format(strprize, sizeof(strprize), "Вы успішно забрали свій приз {ffff00}%d донат-коїнів", prize_info[playerid][sValue][listitem]);
            SendSucc(playerid, strprize);
            user_data[playerid][pDonate] += prize_info[playerid][sValue][listitem];
            UpdatePlayerIntData(playerid, "donate", user_data[playerid][pDonate]);
           
            mysql_tquery_s(g_sql, str_format("UPDATE `ucp_drop_roulette` SET `p_status` = 1 WHERE `p_number` = '%d'", prize_info[playerid][sID][listitem]));
            return 1;
        }
        case 2:
        {
            format(strprize, sizeof(strprize), "Ви успішно забрали свій приз {ffff00}%d ігрової валюти",prize_info[playerid][sValue][listitem]);
            SendSucc(playerid, strprize);
            give_money(playerid, prize_info[playerid][sValue][listitem], "Забрав приз із рулетки");
          
            mysql_tquery_s(g_sql, str_format("UPDATE `ucp_drop_roulette` SET `p_status` = 1 WHERE `p_number` = '%d'", prize_info[playerid][sID][listitem]));
            return 1;
        }
        case 3: format(strprize, sizeof(strprize), "{ffffff}Ви дійсно хочете продати цей автомобіль (id:%d) за {ffff00}%d M-Coins?{ffffff}\n Якщо ні нажміть кнопку {ffff00}'Забрати'{ffffff}\n Увага! Цю дію скасувати не можна!", prize_info[playerid][sValue][listitem], prize_info[playerid][sPrice][listitem]);
        case 4: format(strprize, sizeof(strprize), "{ffffff}Ви дійсно хочете продати цей скін (id:%d) за {ffff00}%d M-Coins?{ffffff}\n Якщо ні нажміть кнопку {ffff00}'Забрати'{ffffff}\n Увага! Цю дію скасувати не можна! \nСкін що наразі знаходиться на вас буде замінено!!!", prize_info[playerid][sValue][listitem], prize_info[playerid][sPrice][listitem]);
    }
    OpenDialog(playerid,

		    "Dialog_Roulete_Sell", DIALOG_STYLE_MSGBOX,
			!"Рулетка",
            strprize,
			!"Забрати", !"Продати"
		);
    return 1;
}
DialogResponse:Dialog_Roulete_Sell(playerid, response, listitem, inputtext[])
{
    new list_id = GetPVarInt(playerid, "prize_id"), fmt_str[168];
    if(response)
    {
        switch(prize_info[playerid][sCategory][list_id])
        {
            case 3:
            {
                mysql_format(g_sql, GlobalString, sizeof(GlobalString), "SELECT userid FROM player_vehicles WHERE userid = '%d' LIMIT 8", pData[playerid][pMysqlID]);

			    new Cache:carfind = mysql_query(g_sql, GlobalString, true), all_vehicle_player = 0;
			    cache_get_row_count(all_vehicle_player);
			    cache_delete(carfind);
			
			    if(all_vehicle_player >= vehicle_player_max_user[playerid]) return SendErr(playerid, !"Перевищено ліміт слотів авто, звільніть слот під приз!");
			    mysql_tquery_s(g_sql, str_format("UPDATE `ucp_drop_roulette` SET `p_status` = 1 WHERE `p_number` = '%d'", prize_info[playerid][sID][list_id]));
                return RouletteCar(playerid, prize_info[playerid][sValue][list_id]);
            }
            case 4:
            {
                format(fmt_str, sizeof(fmt_str), "Ви успішно забрали свій приз {ffff00}Одяг №%d",prize_info[playerid][sValue][list_id]);
                pData[playerid][pSkin] = prize_info[playerid][sValue][list_id];
                UpdatePlayerIntData(playerid, "skin", pData[playerid][pSkin]);
                SetPlayerSkin(playerid, pData[playerid][pSkin]);
            }
        }
        SendSucc(playerid, fmt_str);
        
        mysql_tquery_s(g_sql, str_format("UPDATE `ucp_drop_roulette` SET `p_status` = 1 WHERE `p_number` = '%d'", prize_info[playerid][sID][list_id]));
        return 1;
    }
    else
    {
        user_data[playerid][pDonate] += prize_info[playerid][sPrice][list_id];
        UpdatePlayerIntData(playerid, "donate", user_data[playerid][pDonate]);
        
        format(fmt_str, sizeof(fmt_str), "Ви успішно продали свій приз за %d Донат-коїнів", prize_info[playerid][sPrice][list_id]);
        SendSucc(playerid, fmt_str);
        mysql_tquery_s(g_sql, str_format("UPDATE `ucp_drop_roulette` SET `p_status` = 1 WHERE `p_number` = '%d'", prize_info[playerid][sID][list_id]));
    }
    return 1;
}
stock RouletteCar(const playerid, const car)
{
    new random_pos = random(sizeof position_spawn_auto_rl);
    
	new Float:xPriz = position_spawn_auto_rl[random_pos][0],
	    Float:yPriz = position_spawn_auto_rl[random_pos][1],
	    Float:zPriz = position_spawn_auto_rl[random_pos][2],
	    Float:aPriz = position_spawn_auto_rl[random_pos][3];


	mysql_format(g_sql, GlobalString,sizeof GlobalString, "INSERT INTO `player_vehicles` \
				(`userid`,`model`,`color_1`,`color_2`, `parking_x`,`parking_y`,`parking_z`,`parking_a`) \
					VALUES \
				('%d','%d','%d','%d','%f','%f','%f','%f')",
			pData[playerid][pMysqlID], car, 0, 0,
			xPriz, yPriz, zPriz, aPriz
		);
	mysql_tquery(g_sql, GlobalString, !"", !"");

    SendSucc(playerid, !"Вітаю! Ви успвшно забрали свій автомобіль із рулетки!");
    SendInf(playerid, !"Автомобіль буде припаркований на штраф стоянці!");
	return 1;
}