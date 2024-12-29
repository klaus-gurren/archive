/*Приклад написаний на MysQL v.39, тому деякі запити можуть відрізнятись від новіших версій*/

//номерація діалогів  чисто для знучності
#define DIALOG_NONE    0
#define AUTO_SEARCH    1
#define AUTO_SEARCH_EMAIL    2
#define RESTORE    3

//В систему перевірки твінків, в момент, якщо було знайдено 2+ twink, чи як там по іншому реалізована система.
    SendClientMessage(playerid, -1, "Ви вже зареєстрували декілька аккаунтів!"); //відправив повідомлення в чат
    
    new klaus[] = "{FFFFFF}Вами було зареєстровано більше 2-х аккаунтів\n\
	          Правилами сервера це {F81414}заборонено!\n\
		  {FFFFFF}Ведіть в лаунчері Nick_Name уже зареєстрованого вами аккаунта\n\
		  Якщо забули ігровий нік натисніть {FFFF00}відновити"; //для прикладу текстова змінна
	
    ShowPlayerDialog(playerid, RESTORE, DIALOG_STYLE_MSGBOX, "Примітка", klaus, "Відновити", "Закрити"); //в прикладі показую сам діалог гравцю


public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) //В паблік роботи із діалогами
{
	case RESTORE: //функція діалога
	{
		if(!response) return Kick(playerid); //якщо натиснув закрити кік
		ShowPlayerDialog(playerid, AUTO_SEARCH, DIALOG_STYLE_LIST, "Відновлення аккаунта", "1. Пошук по Email пошті\n 2. Автоматичний пошук", "Вибрати", "Закрити");
	}
	case AUTO_SEARCH: 
	{
	    if(!response) return Kick(playerid);
		switch(listitem) //оперетором перевіряю який пункт вибрано
		{
			case 0:
			{
				ShowPlayerDialog(playerid, AUTO_SEARCH_EMAIL, DIALOG_STYLE_INPUT, "Відновлення аккаунта", "Ведіть адресу електронної пошти\nЯка була привязана до вашого ігового аккаунта!", "Продовжити", "Назад");
			}
			case 1:
			{
			    new query[62+(17-2)+1], ip[16];
                            subnet(playerid, ip);
                            //не стану розписувати збереження/вичеслення підпережі із бази, думаю суть буде зрозуміла
                            format(query, sizeof(query), "SELECT `Name` FROM `"TABLE_ACCOUNT"` WHERE `subreg` = '%s'", ip); //відправляю запит до mysql, таблиці 'account', рядки 'Name' який в прикладі зберігає нік, 'subreg', який теоритично уявімо містить підмережу, збережену в бд
                            mysql_tquery(connects, query, "reconciliation", "i", playerid); //connects(змінна підключення до MYSQL) mysql_connect
			}
		}
	}
	case AUTO_SEARCH_EMAIL:
	{
            if(!response) return ShowPlayerDialog(playerid, AUTO_SEARCH, DIALOG_STYLE_LIST, "Відновлення аккаунта", "1. Пошук по E-Mail пошті\n 2. Автоматичний пошук", "Вибрати", "Закрити"); //Якщо натиснув назад
			
	    if ( strlen ( inputtext ) < 5 || strlen ( inputtext ) > 40 ) //перевірка на кількість ведених символів
       	    {
                SendClientMessage(playerid, -1, "Не правильно ведена пошта!");
                return ShowPlayerDialog(playerid, AUTO_SEARCH_EMAIL, DIALOG_STYLE_INPUT, "Відновлення аккаунта", "Ведіть адресу електронної пошти", "Продовжити", "Назад"); //завершую повторним показом діалога
	    }
	    new query[100];
	    format(query, sizeof(query), "SELECT `Name` FROM `"TABLE_ACCOUNT"` WHERE `pEmail` = '%s'", inputtext); //відправляю запит до mysql, таблиці 'account', 'pEmail' - реєстраційна пошта
	    mysql_tquery(connects, query, "reconciliation", "i", playerid);
	}
    //також тут
	return 1;
}

forward reconciliation(playerid);
public reconciliation(playerid) //Створюю паблік перевірки на наявність твінків
{
    new rows, fields; //змінні для кількості полів та рядків
    cache_get_data(rows, fields); //дізнаюсь кількіснь рядків та полів із записом в змінну
    	if(rows)  //якщо по запиту знайдено поле в таблиці
        {
  	    new nick[24], listem[120], txt[MAX_PLAYER_NAME +4]; //+ строкові змінні
		 
	    for(new i; i < rows; i++) //цикл для перевірки/отримання ніка та форматування його в змінну, якщо значення 'i' менше за кількість рядків у таблиці то цикл працює
	    {
  	        cache_get_field_content(i, "Name", nick, connects, 32); //функція загрузки, Name - як і вище розписано у нас рядок із таблиці account в базі який зберігає в собі нік, записую нік в змінну 'nick'
	        format(txt, sizeof(txt), "%d. %s\n", i +1, nick); //функцією форматую нік твінків, 'i +1' із номерацією рядків
   	        strcat(listem, txt); //функцією strcat записує поочередно із масива 'txt' ніки твінків в 'listem'
	    }
 	    format(listem, sizeof(listem), "{FFFFFF}Список знайдених аккаунтів\n\%s",  listem); //форматую текст, зі значенням "listem", що містить в собі список твінків
 	    ShowPlayerDialog(playerid, RESTORE, DIALOG_STYLE_MSGBOX, "Пошук аккаунта", listem, "Назад", "Закрити"); //показую сам діалог гравцю
        }
	else //якщо в бд не знайдено даних
	{
	    SendClientMessage(playerid, -1, "В базі не знайдено жодного аккаунта за вашими даними!");
	    return ShowPlayerDialog(playerid, AUTO_SEARCH, DIALOG_STYLE_LIST, "Відновлення аккаунта", "1. Пошук по Email пошті\n 2. Автоматичний пошук", "Вибрати", "Закрити"); //повторно показую діалог
	}
	//і тут
    return 1;
}

//Самописна мною функція для отримання підмережі із ІП
stock subnet(playerid, ip_address[]) {
    GetPlayerIp(playerid, ip_address, 17);  // Отримуємо IP гравця
    new point = 0;  // Змінна для вичислення крапок
    for (new x = 0; x < strlen(ip_address); x++) {  // Циклом звіряю кожну букву ІП
        if (ip_address[x] == '.') point++;  // +1 при знаходженні крапки
        if (point == 2) {  // Якщо/коли знайдено другу крапку
            strdel(ip_address, x + 1, strlen(ip_address));  // Обрізаємо залишок ІП після 2 крапки
            break;  // Перериваю цикл
            //тут змянено
        }
    }
    return 1;
}
