
// CDlgLoginRVIA.cpp: archivo de implementación
//

#include "pch.h"
#include "framework.h"
#include "LoginRVIA.h"
#include "CDlgLoginRVIA.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cuadro de diálogo de CDlgLoginRVIA



CDlgLoginRVIA::CDlgLoginRVIA(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_LOGINRVIA_DIALOG, pParent),
	lEmpleado(0L),
	iCantEmp(0),
	iFoco(0),
	iControles(3),
	bShiftTab(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgLoginRVIA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_EMPLEADO, m_EditEmpleado);
	DDX_Control(pDX, IDC_MFCEDITBROWSE_PATH, m_BrowsePath);
	DDX_Control(pDX, IDC_COMBO_MIG_VUL, m_CmbMigVul);
	DDX_Control(pDX, IDC_COMBO_CANT_EMP, m_CboCantEmp);
	DDX_Control(pDX, IDC_MFCBUTTON_ACEPTAR, m_BtnAceptar);
	DDX_Control(pDX, IDC_MFCBUTTON_SALIR, m_BtnSalir);
}

BEGIN_MESSAGE_MAP(CDlgLoginRVIA, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON_ACEPTAR, &CDlgLoginRVIA::OnBnClickedMfcbuttonAceptar)
	ON_BN_CLICKED(IDC_MFCBUTTON_SALIR, &CDlgLoginRVIA::OnBnClickedMfcbuttonSalir)
	ON_EN_SETFOCUS(IDC_EDIT_EMPLEADO, &CDlgLoginRVIA::OnSetfocusEditEmpleado)
	ON_EN_SETFOCUS(IDC_MFCEDITBROWSE_PATH, &CDlgLoginRVIA::OnSetfocusMfceditbrowsePath)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE_PATH, &CDlgLoginRVIA::OnChangeMfceditbrowsePath)
	ON_CBN_SETFOCUS(IDC_COMBO_MIG_VUL, &CDlgLoginRVIA::OnSetfocusComboMigVul)
	ON_CBN_SELCHANGE(IDC_COMBO_MIG_VUL, &CDlgLoginRVIA::OnSelchangeComboMigVul)
	ON_CBN_SETFOCUS(IDC_COMBO_CANT_EMP, &CDlgLoginRVIA::OnSetfocusComboCantEmp)
	ON_CBN_SELCHANGE(IDC_COMBO_CANT_EMP, &CDlgLoginRVIA::OnSelchangeComboCantEmp)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Controladores de mensajes de CDlgLoginRVIA

BOOL CDlgLoginRVIA::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Establecer el icono para este cuadro de diálogo.  El marco de trabajo realiza esta operación
	//  automáticamente cuando la ventana principal de la aplicación no es un cuadro de diálogo
	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño

	iControles = 5;
	iFoco = 0;

	setControlFontSize(20);

	iniciarVariables();

	//getSystemInformation();

	//conectaPG();

	SetTimer(1, 100, NULL);

	return FALSE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CDlgLoginRVIA::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CDlgLoginRVIA::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CDlgLoginRVIA::PreTranslateMessage(MSG* pMsg)
{
	//if (pMsg->message == WM_KEYDOWN)
	//{
	//	switch (pMsg->wParam)
	//	{
	//	case VK_RETURN:
	//		pMsg->wParam = VK_SHIFT;
	//		break;
	//	case VK_ESCAPE:
	//		//termina(0, IDCANCEL, NULL, bHandle);
	//		if (AfxMessageBox(_T("DESEA SALIR?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	//		{
	//			OnCancel();
	//		}
	//		else
	//		{
	//			pMsg->wParam = VK_SHIFT;
	//		}
	//		break;

	//	}
	//}

	CString sPaso;

	bShiftTab = false;
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 13)
		{
			if (!boton())
			{
				if (iFoco <= iControles) //numero de controles
				{
					sPaso = ' ';
					if (validarControl(sPaso))
					{
						iFoco++;
						asignarFoco();
					}
					else
					{
						if (!bShiftTab)
						{
							//CPoint point;
							//::GetCursorPos(&point);						
							//CBalloonHelp::LaunchBalloon( "ATENCION", (LPTSTR)(LPCTSTR)sPaso, /*CPoint(pMsg->pt)*/point, IDI_WARNING, CBalloonHelp::unCLOSE_ON_MOUSE_MOVE|CBalloonHelp::unCLOSE_ON_KEYPRESS, NULL, "", 0);
							AfxMessageBox(sPaso);
						}
					}
					return TRUE;
				}
				else
				{
					if (pMsg->wParam != 13)
					{
						iFoco++;
						asignarFoco();
					}
					else
					{
						asignarFoco();
					}
					return TRUE;
				}
			}
			else
			{
				asignarFoco();
				return TRUE;
			}
		}
		else
		{
			if (pMsg->wParam == VK_TAB && GetKeyState(VK_SHIFT) & 0x8000)
			{
				bShiftTab = true;
			}

			if (pMsg->wParam == VK_TAB)
			{
				pMsg->wParam = VK_SHIFT;
			}

			if (pMsg->wParam == VK_ESCAPE)
			{
				if (AfxMessageBox(_T("DESEA SALIR?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					OnCancel();
				}
				else
				{
					pMsg->wParam = VK_SHIFT;
				}
			}
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgLoginRVIA::OnBnClickedMfcbuttonAceptar()
{
    if (lEmpleado < 90000000 || lEmpleado > 99999999)
    {
        MessageBoxA(NULL, "Debe capturar todos los campos.", "SISTEMA IA", MB_ICONERROR);
        return;
    }

    if (csPath.IsEmpty())
    {
        MessageBoxA(NULL, "Debe capturar o seleccionar una directorio.", "SISTEMA IA", MB_ICONERROR);
        return;
    }

    if (csMigVul.IsEmpty())
    {
        MessageBoxA(NULL, "Debe capturar o seleccionar si es una migración o vulnerabilidad.", "SISTEMA IA", MB_ICONERROR);
        return;
    }

    if (iCantEmp == 0)
    {
        MessageBoxA(NULL, "Debe capturar o seleccionar la cantidad de empleados.", "SISTEMA IA", MB_ICONERROR);
        return;
    }

    std::string executablePath = "C:\\sys\\progs\\parse\\RvIA.exe";
    //std::string commandLine = executablePath + " " + std::to_string(lEmpleado) + " " + std::string(CT2CA(csPath)) + " " + std::string(CT2CA(csMigVul)) + " " + std::to_string(iCantEmp);
	std::string commandLine = executablePath + " " + std::string(CT2CA(csPath)) + " " + std::string(CT2CA(csMigVul)) + " " + std::to_string(iCantEmp);

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		std::cerr << "CreatePipe failed: " << GetLastError() << std::endl;

		MessageBoxA(NULL, "CreatePipe failed.", "SISTEMA IA", MB_ICONERROR);
		return;
	}


    STARTUPINFOA si;
	//LPSTARTUPINFO si = { sizeof(LPSTARTUPINFO) };
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.wShowWindow = SW_HIDE;
	si.hStdOutput = hWrite;
	si.hStdError = hWrite;

    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessA(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        MessageBoxA(NULL, "Error al ejecutar el programa.", "SISTEMA IA", MB_ICONERROR);
        return;
    }


    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    if (!GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        MessageBoxA(NULL, "Error al obtener el código de salida del programa.", "SISTEMA IA", MB_ICONERROR);
        return;
    }

	switch (exitCode)
	{
		case 0:
		MessageBoxA(NULL, "El programa se ejecutó correctamente.", "SISTEMA IA", MB_ICONINFORMATION);
		break;
		case ERROR_FILE_NOT_FOUND:
			MessageBoxA(NULL, "El archivo no se encontró.", "SISTEMA IA", MB_ICONERROR);
			break;
		case ERROR_PATH_NOT_FOUND:
			MessageBoxA(NULL, "El directorio no se encontró.", "SISTEMA IA", MB_ICONERROR);
			break;
		case ERROR_ACCESS_DENIED:
			MessageBoxA(NULL, "Acceso denegado.", "SISTEMA IA", MB_ICONERROR);
			break;
		case ERROR_INVALID_TOKEN:
			MessageBoxA(NULL, "Token inválido.", "SISTEMA IA", MB_ICONERROR);
			break;
		case ERROR_INVALID_PARAMETER:
			MessageBoxA(NULL, "Parámetro inválido.", "SISTEMA IA", MB_ICONERROR);
			break;
		default:
			MessageBoxA(NULL, "El programa terminó con un código de salida diferente de cero.", "SISTEMA IA", MB_ICONERROR);
			break;
	}

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void CDlgLoginRVIA::OnBnClickedMfcbuttonSalir()
{
	if (AfxMessageBox(_T("DESEA SALIR?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		CDialogEx::OnCancel();
	}
	else
	{
		asignarFoco();
	}
}

void CDlgLoginRVIA::asignarFoco()
{
	switch (iFoco)
	{
	case 0:
		m_EditEmpleado.SetFocus();
		break;
	case 1:
		m_BrowsePath.SetFocus();
		break;
	case 2:
		m_CmbMigVul.SetFocus();
		break;
	case 3:
		m_CboCantEmp.SetFocus();
		//OnBnClickedButtonConsulta();
		break;
	case 4:
		m_BtnAceptar.SetFocus();
		break;
	}
}

bool CDlgLoginRVIA::boton()
{
	CWnd* pWnd = GetFocus();
	bool bRet = false;

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_MFCBUTTON_ACEPTAR:
		bRet = true;
		break;
	}
	return bRet;
}

bool CDlgLoginRVIA::validarControl(CString& csCadena)
{
	bool bRet = true;

	CString csEmpleado;
	CString csCantEmp;
	CString css;

	switch (iFoco)
	{
		case 0:
			m_EditEmpleado.GetWindowText(csEmpleado);
			csEmpleado.Trim();

			if (csEmpleado.IsEmpty())
			{
				csCadena = "Favor de Capturar el número de empleado...";
				bRet		= false;
				csEmpleado	= "";
				lEmpleado = 0L;
				m_EditEmpleado.SetWindowText(NULL);
			}
			else
			{
				lEmpleado = _ttol(csEmpleado);
			}
			break;
		case 1:

			m_BrowsePath.GetWindowText(csPath);
			csPath.Trim();

			if (csPath.IsEmpty())
			{
				csCadena = "Favor de Capturar o seleccionar un directorio...";
				bRet = false;
				csPath = "";			
				m_BrowsePath.SetWindowText(NULL);
			}
			break;
		case 2:

			m_CmbMigVul.GetWindowText(csMigVul);
			csMigVul.Trim();

			if (csMigVul.IsEmpty())
			{
				csCadena = "Favor de Capturar o selecciona si es una migración o vulnerabilidad...";
				bRet = false;
				csMigVul = "";
				m_CmbMigVul.SetWindowText(NULL);
			}
			else
			{
				if (csMigVul == "MIGRACION")
				{
					csMigVul = "mig";
				}
				else if (csMigVul == "VULNERABILIDAD")
				{
					csMigVul = "vul";
				}
				else
				{
					csCadena = "Favor de Capturar o selecciona si es una migración o vulnerabilidad...";
					bRet = false;
					csMigVul = "";
					m_CmbMigVul.SetWindowText(NULL);
				}
			}
			break;
		case 3:

			m_CboCantEmp.GetWindowText(csCantEmp);
			csCantEmp.Trim();

			if (csCantEmp.IsEmpty())
			{
				csCadena = "Favor de Capturar o selecciona si es una migración o vulnerabilidad...";
				bRet = false;
				csCantEmp = "";
				iCantEmp = 0;
				m_CboCantEmp.SetWindowText(NULL);
			}
			else
			{
				if (_ttol(csCantEmp) > 0 && _ttol(csEmpleado) < 21)
				{
					iCantEmp = _ttol(csCantEmp);
					if (iCantEmp > 0)
					{
						m_BtnAceptar.EnableWindow(TRUE);
					}
				}
				else
				{
					csCadena = "Favor de Capturar o selecciona si es una migración o vulnerabilidad...";
					bRet = false;
					csCantEmp = "";
					iCantEmp = 0;
					m_CboCantEmp.SetWindowText(NULL);
				}
			}
			break;
		default:
			break;
	}
	return bRet;
}

void CDlgLoginRVIA::iniciarVariables()
{
	CString sDato;

	m_EditEmpleado.SetFocus();
	m_EditEmpleado.SetLimitText(8);
	m_EditEmpleado.SetWindowTextW(NULL);

	m_BrowsePath.SetWindowTextW(NULL);

	lEmpleado = 0L;
	iCantEmp = 0;

	m_BtnAceptar.EnableWindow(FALSE);

	m_CmbMigVul.AddString(L"MIGRACION");
	m_CmbMigVul.AddString(L"VULNERABILIDAD");

	for (int i = 1; i < 26; i++)
	{
		sDato.Format(L"%d", i);
		m_CboCantEmp.AddString(sDato);
	}
	
}


void CDlgLoginRVIA::setControlFontSize(int iFontSize)
{
    CFont* pFont = GetFont();
    LOGFONT lf;
    pFont->GetLogFont(&lf);
    lf.lfHeight = -MulDiv(iFontSize, GetDeviceCaps(GetDC()->GetSafeHdc(), LOGPIXELSY), 72);
    CFont font;
    font.CreateFontIndirect(&lf);
	
    CStatic* pStaticTitulo = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_TITULO));
    pStaticTitulo->SetFont(&font);

    CStatic* pStaticEmpleado = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_EMPLEADO));
    pStaticEmpleado->SetFont(&font);

	CStatic* pStaticPath = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_PATH));
	pStaticPath->SetFont(&font);

	CStatic* pStaticMigVul = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_MIG_VUL));
	pStaticMigVul->SetFont(&font);

	CStatic* pStaticCantEmp = static_cast<CStatic*>(GetDlgItem(IDC_STATIC_CANT_EMP));
	pStaticCantEmp->SetFont(&font);

    // Add more CStatic controls here and set their font

    m_EditEmpleado.SetFont(&font);
    m_BrowsePath.SetFont(&font);
    m_CmbMigVul.SetFont(&font);
    m_CboCantEmp.SetFont(&font);
}

bool CDlgLoginRVIA::validaClick(CEdit& m_EditTmp, int iTmpFocus)
{
	//ValidarClick en CEdit
	CString sPaso;
	CString msg;

	int  iElementoTmp	= 0;
	int  i				= 0;
	bool bRegresa		= true;

	if (iFoco < iTmpFocus)
	{
		sPaso = ' ';
		// validar control anterior
		if (!validarControl(sPaso))
		{
			asignarFoco();
			if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
			{
				if (!bShiftTab)
				{
					AfxMessageBox(sPaso);
				}
			}

			bRegresa = false;
		}
		else
		{
			iElementoTmp = iFoco;
			iFoco = iTmpFocus;

			for (i = 0; i <= iTmpFocus; i++)
			{
				iFoco = i;
				//valida hacia abajo los controles
				if (!validarControl(sPaso))
				{
					break;
				}
			}
			asignarFoco();
		}
	}
	else
	{
		iFoco = iTmpFocus;
	}

	return bRegresa;
}


bool CDlgLoginRVIA::validaClick(CMFCEditBrowseCtrl& m_EditTmp, int iTmpFocus)
{
	//ValidarClick en CEdit
	CString sPaso;
	CString msg;

	int  iElementoTmp = 0;
	int  i = 0;
	bool bRegresa = true;

	if (iFoco < iTmpFocus)
	{
		sPaso = ' ';
		// validar control anterior
		if (!validarControl(sPaso))
		{
			asignarFoco();
			if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
			{
				if (!bShiftTab)
				{
					AfxMessageBox(sPaso);
				}
			}

			bRegresa = false;
		}
		else
		{
			iElementoTmp = iFoco;
			iFoco = iTmpFocus;

			for (i = 0; i <= iTmpFocus; i++)
			{
				iFoco = i;
				//valida hacia abajo los controles
				if (!validarControl(sPaso))
				{
					break;
				}
			}
			asignarFoco();
		}
	}
	else
	{
		iFoco = iTmpFocus;
	}

	return bRegresa;
}

bool CDlgLoginRVIA::validaClick(CComboBox& m_EditTmp, int iTmpFocus)
{
	//ValidarClick en CEdit
	CString sPaso;
	CString msg;

	int  iElementoTmp = 0;
	int  i = 0;
	bool bRegresa = true;

	if (iFoco < iTmpFocus)
	{
		sPaso = ' ';
		// validar control anterior
		if (!validarControl(sPaso))
		{
			asignarFoco();
			if (iFoco != iControles)//numero de controles para los que se quieren se vea el mebsaje de error
			{
				if (!bShiftTab)
				{
					AfxMessageBox(sPaso);
				}
			}

			bRegresa = false;
		}
		else
		{
			iElementoTmp = iFoco;
			iFoco = iTmpFocus;

			for (i = 0; i <= iTmpFocus; i++)
			{
				iFoco = i;
				//valida hacia abajo los controles
				if (!validarControl(sPaso))
				{
					break;
				}
			}
			asignarFoco();
		}
	}
	else
	{
		iFoco = iTmpFocus;
	}

	return bRegresa;
}



void CDlgLoginRVIA::OnSetfocusEditEmpleado()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
	validaClick(m_EditEmpleado, 0);
}


void CDlgLoginRVIA::OnSetfocusMfceditbrowsePath()
{
	validaClick(m_BrowsePath, 1);
}


void CDlgLoginRVIA::OnChangeMfceditbrowsePath()
{
	// TODO:  Si éste es un control RICHEDIT, el control no
	// enviará esta notificación a menos que se invalide CDialogEx::OnInitDialog()
	// función y llamada CRichEditCtrl().SetEventMask()
	// con la marca ENM_CHANGE ORed en la máscara.

	// TODO:  Agregue aquí el controlador de notificación de controles
}


void CDlgLoginRVIA::OnSetfocusComboMigVul()
{
	validaClick(m_CmbMigVul, 2);
}


void CDlgLoginRVIA::OnSelchangeComboMigVul()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}


void CDlgLoginRVIA::OnSetfocusComboCantEmp()
{
	validaClick(m_CboCantEmp, 3);
}


void CDlgLoginRVIA::OnSelchangeComboCantEmp()
{
	// TODO: Agregue aquí su código de controlador de notificación de control
}

bool CDlgLoginRVIA::conectaPG()
{
	bool bReturn = false;
	int  iRespuesta = -1;
	std::string  sSQL = STRING_EMPTY;
	std::string  sRoles = STRING_EMPTY;
	CString csResp;

	std::vector<ES_Records> vcstRecords;

	if (!pg.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
	{
		AfxMessageBox((CString)pg.getLastError());
		bReturn = false;
	}
	else
	{
		MessageBox(_T("CONEXION EXITOSA..."));
		bReturn = true;
		//pg.clearRecords();
		pg.closeConnection();
	}

	return bReturn;
}


std::string CDlgLoginRVIA::getMacAddress()
{
    std::string macAddress;

    IP_ADAPTER_INFO* adapterInfo = nullptr;
    ULONG bufferSize = 0;

    // Get the buffer size needed for the adapter information
    if (GetAdaptersInfo(adapterInfo, &bufferSize) == ERROR_BUFFER_OVERFLOW)
    {
        adapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(new char[bufferSize]);

        // Get the adapter information
        if (GetAdaptersInfo(adapterInfo, &bufferSize) == NO_ERROR)
        {
            IP_ADAPTER_INFO* adapter = adapterInfo;

            while (adapter)
            {
                if (adapter->Type == MIB_IF_TYPE_ETHERNET && adapter->AddressLength == 6)
                {
                    char mac[18];
                    sprintf_s(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
                        adapter->Address[0], adapter->Address[1], adapter->Address[2],
                        adapter->Address[3], adapter->Address[4], adapter->Address[5]);

                    macAddress = mac;
                    break;
                }

                adapter = adapter->Next;
            }
        }

        delete[] reinterpret_cast<char*>(adapterInfo);
    }

    return macAddress;
}

std::string CDlgLoginRVIA::getIPAddress()
{
    std::string ipAddress;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return ipAddress;
    }

    char hostName[256];
    if (gethostname(hostName, sizeof(hostName)) == 0)
    {
        struct addrinfo* result = nullptr;
        struct addrinfo* ptr = nullptr;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;

        if (getaddrinfo(hostName, nullptr, &hints, &result) == 0)
        {
            ptr = result;

            while (ptr != nullptr)
            {
                if (ptr->ai_family == AF_INET)
                {
                    char ip[INET_ADDRSTRLEN];
                    struct sockaddr_in* sockaddr = reinterpret_cast<struct sockaddr_in*>(ptr->ai_addr);
                    inet_ntop(AF_INET, &(sockaddr->sin_addr), ip, INET_ADDRSTRLEN);

                    ipAddress = ip;
                    break;
                }

                ptr = ptr->ai_next;
            }

            freeaddrinfo(result);
        }
    }

    WSACleanup();

    return ipAddress;
}

std::string CDlgLoginRVIA::getHostName()
{
    char hostName[256];
    if (gethostname(hostName, sizeof(hostName)) == 0)
    {
        return hostName;
    }

    return "";
}

void CDlgLoginRVIA::getSystemInformation()
{
    std::string macAddress	= getMacAddress();
    std::string ipAddress	= getIPAddress();
    std::string hostName	= getHostName();

    std::cout << "Mac Address: " << macAddress << std::endl;
    std::cout << "IP Address: " << ipAddress << std::endl;
    std::cout << "Host Name: " << hostName << std::endl;

	std::cout << std::endl;
}

//bool CDlgLoginRVIA::validarToken(long lNumColaborador, long& lRespuesta)
//{
//	bool bReturn = false;
//	lRespuesta = -1;
//	std::string  sSQL = STRING_EMPTY;
//	CString csResp;
//
//	std::vector<ES_Records> vcstRecords;
//
//	if (!pg.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
//	{
//		AfxMessageBox((CString)pg.getLastError());
//		bReturn = false;
//	}
//	else
//	{
//		bReturn = false;
//
//		sSQL.append(utils.stringFormat("SELECT fun_validarsiexistecolaborador( '%ld'::BIGINT );", lNumColaborador));
//
//		if (!pg.queryExec(sSQL.c_str(), SELECT_QUERY))
//		{
//			AfxMessageBox((CString)pg.getLastError());
//			bReturn = false;
//		}
//		else
//		{
//			pg.getRecords(vcstRecords);
//
//			for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
//			{
//				for (int j = 0; j < vcstRecords.size(); j++)
//				{
//					bReturn = true;
//					csResp.AppendFormat(j != (vcstRecords.size() - 1) ? L"%S|" : L"%S", vcstRecords[j].vcValues[i]);
//					lRespuesta = _wtoi(csResp);
//				}
//			}
//		}
//
//		sSQL = STRING_EMPTY;
//
//		pg.clearRecords();
//		pg.closeConnection();
//	}
//
//	return bReturn;
//}

//bool CDlgLoginRVIA::registrarColaboradorRV(long lNumColaborador, CString csNomColaborador, int iNumPuesto, int iNumCentro, int iNumProveedor, long lNumGerente, long lNumCoordinador, int& iRespuesta)
//{
//	bool bReturn = false;
//	iRespuesta = -1;
//	std::string  sSQL = STRING_EMPTY;
//	std::string  sRoles = STRING_EMPTY;
//	CString csResp;
//
//	std::vector<ES_Records> vcstRecords;
//
//	if (!pg.openConnection("checkattendancebyface", "syscheckattendancebyface", "a7a60ccbc507bcfad9e3da68abd7fe5d", "10.50.9.183"))
//	{
//		AfxMessageBox((CString)pg.getLastError());
//		bReturn = false;
//	}
//	else
//	{
//		//sSQL.append(utils.stringFormat("SELECT fun_registrarpersonalrv_test('%ld'::integer, '%S'::varchar, '%d'::smallint, '%d'::int, '%d'::smallint, '%ld'::bigint, '%ld'::bigint);", lNumColaborador, csNomColaborador, iNumPuesto, iNumCentro, iNumProveedor, lNumGerente, lNumCoordinador));
//		sSQL.append(utils.stringFormat("SELECT fun_registrarpersonalrv('%ld'::integer, '%S'::varchar, '%d'::smallint, '%d'::int, '%d'::smallint, '%ld'::bigint, '%ld'::bigint);", lNumColaborador, csNomColaborador, iNumPuesto, iNumCentro, iNumProveedor, lNumGerente, lNumCoordinador));
//
//		if (!pg.queryExec(sSQL.c_str(), SELECT_QUERY))
//		{
//			AfxMessageBox((CString)pg.getLastError());
//			bReturn = false;
//		}
//		else
//		{
//			bReturn = false;
//			pg.getRecords(vcstRecords);
//
//			for (int i = 0; i < vcstRecords[0].vcValues.size(); i++)
//			{
//				for (int j = 0; j < vcstRecords.size(); j++)
//				{
//					bReturn = true;
//					csResp.AppendFormat(j != (vcstRecords.size() - 1) ? L"%S|" : L"%S", vcstRecords[j].vcValues[i]);
//					iRespuesta = _wtoi(csResp);
//				}
//			}
//		}
//
//		pg.clearRecords();
//		pg.closeConnection();
//	}
//
//	vcstRecords.clear();
//
//	return bReturn;
//}

void CDlgLoginRVIA::OnTimer(UINT_PTR nIDEvent)
{
	char buffer[4096] = { 0 };

	DWORD bytesRead;
	if (ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0)
	{
		buffer[bytesRead] = 0;
		CString str;
		GetDlgItem(IDC_EDIT_PROMPT)->GetWindowText(str);
		str += buffer;
		GetDlgItem(IDC_EDIT_PROMPT)->SetWindowText(str);
	}

	CDialogEx::OnTimer(nIDEvent);
}
