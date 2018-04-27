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
		//����������� �������� ���������
		hList1 = GetDlgItem(hwnd, IDC_LIST_1);
		hList2 = GetDlgItem(hwnd, IDC_LIST_2);
		hEdit1 = GetDlgItem(hwnd, IDC_EDIT_1);
		hEdit2 = GetDlgItem(hwnd, IDC_EDIT_2);
		hEdit3 = GetDlgItem(hwnd, IDC_EDIT_3);

		// ��������� �������� � ������ � ��������� �������
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("WinApi")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C#")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("Windows Forms")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("DataBase")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("SQL Server")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("ORACLE")));
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(TEXT("C++")));

		// ������ ������ � ��������� �������
		SendMessage(hList2, LB_SETCOLUMNWIDTH, 170, 0);
		// ��������� �������� � ������ � ��������� �������
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
		case IDC_ADD://��������� �������� � ������
		{
			// ���������� ������� ������,���� �������� � �������� ���� IDC_EDIT_1
			int length = SendMessage(hEdit1, WM_GETTEXTLENGTH, 0, 0);
			TCHAR *pBuffer = new TCHAR[length + 1];
			// � ������� ���'��� ������� �����, ���� �������� � �������� ���� IDC_EDIT_1
			GetWindowText(hEdit1, pBuffer, length + 1);
			if (lstrlen(pBuffer))
			{
				// ����������, �� � ����� ������� � ������
				int index = SendMessage(hList1, LB_FINDSTRINGEXACT, -1, LPARAM(pBuffer));
				if (index == LB_ERR)
					// ������ ������� � ������ � ������� �������� ���� IDC_EDIT_1
				{
					SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(pBuffer));
					SendMessage(hList2, LB_ADDSTRING, 0, LPARAM(pBuffer));
					SendMessage(hEdit1, EM_SETSEL, 0, length);
					SendMessage(hEdit1, WM_CLEAR, 0, 0);
				}
				else
					MessageBox(hwnd, TEXT("����� ������� ��� ����!"), TEXT("��������� ��������"), MB_OK | MB_ICONSTOP);
			}
			else
			{
				MessageBox(hwnd, TEXT("������ ����� ��������!"), TEXT("��������� ��������"), MB_OK | MB_ICONSTOP);
				SetFocus(hEdit1);
			}
			delete[]pBuffer;
		}
		break;
		case IDC_DEL://��������� �������� � ������
		{
			// ������ ��������� �������� � ������
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR)
			{	//��������� ������� ��������� ��������
				int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
				TCHAR *pBuffer = new TCHAR[length + 1];
				//������� �������� ��������� �������� � ������� ���'���
				SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("��������� ��������"), MB_OK | MB_ICONINFORMATION);
				//��������� �������� ������� � ������
				SendMessage(hList1, LB_DELETESTRING, index, 0);
				delete[] pBuffer;
			}
			else
				MessageBox(hwnd, TEXT("������� �� �������!"), TEXT("��������� ��������"), MB_OK | MB_ICONSTOP);
		}
		break;
		case IDC_FIND://����� �������� � ������
		{
			// ��������� ������� ����� �������� 
			int length = SendMessage(hEdit2, WM_GETTEXTLENGTH, 0, 0);
			TCHAR *pBuffer = new TCHAR[length + 1];
			//������� �������� ��������� �������� � ������� ���'���
			GetWindowText(hEdit2, pBuffer, length + 1);
			if (lstrlen(pBuffer))
			{
				// ����������, �� � ����� ������� � ������
				int index = SendMessage(hList1, LB_SELECTSTRING, -1, LPARAM(pBuffer));
				if (index == LB_ERR)
					MessageBox(hwnd, TEXT("�������� �� ��������!"), TEXT("����� ��������"), MB_OK | MB_ICONSTOP);
			}
			else
			{
				MessageBox(hwnd, TEXT("��� ������ ������ ����� ��������!"), TEXT("����� ��������"), MB_OK | MB_ICONSTOP);
				SetFocus(hEdit2);
			}
			delete[] pBuffer;
		}
		break;
		case IDC_DELALL://��������� ��� �������� � ������
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);
			break;
		case IDC_GETSELITEMS://������ �������� � ������ � ��������� �������
		{
			// ��������� ������� �������� ��������
			int nCount = SendMessage(hList2, LB_GETSELCOUNT, 0, 0);
			//	������� ����� ��� ��������� ������� �������� ��������
			int *p = new int[nCount];
			// ���������� ����� ��������� �������� ������
			SendMessage(hList2, LB_GETSELITEMS, nCount, LPARAM(p));
			for (int i = 0; i < nCount; i++)
			{
				// ��������� ����� �������� � ������
				int length = SendMessage(hList2, LB_GETTEXTLEN, p[i], 0);
				TCHAR *pBuffer = new TCHAR[length + 3];
				// � ������� ���'��� ������� �������� �������
				SendMessage(hList2, LB_GETTEXT, p[i], LPARAM(pBuffer));
				_tcscat(pBuffer,TEXT("\r\n"));
				int length_edit = GetWindowTextLength(hEdit3);
				SendMessage(hEdit3, EM_SETSEL, (WPARAM)length_edit, (LPARAM)length_edit);
				SendMessage(hEdit3, EM_REPLACESEL, 0, (LPARAM)((LPSTR)pBuffer));
				SendMessage(hList2, LB_SETSEL, FALSE, p[i]);//�������� ���� ������������� ��������
				SetFocus(hEdit3);
				delete[] pBuffer;
			}
		}
		break;
		}




		// ���� � ������ � ��������� ������� �������� ���� ������ ��������
		if (id == IDC_LIST_1 && (UINT)HIWORD(wParam) == LBN_SELCHANGE)
		{
			// �������� ������ ��������� ��������
			int index = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if (index != LB_ERR) // ������ �� ������� ������?
			{
				// ��������� ������� ����� ��������
				int length = SendMessage(hList1, LB_GETTEXTLEN, index, 0);
				TCHAR *pBuffer = new TCHAR[length];
				SendMessage(hList1, LB_GETTEXT, index, LPARAM(pBuffer));
				MessageBox(hwnd, pBuffer, TEXT("���� ��������"), MB_OK | MB_ICONINFORMATION);
			}
		}
		return TRUE;
	}
	return FALSE;
}