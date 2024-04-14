
// CDlgLoginRVIA.h: archivo de encabezado
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <iphlpapi.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#include <C_PostgreSQL.hpp>

#pragma once


// Cuadro de diálogo de CDlgLoginRVIA
class CDlgLoginRVIA : public CDialogEx
{
// Construcción
public:
	CDlgLoginRVIA(CWnd* pParent = nullptr);	// Constructor estándar

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGINRVIA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:
	HICON m_hIcon;
	
	long lEmpleado;
	int  iCantEmp;

	int  iFoco;
	int  iControles;
	bool bShiftTab;

	CString csPath;
	CString csMigVul;

	bool conectaPG();

	std::string getMacAddress();

	std::string getIPAddress();

	std::string getHostName();

	void getSystemInformation();

	C_PostgreSQL pg;

	HANDLE hRead;
	HANDLE hWrite;

	// Funciones de asignación de mensajes generadas
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_EditEmpleado;
	CMFCEditBrowseCtrl m_BrowsePath;
	CComboBox m_CmbMigVul;
	CComboBox m_CboCantEmp;
	CMFCButton m_BtnAceptar;
	CMFCButton m_BtnSalir;
	afx_msg void OnBnClickedMfcbuttonAceptar();
	afx_msg void OnBnClickedMfcbuttonSalir();
	
	void asignarFoco();
	bool boton();
	bool validarControl(CString& sCadena);
	void iniciarVariables();
	void setControlFontSize(int iFontSize);
	bool validaClick(CEdit& m_EditTmp, int iTmpFocus);
	bool validaClick(CMFCEditBrowseCtrl& m_EditTmp, int iTmpFocus);
	bool validaClick(CComboBox& m_EditTmp, int iTmpFocus);
	afx_msg void OnSetfocusEditEmpleado();
	afx_msg void OnSetfocusMfceditbrowsePath();
	afx_msg void OnChangeMfceditbrowsePath();
	afx_msg void OnSetfocusComboMigVul();
	afx_msg void OnSelchangeComboMigVul();
	afx_msg void OnSetfocusComboCantEmp();
	afx_msg void OnSelchangeComboCantEmp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
