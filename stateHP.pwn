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

public OnPlayerSpawn(playerid)
{
	SetPlayerHealth(playerid, klaus[playerid][HP]);
	if(klaus[playerid][HP] < 10) { //Якщо менше 10 ХП
		//спавн в лікарні + видава 1HP, щоб не помирав по 100 раз якщо hp == 0)
                SetPlayerHealth(playerid, 1); 
	}
	else
	{
		//код відновлення на місце виходу/звичайний спавн
	}
	return 1;
}
