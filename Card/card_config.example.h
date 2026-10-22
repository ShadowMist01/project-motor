// Example local configuration for Card.ino.
//
// Copy this file to "card_config.h" (same folder) and replace the values with
// the UIDs of the cards you want to accept. "card_config.h" is ignored by Git
// so real card identifiers are not published.
//
// Format: uppercase hex bytes separated by single spaces, exactly as the
// sketch prints them after "UID tag :" on the serial monitor
// (4-byte UID: "AA BB CC DD", 7-byte UID: "AA BB CC DD EE FF 00").
//
// NOTE: matching a card UID is NOT secure authentication. UIDs can be read
// and cloned. Use this only for demonstration purposes.

#define AUTHORIZED_UID_1 "AA BB CC DD"
#define AUTHORIZED_UID_2 "04 AA BB CC DD EE FF"
