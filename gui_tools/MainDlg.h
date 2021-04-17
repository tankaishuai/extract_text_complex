
#pragma once
#include <atlbase.h>
#include <atlstr.h>
#include <atlconv.h>
#include <atlfile.h>
#include <list>

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter
{
public:
	CMainDlg();
	enum { IDD = IDD_MAINDLG };

 enum
 {
   TIMER_ID_LOAD_URL_TIMEOUT = 1,
 };

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  MESSAGE_HANDLER(WM_CLOSE, OnClose)
		COMMAND_HANDLER(IDC_BUTTON_GO, BN_CLICKED, OnBnClickedButtonGo)
		COMMAND_HANDLER(IDC_BUTTON_REFRESH, BN_CLICKED, OnBnClickedButtonRefresh)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
 LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	LRESULT OnBnClickedButtonGo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnBnClickedButtonRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
