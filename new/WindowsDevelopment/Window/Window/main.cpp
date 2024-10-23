#include <Windows.h>
#include "resource.h"


CONST CHAR g_sz_LOGIN_INVITATION[] = "Введите имя пользователя";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT mCmdShow)
{
	// hInstance- экземпляр запущенного exe. программы
	// hPrevInst - не используется
	// LPSTR - Long pointer to string
	// lpCmdLine - CommandLine (КОМАНДНАЯ СТРОКА С ПАРРАММЕТРАМИ ЗАПУСКА ПРИЛОЖЕНИЯ)
	// mCmdShow - режим отображения окна (развернтуто, свернуто и тд.)
	// Префиксы n... lp ... - Венгерская нотация 
				 //n-number
				 //lp-long pointer
				 //h-HINSTANCE
	/*MessageBox
	(
		NULL,
		"Hello Windows",
		"Window title",
		MB_OK |
		MB_ICONINFORMATION
	);*/

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);

	return 0;

}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// hwnd-Handler windiw - обработчик или дескриптор окна-число с помощью которого можно обратиться к окну.
	//uMsg - сообщение которое отправляется окну.
	//wParam , lParam - параметры сообщения.
	switch (uMsg)
	{
	case WM_INITDIALOG://Отправляется при инициализации окна
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
	}
		break;
	case WM_COMMAND://отправляется при дейсвтиях пользователя
		switch (LOWORD(wParam))
		{
		//case IDC_EDIT_LOGIN: //Начало попытки домашнего задания
		//{
		//	HWND hLoginPlaceholder = GetDlgItem(hwnd, IDC_PLACEHOLDER);
		//	HWND hEditLogin = GetDlgItem(hwnd,IDC_EDIT_LOGIN);
		//	ShowWindow(hLoginPlaceholder, SW_HIDE);
		//	CONST INT SIZE = 256;
		//	CHAR sz_buffer[SIZE] = {};
		//	SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
		//	if (sz_buffer[0] = NULL)
		//	{
		//		ShowWindow(hLoginPlaceholder, SW_SHOW);
		//		BringWindowToTop(hLoginPlaceholder);
		//	}		
		//}
		//break;//Конец попытки домашнего задания(не возвращается ввод логина если поле осталось незаполненным, чтобы не мешалось убрал поле в сторону и 
			//сделал его невидимым , чтобы оно не появлялось при запуске программы.
		case IDC_EDIT_LOGIN:
		{
			CONST INT SIZE = 256;
			char sz_buffer[SIZE]{};
			SendMessage((HWND)lParam, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS && strcmp(sz_buffer, g_sz_LOGIN_INVITATION) == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)"");
			
			if (HIWORD(wParam) == EN_KILLFOCUS && strcmp(sz_buffer, "") == 0)
					SendMessage((HWND)lParam, WM_SETTEXT, 0, (LPARAM)g_sz_LOGIN_INVITATION);
			//strcmp сравнивает строки и возвращает значение типа int =0-строки идентичны !=0-строки отличаются
			
		}
			break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {}; //sz-string zero(NULL)
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDOK:MessageBox(hwnd, "Была нажата кнопка ок", "info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0); break;

		}
		break;
	case WM_CLOSE://отправляется при закрытии
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;

}