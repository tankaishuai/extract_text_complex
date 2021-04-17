
#include "stdafx.h"
#include "resource.h"
#include "MainDlg.h"
#include <strsafe.h>
#include <atlmisc.h>
#include <locale.h>
#include "..\sdk\ExtractTextV23.h"
#include <string>

CMainDlg::CMainDlg()
{
}

BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CenterWindow();

	// set icons
	HICON hIcon = LoadIconW((HMODULE)(&__ImageBase), MAKEINTRESOURCEW(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	UIAddChildWindowContainer(m_hWnd);
 ShowWindow(SW_SHOWNORMAL);

 if (!ExtractText_Register())
 {
   MessageBoxW(L"ExtractText_Register 注册失败，可能需要管理员权限!");
 }
 return 0;
}

LRESULT CMainDlg::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
  DestroyWindow();
  PostQuitMessage(0);
  return 0;
}

LRESULT CMainDlg::OnBnClickedButtonGo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  CStringA strPath;
  ::GetDlgItemTextA(m_hWnd, IDC_EDIT_URL, strPath.GetBuffer(MAX_PATH), MAX_PATH);
  strPath.ReleaseBuffer();
  if (strPath.IsEmpty())
    return 0;

  LPCSTR szExt = PathFindExtensionA(strPath);
  ExtractDocumentTextA_t pfnExtractDocumentTextA = ExtractDocumentTextA;
  if (0 == stricmp(szExt, ".hlp"))
    pfnExtractDocumentTextA = hlpGet_text_buf;
  else if (0 == stricmp(szExt, ".chm"))
    pfnExtractDocumentTextA = hlpGet_text_buf;

  CStringA strBuf;
  int cchMax = (1 << 20);
  int iRetVal = pfnExtractDocumentTextA(strPath, strBuf.GetBuffer(cchMax), cchMax);
  strBuf.ReleaseBuffer();

  if (!strBuf.IsEmpty())
  {
    CStringA strPathText(strPath);
    strPathText += ".ex.txt";
    HANDLE hFile = CreateFileA(strPathText, GENERIC_WRITE, 0, nullptr, CREATE_NEW, 0, nullptr);
    if (INVALID_HANDLE_VALUE != hFile)
    {
      DWORD dwFetch = 0;
      WriteFile(hFile, (LPCSTR)strBuf, strBuf.GetLength(), &dwFetch, nullptr);
      CloseHandle(hFile);
    }
  }
  MessageBoxW((L"Extract retVal = " + std::to_wstring(iRetVal)).c_str());
	return 0;
}

LRESULT CMainDlg::OnBnClickedButtonRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  CFileDialog dlg(TRUE);
  if (IDOK != dlg.DoModal(m_hWnd))
    return 0;
  CStringW strPath;
  //调用的API，窗口已被销毁，不能用：dlg.GetFilePath(strPath.GetBuffer(MAX_PATH), MAX_PATH);
  //strPath.ReleaseBuffer();
  SetDlgItemTextW(IDC_EDIT_URL, dlg.m_ofn.lpstrFile);
	return 0;
}
