/*
	{F81414} - червоний
	{FFFFFF} -  білий, -1
	{FFFF00} - жовтий
*/

public OnPlayerDeath(playerid, killerid, reason) //В калбек який викликається після смерті персонажа
{
	if(killerid != INVALID_PLAYER_ID) //перевірка щоб не спрацьовувало якщо гравець вбив сам себе.
	{
		killinfo(playerid, killerid); //для зручності та оптимальності створив сток, викликаємо його.
	}
    return 1;
}
stock killinfo(playerid, killerid) //сам сток, аргументи: playerid - жертва, killerid - вбивця
{
    new string[62+(-6+MAX_PLAYER_NAME +3 +26)+1], weapon_name[27]; //створюємо відмінні для зберігання текста, для мінімального споживання памяті підрахував макс.розмір символів
	
    new year, month, day, hour, minuite; //створюємо відмінні для зберігання дати та часу
    getdate(year, month, day); //дізнаємось дату та записуємо в змінні
    gettime(hour, minuite); //дізнаємось час та записуємо

    new nick[MAX_PLAYER_NAME +1], weapon = GetPlayerWeapon(killerid); //перевіряємо яка зброя в руках в killerid та зберігаємо ID в змінну. (можна і напряму, але для зручності створюю)
    GetPlayerName(playerid,nick,sizeof(nick));

    switch(weapon) //Оператором перевіряємо число в змінні, тобто id зброї, з якої здійснено вбивство.
    {
        case 1: weapon_name = "Кастета"; //якщо weapon == 1 записуємо текст в лапках в weapon_name, нижче т/п.
        case 2: weapon_name = "Клюшки для гольфа";
        case 3: weapon_name = "Поліцейської дубинки";
        case 4: weapon_name = "Ножа";
        case 5: weapon_name = "Бейсбольної бити";
        case 6: weapon_name = "Лопати";
        case 7: weapon_name = "Більярдного кия";
        case 8: weapon_name = "Катани";
        case 9: weapon_name = "Бензопили";
        case 10: weapon_name = "Великого дилдо";
        case 11: weapon_name = "Малого дилдо";
        case 12: weapon_name = "Великого вібратора";
        case 13: weapon_name = "Малого вібратора";
        case 14: weapon_name = "Квітів";
        case 15: weapon_name = "Тростя";
        case 16: weapon_name = "Гранати";
        case 17: weapon_name = "Сльозоточивого газу";
        case 18: weapon_name = "Коктеля молотова";
        case 22: weapon_name = "Кольта.45";
        case 23: weapon_name = "Кольта.45 з глушителем";
        case 24: weapon_name = "Desert Eagle";
        case 25: weapon_name = "Дробовика";
        case 26: weapon_name = "Обріза";
        case 27: weapon_name = "Дробовика SPAS-12";
        case 28: weapon_name = "Микро-Узи";
        case 29: weapon_name = "MP5";
        case 30: weapon_name = "АК-47";
        case 31: weapon_name = "M4";
        case 32: weapon_name = "TEC-9";
        case 33: weapon_name = "Гвинтівки";
        case 34: weapon_name = "Снайперскої гвинтівки";
        case 35: weapon_name = "Гранатомета";
        case 36: weapon_name = "Самонаводящого гранатомета";
        case 37: weapon_name = "Вогнемета";
        case 38: weapon_name = "Мінігана";
        case 39: weapon_name = "Взривчатки";
        case 40: weapon_name = "Детонатора";
        case 41: weapon_name = "Балончика з краскою";
        case 42: weapon_name = "Вогнетушителя";
	default: weapon_name = "Кулаків";
    }
    format(string, sizeof(string), "Ви були вбиті гравцем {F81414}%s[%d]. {FFFFFF}За допомогою: %s", nick, playerid, weapon_name); //форматуємо сам текст
    SendClientMessage(playerid, -1, string); //Відправляємо текст в чат playerid
		
    format(string, sizeof(string), "Час смерті {FFFF00}%02d:%02d | {FFFFFF}Дата: {FFFF00}%02d.%02d.%d", hour, minuite, day, month, year);
    SendClientMessage(playerid, -1, string);
    return 1;
}
