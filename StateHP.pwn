enum pInfo
{
    Float:HP
}
new klaus[MAX_PLAYERS][pInfo];

public OnPlayerDisconnect(playerid, reason)
{
	GetPlayerHealth(playerid, klaus[playerid][HP]); //записую рівень HP
	//збереження в базу даних
	return 1;
}

public OnPlayerConnect(playerid)
{
    //загрузка із бд в змінну
    return 1;
}
public OnPlayerSpawn(playerid)
{
	SetPlayerHealth(playerid, klaus[playerid][HP]);
	if(klaus[playerid][HP] < 10 && klaus[playerid][HP] != 0) SendClientMessage(playerid, -1, "Підказка | У вас мало здоров'я, використайте аптечку або зверніться в лікарню!");
        if(klaus[playerid][HP] == 0)
        {
    	    SetPlayerHealth(playerid, 1);
	    //спавн в лікарні
        }
	else
	{
		//код відновлення на місце виходу/звичайний спавн
	}
	return 1;
}
