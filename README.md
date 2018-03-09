# RFID Music Box


## Components
* RFID-RC522 - on [AliExpress](https://de.aliexpress.com/item/RC522-Card-Read-Antenna-RFID-Reader-IC-Card-Proximity-Module/1859133832.html) ~ $ 1.50
* PAM8403 - on [AliExpress](https://de.aliexpress.com/item/PAM8403-5V-Power-Audio-Amplifier-Board-2-Channel-3W-W-Volume-Control-USB-Power/32525351819.html) ~ $ 0.60
* [DFPlayer Mini](https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299) - on [AliExpress](https://de.aliexpress.com/item/TF-Card-U-Disk-Mini-MP3-Player-Audio-Voice-Module-For-Arduino-DFPlay-Min-Board/32659645208.html) ~ $ 1.30
* [Arduino Nano](https://store.arduino.cc/usa/arduino-nano) - on [AliExpress](https://de.aliexpress.com/item/Nano-V3-0-3-0-ATmega168-CH340G-CH340-Mini-USB-UART-Schnittstellenkarte-Micro-controller-Modul-F/32674278303.html)  ~ $ 2
* Speakers - on [AliExpress](https://de.aliexpress.com/item/2pcs-lot-4-ohm-3W-3Watts-53MM-Square-Speaker-36MM-External-Magnetic-Foam-Edge-Silvery/32710329947.html) ~ $ 1.50
* Power Bank
* 2x 1K Ohm Resistors
* (Jumper) Cables
* Breadboard 
* Buttons

In total these components should be less than $10. In bulk they might even be cheaper. On top comes the cost of the case.

## Wiring

The following explains how the different components are connected. Different microcontrollers can be used as an replacement for the Arduino Nano, e.g., NodeMCU. However, the Arduino Nano is cheap and provides both 5V and 3.3V, which is ideal for these components.

### RC522 to Arduino Nano
```
RST     = D9 (can be configured in the sketch)
SDA(SS) = D10 (can be configured in the sketch)
MOSI    = D12
MISO    = D11
SCK     = D13
GND     = GND
3.3V    = 3.3V
```

### RC522 to NodeMCU (alternative to Arduino Nano)
```
RST     = D3 (can be configured in the sketch)
SDA(SS) = D5 (can be configured in the sketch)
MOSI    = D7 
MISO    = D6
SCK     = D5
GND     = GND
3.3V    = NodeMCU does not provide 3.3V - use other power supply
```

### DF Player Mini to Arduino Nano
```
5V      = 5V
GND     = GND
TX      = D8 (or whatever is defined as SOFT_RX in the sketch)
RX      = D7 (or whatever is defined as SOFT_TX in the sketch)
```

*Note:* TX must be connected to RX and vice versa.

### PAM8403 to DF Player Mini
```
R       = DAC_R
L       = DAC_L
GND     = GND
5V      = Some 5V power supply
``` 


## Commercial Off-the-Shelf Solutions

There are some commercial off-the-shelf solutions doing the same thing. However, those are far more expensive and do not always allow to play arbitrary MP3 files.

* [Tony Box](https://tonies.de/toniebox/)

# Useful Links
* https://github.com/PowerBroker2/DFPlayerMini_Fast
* https://github.com/hnauen/Fritzing
* https://github.com/miguelbalboa/rfid/tree/master/doc/fritzing