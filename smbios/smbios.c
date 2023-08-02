#include <Uefi.h>  
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#include <Library/UefiApplicationEntryPoint.h>
#include <IndustryStandard/SmBios.h>
#include <IndustryStandard/SmBios.h>


#define EFI_SMBIOS3_TABLE_GUID \
{ \
    0xf2fd1544, 0x9794, 0x4a2c, {0x99, 0x2e, 0xe5, 0xbb, 0xcf, 0x20, 0xe3, 0x94} \
}


EFI_GUID gEfiSmbiosTable3Guid = EFI_SMBIOS3_TABLE_GUID;

STATIC SMBIOS_STRUCTURE_POINTER         m_SmbiosStruct;
STATIC SMBIOS_STRUCTURE_POINTER         *mSmbiosStruct = &m_SmbiosStruct;   //用引用进行初始化，否则运行会卡退
STATIC SMBIOS_TABLE_3_0_ENTRY_POINT     *SmbiosTable   = NULL; 

CHAR8*
EFIAPI
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  );




CHAR8*
LibGetSmbiosString (
  IN  SMBIOS_STRUCTURE_POINTER    *Smbios,
  IN  UINT16                      StringNumber
  )
{
  UINT16  Index;
  CHAR8   *String;

  ASSERT (Smbios != NULL);

  //
  // Skip over formatted section
  //
  String = (CHAR8 *) (Smbios->Raw + Smbios->Hdr->Length);

  //
  // Look through unformated section
  //
  for (Index = 1; Index <= StringNumber; Index++) {
    if (StringNumber == Index) {
      return String;
    }
    //
    // Skip string
    //
    for (; *String != 0; String++);
    String++;  //这一句和上一句是分开的

    if (*String == 0) {
      //
      // If double NULL then we are done.
      //  Return pointer to next structure in Smbios.
      //  if you pass in a -1 you will always get here
      //
      Smbios->Raw = (UINT8 *)++String;
      return NULL;
    }
  }

  return NULL;
}






EFI_STATUS EFIAPI UefiMain (	IN EFI_HANDLE ImageHandle,IN EFI_SYSTEM_TABLE  *SystemTable)
{

	EFI_STATUS Status ;
	SMBIOS_STRUCTURE_POINTER SmBiosStruct;
	//UINT32 address;

   //1 . 获取smbios 表地址
	Status = EfiGetSystemConfigurationTable (&gEfiSmbiosTable3Guid, &SmbiosTable);
   
    Print (L"SmBios Table:\n");
    Print (L"  AnchorString:%c%c%c%c%c\n  EntryPointStructureChecksum:0x%x\n  EntryPointLength:0x%x\n  MajorVersion:0x%x\n  MinorVersion:0x%x\n  TableAddress:0x%x\n",  
          SmbiosTable->AnchorString[0],
          SmbiosTable->AnchorString[1],
          SmbiosTable->AnchorString[2],
          SmbiosTable->AnchorString[3],
          SmbiosTable->AnchorString[4],
          SmbiosTable->EntryPointStructureChecksum,
          SmbiosTable->EntryPointLength,
          SmbiosTable->MajorVersion,
          SmbiosTable->MinorVersion,
          SmbiosTable->TableAddress
          );
	mSmbiosStruct->Raw	= (UINT8 *) (UINTN) (SmbiosTable->TableAddress);
	SmBiosStruct.Raw = mSmbiosStruct->Raw;
	while(1)
	{
        if(SmBiosStruct.Hdr->Handle == 0xFEFF)
		{ 
		   //当到Type127时break
           break;
        }

		if(SmBiosStruct.Hdr->Type == 0x09)
		{
             Print(L"The Second Type9's handle:0x%x\n",SmBiosStruct.Hdr->Handle);
		}

		LibGetSmbiosString (&SmBiosStruct, (UINT16) (-1)); 
	}
	
    return EFI_SUCCESS;
	
}

