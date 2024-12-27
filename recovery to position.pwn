enum AfterDeath
{
    Float:X,
    Float:Y,
    Float:Z
}
new klaus[MAX_PLAYERS][AfterDeath];

public OnPlayerDisconnect(playerid, reason)
{ //калбек при відключенні від сервера

    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED) //якщо гравець в стані смерті
    {
        klaus[playerid][X] = 0.0; //присвоюю змінним нульові координати
        klaus[playerid][Y] = 0.0;
        klaus[playerid][Z] = 0.0;
        print("Вийшов під час смерті, координати не збережено");
    }
    else //якщо не під час смерті зберігаю координати
    {
        GetPlayerPos(playerid, klaus[playerid][X], klaus[playerid][Y], klaus[playerid][Z]);
        print("координати збережено");
    }
    return 1;
}

public OnPlayerSpawn(playerid)
{
    //При спавні, після авторизації
    if(klaus[playerid][X] + klaus[playerid][Y] + klaus[playerid][Z] != 0.0)//якщо координати не нульові
    {
        //функціонал відновлення, в прикладі тп
        SetPlayerPos(playerid, klaus[playerid][X] ,klaus[playerid][Y],klaus[playerid][Z]); //приклад телепорт на тіж координати
        print("По координатах відновлено");
    }
    else { /* звичайний спавн */ }
    return 1;
}
