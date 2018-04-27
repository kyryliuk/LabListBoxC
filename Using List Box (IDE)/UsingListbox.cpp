#include <windows.h>
#include <tchar.h>
#include "resource.h"
HWND hDialog, hEdit1, hEdit2, hEdit3, hList1, hList2;
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}



BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

switch (message)
{
case WM_INITDIALOG:
		//дескриптори элементів керування
		hList1 = GetDlgItem(hwnd, IDC_LIST_1);
		hList2 = GetDlgItem(hwnd, IDC_LIST_2);
		hEdit1 = GetDlgItem(hwnd, IDC_EDIT_1);
		hEdit2 = GetDlgItem(hwnd, IDC_EDIT_2);
		hEdit3 = GetDlgItem(hwnd, IDC_EDIT_3);

		// додавання елементів в список з одинарним вибором
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("WinApi")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C#")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Windows Forms")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("DataBase")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("SQL Server")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("ORACLE")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C++")));

		// ширина списку з множинним вибором
		SendMessage(hList2, LB_SETCOLUMNWIDTH, 170, 0);
		// додавання елементів в список з множинним вибором
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("C")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("WinApi")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("C#")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("Windows Forms")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("DataBase")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("SQL Server")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("ORACLE")));
		SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(TEXT("C++")));
return TRUE;
case WM_CLOSE:
		EndDialog(hwnd, 0);
return TRUE;
case WM_COMMAND:
		UINT id = LOWORD(wParam);
		switch (id)
		{
		case IDC_ADD://додавання елемента в список
		{
			// визначення довжини тексту,який введений в текстове поле IDC_EDIT_1
			int length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			TCHAR *pBuffer = new TCHAR[length + 1];
			// у виділену пам'ять копіюємо текст, який введений в текстове поле IDC_EDIT_1
			GetWindowText(hEdit1, pBuffer, length + 1);
			if (lstrlen(pBuffer))
			{
				// перевіряємо, чи є такий предмет в списку
				int index = SendMessage(hList1, LB_FINDSTRINGEXACT, -1, LPARAM(pBuffer));
				if (index == LB_ERR)
					// додаємо предмет в списки і очищуємо текстове поле IDC_EDIT_1
				{
					SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(pBuffer));
					SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(pBuffer));
					SendMessage(hEdit1, EM_SETSEL, 0, length);
					SendMessage(hEdit1, WM_CLEAR, 0, 0);
				}
				else
					MessageBox(hwnd, TEXT("Такий предмет вже існує!"), TEXT("Додавання предмету"), MB_OK | MB_ICONSTOP);
			}
			else
			{
				MessageBox(hwnd, TEXT("Введіть назву предмету!"), TEXT("Додавання предмету"), MB_OK | MB_ICONSTOP);
				SetFocus(hEdit1);
			}
			delete[]pBuffer;
		}
		break;
		case IDC_DEL://видалення елемента зі списку
		{
			// індекс вибраного елемента в списку
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{	//визначаємо довжину вибраного елемента
				int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
				TCHAR *pBuffer = new TCHAR[length + 1];
				//копіюємо значення вибраного елемента в виділену пам'ять
				SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("Видалення предмету"), MB_OK | MB_ICONINFORMATION);
				//видаляємо вибраний елемент зі списку
				SendMessage(hList1, LB_DELETESTRING, index, 0);
				delete[] pBuffer;
			}
			else
				MessageBox(hwnd, TEXT("Предмет не вибрано!"), TEXT("Видалення предмету"), MB_OK | MB_ICONSTOP);
		}
		break;
		case IDC_FIND://пошук елемента в списку
		{
			// визначаємо довжину назви предмету 
			int length = SendMessage(hEdit2, WM_GETTEXTLENGTH, 0, 0);
			TCHAR *pBuffer = new TCHAR[length + 1];
			//копіюємо значення введеного предмету в виділену пам'ять
			GetWindowText(hEdit2, pBuffer, length + 1);
			if (lstrlen(pBuffer))
			{
				// перевіряємо, чи є такий предмет у списку
				int index = SendMessage(hList1, LB_SELECTSTRING, -1, LPARAM(pBuffer));
				if (index == LB_ERR)
					MessageBox(hwnd, TEXT("Предмету не знайдено!"), TEXT("Пошук предмету"), MB_OK | MB_ICONSTOP);
			}
			else
			{
				MessageBox(hwnd, TEXT("Для пошуку введіть назву предмету!"), TEXT("Пошук предмету"), MB_OK | MB_ICONSTOP);
				SetFocus(hEdit2);
			}
			delete[] pBuffer;
		}
		break;
		case IDC_DELALL://видалення усіх елементів зі списку
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);
			break;
		case IDC_GETSELITEMS://вибірка елементів зі списку з множинним вибором
		{
			// визначаємо кількість вибраних елементів
			int nCount = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
			//	формуємо масив для зберігання індексів вибраних елементів
			int *p = new int[nCount];
			// Заповнюємо масив індексами елементів списку
			SendMessage(hList2, LB_GETSELITEMS, nCount, LPARAM(p));
			for (int i = 0; i < nCount; i++)
			{
				// визначаємо розмір елемента в списку
				int length = SendMessage(hList2, LB_GETTEXTLEN, p[i], 0);
				TCHAR *pBuffer = new TCHAR[length + 3];
				// в виділену пам'ять копіюємо вибраний елемент
				SendMessage(hList2, LB_GETTEXT, p[i], LPARAM(pBuffer));
				_tcscat(pBuffer,TEXT("\r\n"));
				int length_edit = GetWindowTextLength(hEdit3);
				SendMessage(hEdit3, EM_SETSEL, (WPARAM)length_edit, (LPARAM)length_edit);
				SendMessage(hEdit3, EM_REPLACESEL, 0, (LPARAM)((LPSTR)pBuffer));
				SendMessage(hList2, LB_SETSEL, FALSE, p[i]);//відміняємо вибір опрацьованого елемента
				SetFocus(hEdit3);
				delete[] pBuffer;
			}
		}
		break;
		}




		// якщо в списку з одинарним вибором відбулася зміна вибору елемента
		if (id == IDC_LIST_1 && (UINT)HIWORD(wParam) == LBN_SELCHANGE)
		{
			// отримуємо індекс вибраного елемента
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) // выбран ли элемент списка?
			{
				// визначаємо довжину назви предмету
				int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
				TCHAR *pBuffer = new TCHAR[length];
				SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("Вибір предмету"), MB_OK | MB_ICONINFORMATION);
			}
		}
		return TRUE;
	}
	return FALSE;
}