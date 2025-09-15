#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define JUDGE_SOF 0xA5
#define RX_BUFFER_SIZE 256

// ================= CRC16 Interface =================
extern uint16_t Get_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength, uint16_t wCRC);
extern uint8_t Verify_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);
extern void Append_CRC16_Check_Sum(uint8_t *pchMessage, uint32_t dwLength);


// ================== UART Receive Ring Buffer ==================
static uint8_t rxBuffer[RX_BUFFER_SIZE];
static volatile uint16_t rxWriteIndex = 0;
static volatile uint16_t rxReadIndex = 0;

// Simulate UART receive interrupt callback
void UART_Receive_IT(uint8_t data)
{
    // TODO
}

// Read a byte from the ring buffer
bool RingBuffer_Read(uint8_t *data)
{
    // TODO
}


// ================== Data Structure ==================
typedef struct {
    // TODO
} RobotStatus_t;

RobotStatus_t robot_status; // Global variable


// ================== Packet Decode ==================
#define HEADER_LEN 5  // SOF(2) + DataLen(2) + Seq(1)
#define HEADER_CRC_LEN 7 // Header+CRC16
#define MAX_PAYLOAD_LEN 64

bool Packet_Decode(void)
{
    // TODO
}


// ================== Main Function Test ==================
int main(void)
{
    // Simulate UART input packet (SOF=0xA5 0x00, Payload=RobotStatus)
    uint8_t example_packet[] = {
        0xA5, 0x00, // SOF
        0x06, 0x00, // DataLen=6
        0x01,       // Seq=1
        0x00, 0x00, // Header CRC (The example fills in 0, but it should be calculated in practice)
        // Payload
        0x01, 0x00, // robot_id=1
        0x64, 0x00, // current_HP=100
        0xC8, 0x00, // max_HP=200
        0x00, 0x00  // Packet CRC (The example fills in 0, but it should be calculated in practice)
    };

    // Simulate UART receive
    for (int i = 0; i < sizeof(example_packet); i++) {
        UART_Receive_IT(example_packet[i]);
    }

    // Attempt to decode packet
    while (Packet_Decode());

    return 0;
}
