/*****************************************************************************/
/**
* @file xil_mmu.h
*
* @addtogroup a9_mmu_apis Cortex A9 Processor MMU Functions
*
* MMU functions equip users to enable MMU, disable MMU and modify default
* memory attributes of MMU table as per the need.
*
******************************************************************************/

/***************************** Include Files *********************************/

#include "xil_mmu.h"

/************************** Function Prototypes ******************************/

void Xil_SetTlbAttributes(INTPTR Addr, u32 attrib)
{
    (void)Addr,
    (void)attrib;
}
void Xil_EnableMMU(void)
{}
void Xil_DisableMMU(void)
{}
void* Xil_MemMap(UINTPTR PhysAddr, size_t size, u32 flags)
{
    (void)PhysAddr;
    (void)size;
    (void)flags;
    return NULL; //*TODO fix.
}
