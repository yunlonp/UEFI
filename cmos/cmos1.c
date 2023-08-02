#include <Uefi.h>  
#include <Library/UefiLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h> 

 
#define CMOS_INDEX    0x70
#define CMOS_DATA     0x71 
 
EFI_STATUS EFIAPI UefiMain (	IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE  *SystemTable)
{
  UINT32 flag = 0;
//定义秒、分、时、周几、日、月、年并初始化
  UINT8 second = 0;
  UINT8 minute = 0;
  UINT8 hour = 0;
  UINT8 weekday = 0;
  UINT8 date = 0;
  UINT8 month = 0;
  UINT8 year = 0;
  
  while (flag < 10000) { 
  //写入数据地址并读取，将结果返回给定义好的变量
    IoWrite8 (CMOS_INDEX, 0x00); 
    second = IoRead8 (CMOS_DATA);    
    IoWrite8 (CMOS_INDEX, 0x02); 
    minute = IoRead8 (CMOS_DATA);
    IoWrite8 (CMOS_INDEX, 0x04); 
    hour = IoRead8 (CMOS_DATA);
    IoWrite8 (CMOS_INDEX, 0x06); 
    weekday = IoRead8 (CMOS_DATA);
    IoWrite8 (CMOS_INDEX, 0x07); 
    date = IoRead8 (CMOS_DATA);
    IoWrite8 (CMOS_INDEX, 0x08); 
    month = IoRead8 (CMOS_DATA);
    IoWrite8 (CMOS_INDEX, 0x09); 
    year = IoRead8 (CMOS_DATA); 
    Print (L"%02x/%02x/%02x %02x %02x:%02x:%02x\n", year,month,date,weekday,hour,minute,second);  //用十六进制显示，之前用其他格式显示老出错
    MicroSecondDelay(1000*1000);  //每隔一秒显示一次
    gST->ConOut->ClearScreen(gST->ConOut);  //清屏
    flag++;
  } 
 
  return EFI_SUCCESS;
	
} 
