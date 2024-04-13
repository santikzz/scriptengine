#pragma once
#include <Windows.h>

typedef int(__stdcall* lpfun_DD_todc)(int);
typedef int(__stdcall* lpfun_DD_btn)(int btn);
typedef int(__stdcall* lpfun_DD_mov)(int x, int y);
typedef int(__stdcall* lpfun_DD_movR)(int dx, int dy);
typedef int(__stdcall* lpfun_DD_whl)(int whl);
typedef int(__stdcall* lpfun_DD_key)(int code, int flag);
typedef int(__stdcall* lpfun_DD_str)(char* str);

HINSTANCE hinst = LoadLibraryW(L"ddxoft.dll");

lpfun_DD_todc dd_todc = (lpfun_DD_todc)GetProcAddress(hinst, "DD_todc");
lpfun_DD_btn dd_btn = (lpfun_DD_btn)GetProcAddress(hinst, "DD_btn");
lpfun_DD_mov dd_mov = (lpfun_DD_mov)GetProcAddress(hinst, "DD_mov");
lpfun_DD_movR dd_movR = (lpfun_DD_mov)GetProcAddress(hinst, "DD_movR");
lpfun_DD_whl dd_whl = (lpfun_DD_whl)GetProcAddress(hinst, "DD_whl");
lpfun_DD_key dd_key = (lpfun_DD_key)GetProcAddress(hinst, "DD_key");
lpfun_DD_str dd_str = (lpfun_DD_str)GetProcAddress(hinst, "DD_str");

int driver_init() {
    if (!hinst) {
        return 0;
    }

    int st = dd_btn(0); //DD Initialize
    if (st != 1) {
        return 0;
    }
    return 1;
}


void driver_MoveAbsolute(int x, int y) {
    dd_mov(x, y);
}

void driver_MoveRelative(int x, int y) {
    
    // fix x,y weird glitch on 129 threshold
    if (x <= -129)
        x = -x;
    else if (x >= 129)
        x = -x;

    if (y <= -129) 
        y = -y;
    else if (y >= 129)
        y = -y;
   
    dd_movR(x, y);
}

void driver_MouseButton(int btn) {
    dd_btn(btn);
}

void driver_Key(int vkcode, bool state) {
    
    int flag = state ? 1 : 2;
    int ddCode = dd_todc(vkcode);
    dd_key(ddCode, flag);
}