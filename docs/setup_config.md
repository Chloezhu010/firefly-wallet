# ESP32
```
Power:
├── 3.3V → OLED VCC
├── GND  → Common ground
└── VIN  → External power input (optional)

I2C (for OLED):
├── GPIO21 → SDA (OLED data)
└── GPIO22 → SCL (OLED clock)

Digital I/O:
├── GPIO2  → Built-in LED + Button input
├── GPIO4  → Available for button
└── GPIO5  → Available for additional features

Bluetooth:
└── Built-in (no external pins needed!)
```