enum pInfo
{
    Float:HP
}
new klaus[MAX_PLAYERS][pInfo];

public OnPlayerDisconnect(playerid, reason)
{
	GetPlayerHealth(playerid, klaus[playerid][HP]); //записую рівень HP
	//зберегти в базу даних
	return 1;
}

public OnPlayerConnect(playerid)
{
	SetPlayerHealth(playerid, klaus[playerid][HP]);
	if(klaus[playerid][HP] < 10) { //Якщо менше 10 ХП
		//спавн в лікарні
	}
	else
	{
		//код відновлення на місце виходу
	}
	return 1;
}
