#include "ethers.h"
#include "firefly_qrcode.h"
// #include "firefly_blecast.h": TODO need to compatible with ESP32

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== Firefly crypto lib test ===");
  // test ethers lib
  testEthersLib();

  // test qr code lib

  // test blecast lib


}

void testEthersLib() {
  Serial.println("1. Test ethers library...");
  // test private key to address conversion
  uint8_t privateKey[32] = {
    0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0,
    0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
    0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11,
    0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99
  };
  uint8_t address[20];
  bool success = ethers_privateKeyToAddress(privateKey, address);
  if (success)
  {
    Serial.println("  Generate address: 0x");
    for (int i = 0; i < 20; i++) {
      if (address[i] < 0x10)
        Serial.print("0");
      Serial.print(address[i], HEX);
    }
    Serial.println();
    Serial.println("  ✅ Ethers library working!");
  } else
    Serial.println("  ❌ Ethers library failed!");

}

void loop() {
  // put your main code here, to run repeatedly:

}
