// код в момент якщо було знайдено твінки, показую діалог
new klaus[] = "{FFFFFF}Вами було зареєстровано більше 2-х аккаунтів\n\
		Правилами сервера це {F81414}заборонено!\n\
		{FFFFFF}Ведіть в лаунчері Nick-Name уже зареєстрованого вами аккаунта\n\
		Якщо забули Nick-Name натисніть {FFFF00}відновити"; //для прикладу текстова змінна
	
    ShowPlayerDialog(playerid, вільний ID діалога, DIALOG_STYLE_MSGBOX, "Примітка", klaus, "Відновити", "Закрити"); //показую сам діалог гравцю

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) //В паблік роботи із діалогами
{
	case вільний ID діалога: //функція діалога
	{
	    if(!response) return Kick(playerid); //якщо натиснув закрити - кік
	    OpenLinkForPlayer(playerid, "https://www.uarp.mobi/"); //функцією відправляю запит на перехід на сайт
     }
 return 1;
}
