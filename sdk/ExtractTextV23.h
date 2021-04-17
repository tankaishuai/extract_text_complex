#pragma once

extern "C"
{
  //提取文本（自动识别格式）, ExtractText2.dll提供:
  int ExtractDocumentTextA(const char *filePath, char *bufPtr, unsigned long bufSize);

  //提取特殊格式文本
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

  //直接读取文件
  int ExtractFileAnsiTextA(const char *filePath, char *bufPtr, unsigned long bufSize);
  int ExtractFileAnsiTextW(const wchar_t *filePath, wchar_t *bufPtr, unsigned long bufSize);

  //ExtractRarFileDataA
  //ExtractZipFileDataA
}

extern "C++"
{
  //ExtractText3.dll提供： 
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
