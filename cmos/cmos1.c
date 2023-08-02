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
//�����롢�֡�ʱ���ܼ����ա��¡��겢��ʼ��
  UINT8 second = 0;
  UINT8 minute = 0;
  UINT8 hour = 0;
  UINT8 weekday = 0;
  UINT8 date = 0;
  UINT8 month = 0;
  UINT8 year = 0;
  
  while (flag < 10000) { 
  //д�����ݵ�ַ����ȡ����������ظ�����õı���
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
    Print (L"%02x/%02x/%02x %02x %02x:%02x:%02x\n", year,month,date,weekday,hour,minute,second);  //��ʮ��������ʾ��֮ǰ��������ʽ��ʾ�ϳ���
    MicroSecondDelay(1000*1000);  //ÿ��һ����ʾһ��
    gST->ConOut->ClearScreen(gST->ConOut);  //����
    flag++;
  } 
 
  return EFI_SUCCESS;
	
} 
