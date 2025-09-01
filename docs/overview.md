# Overview of firefly-wallet (old version)
## Reference link
- https://firefly.city/
- https://github.com/firefly/wallet
## Hardware architecture overview


## Key components
**1. Arduino Nano (ATmega328P) - The main microcontroller**
- Role: Central processing unit and coordinator
- Specs: 16MHz, 2KB SRAM, 32KB Flash storage
- Functions: Cryptographic operations, transaction processing, device orchestration
**2. nRF24L01+ Radio Module - 2.4GHz wireless communication**
- Role: Receives encrypted transaction data from iOS devices
- Interface: SPI communication (CE: Pin 9, CSN: Pin 10)
- Power: Critical - Must use 3.3V rail (5V will destroy it)
- Protocol: Custom BLECast protocol for secure message transmission
**3. 128x64 OLED Display (SSD1306)**
- Role: Visual interface for transaction confirmation and QR code display
- Interface: I2C communication (Address: 0x3C)
- Functions: Shows wallet address, transaction details, signature QR codes
**4. Tactile Button - 6mm x 6mm x 5mm**
- Role: User confirmation and navigation
- Interface: Digital input on Pin 2
- Functions: Transaction approval, pairing mode activation (long-press)
**5. EEPROM Storage - Internal to ATmega328P**
- Role: Persistent storage for sensitive data
- Contents: Private key checksum, wallet address, pairing secrets

## Hardware integration flow
Communication Interfaces:
- SPI Bus: Arduino ↔ nRF24L01+ for radio communication
- I2C Bus: Arduino ↔ OLED display for visual output
- GPIO: Digital pin for button input with debouncing

Operational Workflow:
- Startup Sequence:
    - Arduino initializes I2C display system
    - Generates/validates cached cryptographic data in EEPROM
    - Displays wallet address as QR code
    - Initializes nRF24L01+ radio for BLECast reception
- Transaction Processing:
    - Radio Reception: nRF24L01+ receives encrypted transaction chunks via BLECast protocol
    - Decryption: Arduino decrypts using stored pairing secret
    - Display: Transaction details shown on OLED for user review
    - Confirmation: User presses button to approve
    - Signing: Arduino performs ECDSA signing using private key
    - Output: Signature displayed as dual QR codes (R and S components)

