enum pInfo
{
    Float:HP 
};
new klaus[MAX_PLAYERS][pInfo];

public OnPlayerDisconnect(playerid, reason)
{
	GetPlayerHealth(playerid, klaus[playerid][HP]);
	//save mysql
	return 1;
}

public OnPlayerConnect(playerid)
{
    //loading mysql
    return 1;
}
public OnPlayerSpawn(playerid)
{
    if(klaus[playerid][HP] == 0)
    {
        SetPlayerHealth(playerid, 1);
        return //spawn hospitals;
    }
    if(klaus[playerid][HP] < 10 && klaus[playerid][HP] != 0) SendClientMessage(playerid, -1, "Підказка | У вас мало здоров'я, використайте аптечку або зверніться в лікарню!");
	//код відновлення на місце виходу/звичайний спавн
    SetPlayerHealth(playerid, klaus[playerid][HP]);
    return 1;
}
