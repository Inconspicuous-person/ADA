# DATA MCU DOCUMENTATION

NI - Not implemented yet (planned)

## SECTION 1 -- PURPOSE

The purpose of the data mcu is to have things such as json encoding and other resource intensive tasks. The stricter memory and clock speed boundaries will impact the system if where to only have one. This would increase latency in commands and possibly cause loss of communication and control.

## SECTION 2 -- CONNECTIONS

Connected to the data mcu at the current stage shall only be a serial link to the IO mcu (A maximum of 1Mbps) for offloading. No other connections shall be made to the to the DATA mcu.

## SECTION 3 -- FIRMWARE

The firmware on the DATA mcu shall be made as stream lined as possible to increase data processing rates. The firmware uses at the current stage ArduinoJson for encoding strings for sending. A csv string shall be provided to the MCU along with the other appropriate commands for encoding JSON. Other commands will provided to the MCU for other functions. When such a command is sent a "waitc" flag will be sent impling that the next serial packet will be data for the command sent. There are exceptions to this rule such as the "ACK" command. Such exceptions will be defined in the following section.

## SECTION 4 -- DEFINITIONS

### Commands

REQ - Request acknoledgment package - WAITC = FALSE, ACKED = FALSE
ACK - Acknoledgment package - WAITC = FALSE, ACKED = TRUE
ENCODE - Encode CSV TO JSON - WAITC = TRUE, ACKED = FALSE
DECODE - NI
