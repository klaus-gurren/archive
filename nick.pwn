#define D_NAME	3333 //для зручності

cmd:nickname(playerid) //приклад виклику по команді
{
    ShowPlayerDialog(playerid, D_NAME, DIALOG_STYLE_INPUT, "Змінити ім'я та прізвище", "Введіть ваш бажаний нік у поле нижче, в форматі (Imya_Prizvishe)", "Продовжити", "Скасувати");
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) //В паблік роботи із діалогами
{
    case D_NAME:
    {
        if(!response) return 1;
        if(!strlen(inputtext)) return ShowPlayerDialog(playerid, D_NAME, DIALOG_STYLE_INPUT, "Змінити ім'я та прізвище", "Введіть ваш бажаний нік у поле нижче, в форматі (Imya_Prizvishe)", "Продовжити", "Скасувати");
	    if(strlen(inputtext) < 6 || strlen(inputtext) > 24) return  SendClientMessage(playerid, -1, "Не менше 6 та більше 24 букв");
	    if(!strcmp(inputtext, "Imya_Prizvishe", true)) return SendClientMessage(playerid, -1, "Дурачок?)");

	    new underscorePos = strfind(inputtext, "_", true);
	    if(underscorePos == -1) return SendClientMessage(playerid, -1, "Невірний формат ведення! (приклад: Imya_Prizvishe)"); //якщо відсутнє нижнє підкреслення
		
	    new surnameLength = (strlen(inputtext)-(underscorePos)+1); //від повного ніка віднімаю ім'я +1 з врахуванням нижнього підкреслення, змінна містить кількість букв фамілії
	    if(underscorePos < 3 || surnameLength < 3) return SendClientMessage(playerid, -1, "Довжина імені чи прізвища має бути не менше 3 символів");
		
        new lower, big = 0;
        for(new i = 0; i < strlen(inputtext); i++)
        {
            switch(inputtext[i])
            {
            	case 'A'..'Z': 
		        {
		            if(i == 0 || i == underscorePos+1) big++;
		            else {
		                return SendClientMessage(playerid, -1, "Тільки ім'я та прізвище повинно починатися із великої літери!");
                    }
		        }
                case 'a'..'z': continue;
		        case '_': lower++;
                default: return SendClientMessage(playerid, -1, "Заборонені символи, використовуйте тільки англійські букви! (A-Z, a-z)");
            }
        }
        if(big < 2 || lower > 1) return SendClientMessage(playerid, -1, "Невірний формат ведення! (приклад: Imya_Prizvishe)"); //Якщо перша буква імені/фамілії не з великої, або більше 1 нижніх підкреслень
	    //далі вже збереження і т.п.
    }
    return 1;
}
