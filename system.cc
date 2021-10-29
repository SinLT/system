#include <node.h>

#include <windows.h>
#include <winspool.h> 

#pragma comment(lib, "Winspool.lib")

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

static int getPrintNumber() {
	//获取所有打印机
	DWORD dwSize, dwPrinters;
	BOOL bSet = FALSE;
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 5, NULL, 0, &dwSize, &dwPrinters);
	BYTE* pBuffer = new BYTE[dwSize];
	EnumPrinters(PRINTER_ENUM_LOCAL, NULL, 5, pBuffer, dwSize, &dwSize, &dwPrinters);
	delete[] pBuffer;
	return dwPrinters;
}

void Method(const FunctionCallbackInfo<Value>& args) {
    int result = getPrintNumber();
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(result);
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "getPrintNumber", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
