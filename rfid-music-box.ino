/***************************************************

Consult README for information on necessary 
components and how they are connected.

****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SPI.h>
#include "MFRC522.h"

// Software Serial Pins
#define SOFT_TX 7 // Needed for RX of DF Player Mini
#define SOFT_RX 8 // Needed for TX of DF Player Mini

#define RST_PIN 9 // Needed for RST of RC522
#define SS_PIN 10 // Needed for SDA(SS) of RC522

#define CARD_ID_LENGTH 4

// IDs of RFID
const byte CARDS[][CARD_ID_LENGTH] = {
    {0x40, 0x36, 0x75, 0x65},
    {0xD5, 0xC0, 0x09, 0x02}};

const int CARD_COUNT = sizeof(CARDS) / sizeof(CARDS[0]);

byte currentCard[] = {0, 0, 0, 0};

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

SoftwareSerial mySoftwareSerial(SOFT_RX, SOFT_TX); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
    mySoftwareSerial.begin(9600);
    Serial.begin(9600);

    while (!myDFPlayer.begin(mySoftwareSerial))
    {
        Serial.println("Unable to begin:");
        Serial.println("Recheck TX/RX");
        Serial.println("AND check if SD card is inserted!");
        Serial.println("Waiting 5 Seconds");
        delay(5000);
    }

    Serial.println("DFPlayer Mini online.");

    myDFPlayer.volume(30); //Set volume value. From 0 to 30

    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
}

void loop()
{
    if (myDFPlayer.available())
    {
        printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }

    if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial() && isNewCard(mfrc522.uid.uidByte))
    {
        Serial.println("New card found: ");
        printCardId(currentCard);
        Serial.println();

        int fileNumber = getCardIndex() + 1;
        myDFPlayer.stop();
        myDFPlayer.play(fileNumber);
    }

    delay(50);
}

int getCardIndex()
{
    for (int i = 0; i < CARD_COUNT; i++)
    {
        if (equalCards(currentCard, CARDS[i]))
            return i;
    }
}

bool isNewCard(byte *card)
{
    if (equalCards(currentCard, card))
        return false;
    for (int i = 0; i < CARD_ID_LENGTH; i++)
    {
        currentCard[i] = card[i];
    }
    return true;
}

// Checks if two RFID cards are equal
bool equalCards(byte *card1, byte *card2)
{
    for (int i = 0; i < CARD_ID_LENGTH; i++)
    {
        if (card1[i] != card2[i])
        {
            return false;
        }
    }
    return true;
}

// Helper routine to print card ids to serial
void printCardId(byte *card)
{
    for (byte i = 0; i < CARD_ID_LENGTH; i++)
    {
        Serial.print(card[i] < 0x10 ? " 0" : " ");
        Serial.print(card[i], HEX);
    }
}

void printDetail(uint8_t type, int value)
{
    switch (type)
    {
    case TimeOut:
        Serial.println("Time Out!");
        break;
    case WrongStack:
        Serial.println("Stack Wrong!");
        break;
    case DFPlayerCardInserted:
        Serial.println("Card Inserted!");
        break;
    case DFPlayerCardRemoved:
        Serial.println("Card Removed!");
        break;
    case DFPlayerCardOnline:
        Serial.println("Card Online!");
        break;
    case DFPlayerPlayFinished:
        Serial.print("Number:");
        Serial.print(value);
        Serial.println(" Play Finished!");
        break;
    case DFPlayerError:
        Serial.print("DFPlayerError:");
        switch (value)
        {
        case Busy:
            Serial.println("Card not found");
            break;
        case Sleeping:
            Serial.println("Sleeping");
            break;
        case SerialWrongStack:
            Serial.println("Get Wrong Stack");
            break;
        case CheckSumNotMatch:
            Serial.println("Check Sum Not Match");
            break;
        case FileIndexOut:
            Serial.println("File Index Out of Bound");
            break;
        case FileMismatch:
            Serial.println("Cannot Find File");
            break;
        case Advertise:
            Serial.println("In Advertise");
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
