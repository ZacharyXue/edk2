// Ref: https://blog.csdn.net/xiaopangzi313/article/details/89602882
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/PeimEntryPoint.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Pi/PiHob.h>
#include <Pi/PiPeiCis.h>

EFI_GUID gMyPpiGUID = { 
    0xbdb38129, 0x4d65, 0x39f4, 
    { 0x72, 0x12, 0x68, 0xcf, 0x5a, 0x19, 0xa, 0xf8 }
};

EFI_STATUS
EFIAPI
PrintHelloMsg (
    IN CHAR16* Msg
)
{
    DEBUG((EFI_D_ERROR, "[MyPpiInstall] PrintHelloMsg: %s\n", Msg));
    return EFI_SUCCESS;
}


typedef EFI_STATUS (EFIAPI* PRINTMSG)(CHAR16 *Msg);
typedef struct _EFI_HELLOWORLD_PROTOCOL {
    PRINTMSG PrintMsg;
}EFI_HELLOWORLD_PROTOCOL;

EFI_HELLOWORLD_PROTOCOL mHelloworldPpi = {
    PrintHelloMsg
};

EFI_PEI_PPI_DESCRIPTOR mPpiListCodePpi = {
    (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gMyPpiGUID,
    &mHelloworldPpi
};

//ShellCEntryLib call user interface ShellAppMain
EFI_STATUS
EFIAPI 
MyPpiInstallEntry(
    IN EFI_PEI_FILE_HANDLE FileHandle,
    IN CONST EFI_PEI_SERVICES **PeiServices
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    DEBUG ((EFI_D_ERROR, "[MyPpiInstall] MyPpiInstallEntry Start..\n"));
    PeiServicesInstallPpi  (&mPpiListCodePpi);
    DEBUG ((EFI_D_ERROR, "[MyPpiInstall] MyPpiInstallEntry End..\n"));

    return Status;
}
