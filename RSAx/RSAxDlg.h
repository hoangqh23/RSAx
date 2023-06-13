
// RSAxDlg.h : header file
//

#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


// CRSAxDlg dialog
class CRSAxDlg : public CDialogEx
{
// Construction
public:
	CRSAxDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSAX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit edit_banro;
	CEdit edit_banma;
	CEdit edit_banma2;
	CEdit edit_banro2;
public:
	afx_msg void OnBnClickednutma();

	public:
		CString str_banro= _T("");
		CString str_banma= _T("");
		CString str_banma2 = _T("");
		CString str_banro2 = _T("");
		std::vector<__int64> banma;
		std::vector<__int64> banma2;
		std::vector<__int64> banro2;
		__int64 p;
		__int64 q;
		__int64  n;
		__int64 phiN;
		__int64 b;
		__int64 a;

public:
	bool isPrime(__int64 n);
	std::vector<__int64> stringToByteCode(const CString str);
	__int64 generateRandomPrime(__int64 min, __int64 max);
	__int64 gcd(__int64 a, __int64 b);
	__int64 ModInverse(__int64 a, __int64 m);
	__int64 CalculatePrivateKey(__int64 publicKey, __int64 phi);
	__int64 power_modulo(__int64 x, __int64 b, __int64 n);
	std::vector<__int64> encryptRSA(const std::vector<__int64>& byteCode, __int64 b, __int64 n);
	std::vector<__int64> decryptRSA(const std::vector<__int64>& banma, __int64 a, __int64 n);
	CString ByteCodeToString(const std::vector<__int64>& byteCode);
	int ConvertVietnameseToInteger(wchar_t currentChar);
	CStringW decodeIntegerToVietnamese(std::vector<__int64>& integerVal);
	void ReadFile(CString& str_banro);

	afx_msg void OnBnClickednutchuyen();
	afx_msg void OnBnClickednutgiai();
	afx_msg void OnEnChangetextbanma();

	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonLuuBanMa();
	afx_msg void OnBnClickedButtonFile2();
	afx_msg void OnBnClickedButtonLuubanro();
};
