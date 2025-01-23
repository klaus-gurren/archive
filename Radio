enum Radio
{
    UrlStations[64],
    NameStations[30]
};
new const radioUA[3][Radio] = {
    {"", ""}, //Null
    {"http://radio.ukr.radio:8000/ur2-mp3-m", "Радіо Промінь"},
    {"http://online.z-polus.info/hq", "Радіо Західний Полюс"}
};
new bool:OnRadio[MAX_PLAYERS];

CMD:radio(playerid, params[])
{
    if(OnRadio[playerid])
    {
        StopAudioStreamForPlayer(playerid);
        SendClientMessage(playerid, 0xFFFF00FF, "[Radio]: Радіо вимкнено!");
        return OnRadio[playerid] = false;
    }
    
    new id;
    if(sscanf(params, "d", id)) return SendClientMessage(playerid, 0xFFFF00FF, "[Radio]: Використовуйте: /radio | 1 | 2 ..]");
    if(id > sizeof(radioUA) -1 || id == 0) return SendClientMessage(playerid, 0xFFFF00FF, "Не вірний номер станції, або станції не існує");
    
    new string[80];
    PlayAudioStreamForPlayer(playerid, radioUA[id][UrlStations]);
    format(string, sizeof(string), "[Radio]: Ви увімкнули %s!", radioUA[id][NameStations]);
    SendClientMessage(playerid, 0x00FF00FF, string);
    
    SendClientMessage(playerid, -1, "Для вимкнення радіо ведіть команду повторно");
    OnRadio[playerid] = true;
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    OnRadio[playerid] = false;
    return 1;
}
