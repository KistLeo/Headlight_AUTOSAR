#include "BSW/ECU_Abstraction/COMAbstraction/VehicleState_CanRx.h"
#include <stddef.h>
#include "BSW/Services/Pdu_Router.h"




#define MAX_PDU 2  

/* Bộ nhớ tạm lưu dữ liệu CAN */
static uint8_t canRxBuffer[MAX_PDU][8];  // Giữ dữ liệu từng PDU
static uint8_t canRxBufferSize[MAX_PDU]; // Giữ độ dài dữ liệu của từng PDU

void CanIf_RxIndication(const Can_HwType* Mailbox, const PduInfoType* PduInfoPtr)
{


    /* Duyệt danh sách Rx PDU để tìm CAN ID phù hợp */
    for (uint8_t i = 0; i < CanIfConfig.RxPduCount; i++) {
        if (CanIfConfig.RxPduConfig[i].CanId == Mailbox->CanId) {
            const CanIf_RxPduConfigType* rxPdu = &CanIfConfig.RxPduConfig[i];  // Giữ `const`

            if (!rxPdu->ReadDataEnabled) {
                return; // Nếu không cho phép đọc, thoát sớm
            }

            /* Sao chép dữ liệu vào buffer tạm */
            uint8_t copyLength = (PduInfoPtr->SduLength <= sizeof(canRxBuffer[i])) 
                                ? PduInfoPtr->SduLength 
                                : sizeof(canRxBuffer[i]);

            memcpy(canRxBuffer[i], PduInfoPtr->SduDataPtr, copyLength);
            canRxBufferSize[i] = copyLength;  // Lưu kích thước dữ liệu

            return;
        }
    }
}



Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxPduId, PduInfoType* PduInfoPtr)
{


    const CanIf_RxPduConfigType* rxPdu = &CanIfConfig.RxPduConfig[CanIfRxPduId];

    if (!rxPdu->ReadDataEnabled || canRxBufferSize[CanIfRxPduId] == 0) {
        return E_NOT_OK; // Không có dữ liệu
    }

    /* Trả dữ liệu từ buffer tạm */
    PduInfoPtr->SduDataPtr = canRxBuffer[CanIfRxPduId];
    PduInfoPtr->SduLength = canRxBufferSize[CanIfRxPduId];
    PduR_RxIndication(CanIfRxPduId, PduInfoPtr);
    return E_OK;
}
