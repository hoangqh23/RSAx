
// RSAxDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RSAx.h"
#include "RSAxDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <afxdlgs.h>
#include <afx.h>
#include <io.h>
#include <fcntl.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
CRSAxDlg::CRSAxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSAX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRSAxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_text_banro, edit_banro);
	DDX_Control(pDX, IDC_text_banma, edit_banma);
	DDX_Control(pDX, IDC_text_banma2, edit_banma2);
	DDX_Control(pDX, IDC_text_banro2, edit_banro2);
	
}

BEGIN_MESSAGE_MAP(CRSAxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_nut_ma, &CRSAxDlg::OnBnClickednutma)
	ON_BN_CLICKED(IDC_nut_chuyen, &CRSAxDlg::OnBnClickednutchuyen)
	ON_BN_CLICKED(IDC_nut_giai, &CRSAxDlg::OnBnClickednutgiai)
	ON_EN_CHANGE(IDC_text_banma, &CRSAxDlg::OnEnChangetextbanma)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CRSAxDlg::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_LUU_BAN_MA, &CRSAxDlg::OnBnClickedButtonLuuBanMa)
	ON_BN_CLICKED(IDC_BUTTON_FILE2, &CRSAxDlg::OnBnClickedButtonFile2)
	ON_BN_CLICKED(IDC_BUTTON_LuuBanRo, &CRSAxDlg::OnBnClickedButtonLuubanro)
END_MESSAGE_MAP()


// CRSAxDlg message handlers

BOOL CRSAxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRSAxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRSAxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRSAxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRSAxDlg::OnBnClickedButtonFile()
{
	// TODO: Add your control notification handler code here
	ReadFile(str_banro);
			edit_banro.SetWindowText(str_banro);
}

void CRSAxDlg::OnBnClickednutma()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	edit_banro.GetWindowText(str_banro);

	srand(time(0));
	 p = generateRandomPrime(10000, 100000); // tao p ngau nhien
	 q = generateRandomPrime(10000, 100000); // tao q ngau nhien

	std::vector<__int64> byteCode ;
	for (int i = 0; i < str_banro.GetLength(); i++)
	{
		wchar_t currentChar = str_banro.GetAt(i);
		int x = ConvertVietnameseToInteger(currentChar);
		byteCode.push_back(x);
	}
	  n = p * q;       // tinh n

	 phiN = (p - 1) * (q - 1);   // tinh phiN 

	 
	do {
		b = generateRandomPrime(2, phiN);     // chon b 
	} while (gcd(b, phiN) != 1);

	 a = CalculatePrivateKey(b, phiN);  // tinh a

	// chuoi sau khi duoc ma hoa	
	banma = encryptRSA(byteCode, b, n);
	str_banma.Empty();
	CString strNum;
	for (const auto& num : banma) {
		strNum.Format(_T("%lld"), num);
		str_banma += strNum;
	}
	edit_banma.SetWindowText(str_banma);
	UpdateData(FALSE);
}

void CRSAxDlg::OnBnClickednutchuyen()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	str_banma2 = str_banma;
	edit_banma2.SetWindowText(str_banma2);
	banma2 = banma;
	UpdateData(FALSE);
}

void CRSAxDlg::OnBnClickednutgiai()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	banro2 = decryptRSA(banma2, a, n);
	CString a = decodeIntegerToVietnamese(banro2);
	edit_banro2.SetWindowText(a);
	UpdateData(FALSE);
}
void CRSAxDlg::OnEnChangetextbanma()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CRSAxDlg::OnBnClickedButtonLuuBanMa()
{
	// TODO: Add your control notification handler code here
	CString strFileName;
	CString strDefaultExt = _T("txt"); // Phần mở rộng tệp mặc định
	CFileDialog dlg(FALSE, strDefaultExt, NULL, OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt||")); // Tạo cửa sổ lưu file
	if (dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetPathName(); // Lấy đường dẫn tệp lưu

		CFile file;
		if (file.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
		{
			CStringA strContent(str_banma); // Chuyển đổi CString sang CStringA
			file.Write(strContent, strContent.GetLength()); // Ghi nội dung văn bản vào tệp
			file.Close();
		}
	}
}

void CRSAxDlg::OnBnClickedButtonFile2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFileDialog dlg(TRUE); // Tạo cửa sổ chọn file
	if (dlg.DoModal() == IDOK)
	{
		CString strFileName;
		strFileName = dlg.GetPathName(); // Lấy đường dẫn tệp được chọn
		CFile file;
		if (file.Open(strFileName, CFile::modeRead))
		{
			ULONGLONG dwLength = file.GetLength(); // Lấy kích thước tệp
			CStringA strContent;
			strContent.GetBufferSetLength(dwLength);

			// Đọc nội dung văn bản từ tệp
			file.Read(strContent.GetBuffer(), dwLength);
			strContent.ReleaseBuffer();
			file.Close();
			// Gán giá trị cho biến str_banro
			str_banma2 = CString(strContent);
		}
	}
	__int64 length = str_banma2.GetLength();
	int startPos = 0;
	int chunkSize = 9;
	while (startPos < length)
	{
		CString strNumber = str_banma2.Mid(startPos, chunkSize); // Lấy một phần chuỗi số có độ dài 9
		__int64 number = _ttoi64(strNumber);
		banma2.push_back(number); 
		startPos += chunkSize;
	}
	edit_banro2.SetWindowText(_T(""));
	UpdateData(FALSE);
}

void CRSAxDlg::OnBnClickedButtonLuubanro()
{
	// TODO: Add your control notification handler code here
	CString strFileName;
	CString strDefaultExt = _T("txt"); // Phần mở rộng tệp mặc định
	CFileDialog dlg(FALSE, strDefaultExt, NULL, OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt||")); // Tạo cửa sổ lưu file

	if (dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetPathName(); // Lấy đường dẫn tệp lưu

		CFile file;
		if (file.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
		{
			CStringA strContent(str_banro2); // Chuyển đổi CString sang CStringA
			file.Write(strContent, strContent.GetLength()); // Ghi nội dung văn bản vào tệp
			file.Close();
		}
	}
}
// cac ham thuat toan


// Hàm kiểm tra tính nguyên tố của một số
bool CRSAxDlg::isPrime(__int64 n) {
	if (n <= 1) {
		return false;
	}

	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

// Hàm tạo số nguyên tố ngẫu nhiên trong khoảng [min, max]
__int64 CRSAxDlg::generateRandomPrime(__int64 min, __int64 max) {
	__int64 num;
	do {
		num = min + rand() % (max - min + 1);
	} while (!isPrime(num));

	return num;
}

// Hàm tính gcd của hai số a và b
__int64 CRSAxDlg::gcd(__int64 a, __int64 b) {

	if (b == 0) {
		return a;
	}
	else
		return gcd(b, a % b);
}

// Hàm tính phần tử nghịch đảo modulo
__int64 CRSAxDlg::ModInverse(__int64 a, __int64 m)
{
	__int64 m0 = m;
	__int64 y = 0;
	__int64 x = 1;

	if (m == 1)
		return 0;

	while (a > 1)
	{
		__int64 q = a / m;
		__int64 t = m;

		m = a % m;
		a = t;
		t = y;

		y = x - q * y;
		x = t;
	}

	if (x < 0)
		x += m0;

	return x;
}
__int64 CRSAxDlg::CalculatePrivateKey(__int64 publicKey, __int64 phi)
{
	__int64 privateKey = ModInverse(publicKey, phi);
	return privateKey;
}

// 
int CRSAxDlg::ConvertVietnameseToInteger(wchar_t currentChar)
{
	const wchar_t* characterMapping = L" aáàảãạăắằẳẵặâấầẩẫậbcdđeéèẻẽẹêếềểễệghiíìỉĩịklmnopóòỏõọôốồổỗộơớờởỡợpqrstuúùủũụưứừửữựvxyýỳỷỹỵAÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬBCDĐEÉÈẺẼẸÊẾỀỂỄỆGHIÍÌỈĨỊKLMNOÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢPQRSTUÚÙỦŨỤƯỨỪỬỮỰVXYÝỲỶỸỴ`1234567890-=~!@#$%^&*()_+[];',./{}|:<>?\"\\";
	const int integerMapping[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222 ,223, 224 };

	int result = 0;

	const wchar_t* foundChar = wcschr(characterMapping, currentChar);
	if (foundChar != nullptr)
	{
		int mappingIndex = foundChar - characterMapping;
		result += integerMapping[mappingIndex];
	}
	return result;
}

// Hàm tính công thức bình phương và nhân modulo
__int64 CRSAxDlg::power_modulo(__int64 x, __int64 b, __int64 n)
{
	if (b == 0)
	{
		return 1;
	}
	if (b == 1)
	{
		return x % n;
	}
	__int64 t = power_modulo(x, b / 2, n);
	t = (t * t) % n;
	if (b % 2 == 0)
		return t;
	else
		return ((x % n) * t) % n;
}

// Hàm mã hóa RSA
std::vector<__int64>  CRSAxDlg::encryptRSA(const std::vector<__int64>& byteCode, __int64 b, __int64 n)
{
	std::vector<__int64> banma;
	for (int i = 0; i <= byteCode.size() - 1; i++)
	{
		__int64 encryptedValue = power_modulo(byteCode[i], b, n);
		banma.emplace_back(encryptedValue);
	}

	return banma;
}

// Hàm giai ma RSA
std::vector<__int64> CRSAxDlg::decryptRSA(const std::vector<__int64>& banma, __int64 a, __int64 n)
{
	std::vector<__int64> banro;
	for (int i = 0; i <= banma.size() - 1; i++)
	{
		__int64 decryptedValue = power_modulo(banma[i], a, n);
		banro.emplace_back(decryptedValue);
	}

	return banro;
}
//hàm chuyển integer sang kí tự
CStringW CRSAxDlg::decodeIntegerToVietnamese(std::vector<__int64>& integerVal)
{
	const int integerMapping[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222 ,223, 224 };
	const wchar_t* characterMapping = L" aáàảãạăắằẳẵặâấầẩẫậbcdđeéèẻẽẹêếềểễệghiíìỉĩịklmnopóòỏõọôốồổỗộơớờởỡợpqrstuúùủũụưứừửữựvxyýỳỷỹỵAÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬBCDĐEÉÈẺẼẸÊẾỀỂỄỆGHIÍÌỈĨỊKLMNOÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢPQRSTUÚÙỦŨỤƯỨỪỬỮỰVXYÝỲỶỸỴ`1234567890-=~!@#$%^&*()_+[];',./{}|:<>?\"\\";

	CStringW result;

	for (int i = 0; i < integerVal.size(); i++)
	{
		int integerValue = integerVal[i];

		for (int j = 0; j < sizeof(integerMapping) / sizeof(integerMapping[0]); j++)
		{
			if (integerValue == integerMapping[j])
			{
				result.AppendChar(characterMapping[j]);
				break;
			}
		}
	}

	return result;
}

void CRSAxDlg::ReadFile(CString& str_banro)
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("Text files (*.txt)|*.txt|All Files (*.*)|*.*||"), this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();

		CFile file;
		if (file.Open(filePath, CFile::modeRead))
		{
			UINT fileSize = (UINT)file.GetLength();
			char* fileData = new char[fileSize + 1];
			file.Read(fileData, fileSize);
			fileData[fileSize] = '\0';
			CString fileContent(CA2W(fileData, CP_UTF8));
			delete[] fileData;
			str_banro = fileContent;
			
		}

	}
	edit_banro.SetWindowText(str_banro);
}