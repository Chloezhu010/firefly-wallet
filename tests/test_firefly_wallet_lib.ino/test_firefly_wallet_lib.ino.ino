#include "ethers.h"
#include "firefly_qrcode.h"
// #include "BluetoothSerial.h" // bluetooth classic
// #include "firefly_blecast.h" //TODO need to compatible with ESP32

// BluetoothSerial SerialBT; // bluetooth classic

void setup() {
  // initialize serial communication at 115200 baud
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== Firefly crypto lib test ===");
  // test ethers lib
  testEthersLib();

  // test qr code lib
  testQrCodeLib();

  // test ble lib
  testBleLib();
  // testBlecastLib();

}

void testEthersLib() {
  Serial.println("1. Test ethers library...");
  // test private key to address conversion
  uint8_t privateKey[32] = { // create 32-byte private key
    0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0,
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99
  };
  uint8_t address[20]; // ethereum address is 20 bytes
  // convert private key to address
  bool success = ethers_privateKeyToAddress(privateKey, address);
  if (success)
  {
    // print prefix 0x
    Serial.println("  Generate address: 0x");
    // loop through the 20 address bytes
    for (int i = 0; i < 20; i++) {
      // if byte is less than 0x10, add leading 0
      if (address[i] < 0x10)
        Serial.print("0");
      // else print the byte in hex
      Serial.print(address[i], HEX);
    }
    // print newline
    Serial.println();
    Serial.println("  ✅ Ethers library working!");
  } else
    Serial.println("  ❌ Ethers library failed!");

}

void testQrCodeLib() {
  Serial.println("2. Test qr code library...");
  // test qr code generation
  uint8_t qrBuffer[qrcode_getBufferSize(3)]; // allocate buffer for qr code
  QRCode qrcode; // create qr code struct
  // generate qr code
  int result = qrcode_initText(&qrcode, qrBuffer, 3, 0, "Hello Firefly");
  if (result == 0) {
    Serial.print("  QR code size: ");
    Serial.print(qrcode.size); // print qr code dimensions
    Serial.println("x" + String(qrcode.size)); // print as 29x29 format
    Serial.println("  ✅ Qr code library working!");
  } else {
    Serial.println("  ❌ Qr code library failed!");
  }
}

// bluetooth classic
// void testBleLib() {
//   Serial.println("3. Test BLE library...");
//   if (SerialBT.begin("BLE-test")) {
//     Serial.println("  ✅ BLE initialized successfully!");
//     Serial.println("  📱 Look for BLE-test to connect on your phone...");
//   } else {
//     Serial.println("  ❌ Failed to initialize BLE!");
//   }
// }

// void testBlecastLib() {
//   Serial.println("3. Test blecast library...");
//   // test blecast messgae structure
//   BLECastMessage message; // create blecast message struct
//   uint8_t key[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}; // AES encryption key

//   bool success = blecast_init(&message, key, buffer, 100); // init BLE with key and buffer
//   if (success) {
//     Serial.println("  Blecast message initialized!");
//   } else {
//     Serial.println("  ❌ Blecast message initialization failed!");
//   }
//   blecast_shutdown(&message); // shutdown BLE
// }

void loop() {
  // put your main code here, to run repeatedly:
  if (SerialBT.available()) {
    String message = SerialBT.readString();
    Serial.println("Received message: " + message);
    SerialBT.println("Echo: " + message);
  }
  delay(100);
}
