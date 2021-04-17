#pragma once

extern "C"
{
  //��ȡ�ı����Զ�ʶ���ʽ��, ExtractText2.dll�ṩ:
  int ExtractDocumentTextA(const char *filePath, char *bufPtr, unsigned long bufSize);

  //��ȡ�����ʽ�ı�
  int ExtractChmTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractOffice2003TextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractOffice2007TextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractOffice2007DocxTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractOffice2007PptxTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractOffice2007XlsxTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractPdfTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractRtfTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractXmlTextW(const wchar_t *filePath, wchar_t *bufPtr, unsigned long bufSize);
  int _ExtractXmlTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int pdfGet_text_buf(const char *filePath, char *bufPtr, unsigned long bufSize);
  int rtfGet_text_buf(const char *filePath, char *bufPtr, unsigned long bufSize);

  //ֱ�Ӷ�ȡ�ļ�
  int ExtractFileAnsiTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractFileAnsiTextW(const wchar_t *filePath, wchar_t *bufPtr, unsigned long bufSize);

  //ExtractRarFileDataA
  //ExtractZipFileDataA
}

extern "C++"
{
  //ExtractText3.dll�ṩ�� 
  int hlpGet_text_buf(const char *filePath, char *bufPtr, unsigned long bufSize);
  int rtfGet_text_buf2(const char *filePath, char *bufPtr, unsigned long bufSize);
}

typedef int (*ExtractDocumentTextA_t)(const char *filePath, char *bufPtr, unsigned long bufSize);

static BOOL ExtractText_Register()
{
  HMODULE hDll = LoadLibraryW(L"ExtractText.dll");
  if (!hDll)
    return FALSE;
  FARPROC pfnDllRegisterServer = GetProcAddress(hDll, "DllRegisterServer");
  HRESULT hr = pfnDllRegisterServer();
  return SUCCEEDED(hr);
}
