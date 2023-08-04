#include <Uefi.h>  
#include <Library/UefiLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h> 

 
#define Port80  0xC80 
 
EFI_STATUS EFIAPI UefiMain (	IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE  *SystemTable)
{
 
  UINT16 data = 0;
  IoWrite8(Port80,0x14) ;
  data = IoRead8 (Port80);    
  Print (L"%x\n", data);  
  return EFI_SUCCESS;
} 
 
 