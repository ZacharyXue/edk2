// Ref https://blog.csdn.net/xiaopangzi313/article/details/89602882

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

EFI_GUID gMyPpiGUID = { 
    0xbdb38129, 0x4d65, 0x39f4, 
    { 0x72, 0x12, 0x68, 0xcf, 0x5a, 0x19, 0xa, 0xf8 }
};

/*
    1. 定义一个函数指针，使用 typedef 重命名
    2. 初始化协议结构，使用第1步函数指针
*/
typedef EFI_STATUS (EFIAPI* PRINTMSG)(CHAR16 *Msg);
typedef struct _EFI_HELLOWORLD_PROTOCOL {
    PRINTMSG PrintMsg;
}EFI_HELLOWORLD_PROTOCOL;

//ShellCEntryLib call user interface ShellAppMain
EFI_STATUS
EFIAPI 
MyPpiLocateEntry(
    IN EFI_PEI_FILE_HANDLE FileHandle,
    IN CONST EFI_PEI_SERVICES **PeiServices
)
{
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_HELLOWORLD_PROTOCOL* mHelloWorldPpi = NULL;
    DEBUG((EFI_D_ERROR, "[MyPpiLocate] MyPpiLocateEntry Locate PPI start.. \n"));
    Status = PeiServicesLocatePpi (
        &gMyPpiGUID,
        0,
        NULL,
        (void **)&mHelloWorldPpi
    );
    if(EFI_ERROR(Status)){
        DEBUG((EFI_D_ERROR, "[MyPpiLocate] MyPpiLocateEntry Locate PPI fail.. %r\n", Status));
        return Status;
    }
    mHelloWorldPpi->PrintMsg(L"No job to do, worried.. \n");
    DEBUG((EFI_D_ERROR, "[MyPpiLocate] MyPpiLocateEntry Locate PPI end.. \n"));

    return Status;
}