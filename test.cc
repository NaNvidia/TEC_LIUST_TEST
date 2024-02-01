#include<iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef int(*TECUSB_Open)();
typedef HANDLE(*TECUSB_OpenPipe)(int,int,int,int);
typedef int(*TECUSB_Check)(int);
typedef void(*TECUSB_Close)(int);
typedef BOOL(*TECUSB_ResetDevice)(int);


int main(void){
    int val,tmp,i;
    HANDLE liu0,liu1;
    int buffer;
    char wbf[1024] = "\0";
    DWORD nwrite = 1024;
    DWORD nwritn = 0;

    HMODULE TECUSB ;
    TECUSB = LoadLibrary("TECUSB.dll");
    TECUSB_Open TECUSB_Open_0 = (TECUSB_Open)GetProcAddress(TECUSB,"TECUSB_Open");
    TECUSB_OpenPipe TECUSB_OpenPipe_0 = (TECUSB_OpenPipe)GetProcAddress(TECUSB,"TECUSB_OpenPipe");
    TECUSB_Check TECUSB_Check_0 = (TECUSB_Check)GetProcAddress(TECUSB,"TECUSB_Check");
    TECUSB_Close TECUSB_Close_0 = (TECUSB_Close)GetProcAddress(TECUSB,"TECUSB_Close");
    TECUSB_ResetDevice TECUSB_ResetDevice_0 = (TECUSB_ResetDevice)GetProcAddress(TECUSB,"TECUSB_ResetDevice");

    val = TECUSB_Open_0();
    if(val != -1){
        std::cout << "TECUSB device is opened -> " << val  << std::endl;
        if(TECUSB_ResetDevice_0(val))
            std::cout << "DEVICE INITIALED OK " << std::endl;
        else
            std::cout << "DEVICE INITIALED FAIL " << std::endl;
    }
    else if(val = -1)std::cout << "TECUSB device open FAILED" << std::endl;

    std::cout << "TECUSBUSB Check : " << TECUSB_Check_0(val) << std::endl;

    liu0 = TECUSB_OpenPipe_0(val,0,0,0);
    liu1 = TECUSB_OpenPipe_0(val,0,1,0);
    std::cout << "TECUSBUSB HANDLE 0 : " << liu0 << std::endl;
    std::cout << "TECUSBUSB HANDLE 1 : " << liu1 << std::endl;

 OVERLAPPED ovl;

//line mode select
    snprintf(wbf,1024,"\033\\?LS4");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    

//brightness
    snprintf(wbf,1024,"\033\\?LD5");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);  


//set country code
    snprintf(wbf,64,"\033R63");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));

//cleardisplay
    snprintf(wbf,1024,"\033[2J");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));


//setcursor
    snprintf(wbf,1024,"\033[1;1H");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf)); 

//x0A LF
//x9D CR

    snprintf(wbf,1024,"\033[2J");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));
    snprintf(wbf,1024,"");
    tmp = WriteFile(liu1,&wbf,nwrite,&nwritn,NULL);    
    memset(wbf, '\0', sizeof(wbf));


    tmp = CloseHandle(liu0);
    if(tmp != 0)std::cout <<"liu0 CLOSE OK"<< std::endl;
    tmp = CloseHandle(liu1);
    if(tmp != 0)std::cout <<"liu1 CLOSE OK"<< std::endl;
    TECUSB_Close_0(val);

    FreeLibrary(TECUSB);
    return 0;
}
