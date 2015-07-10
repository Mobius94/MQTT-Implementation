#ifndef MQTTPACKET
#define MQTTPAcket
#include<string.h>

typedef enum msgTypes
{
	MQTTCONNECT = 1, CONNACK, PUBLISH, PUBACK, PUBREC, PUBREL,
	PUBCOMP, SUBSCRIBE, SUBACK, UNSUBSCRIBE, UNSUBACK,
	PINGREQ, PINGRESP, DISCONNECT
};

/**
* Bitfields for the MQTT header byte.
*/
typedef union
{
	char byte;	                /**< the whole byte */
#if defined(REVERSED)
	struct
	{
		unsigned int type : 4;			/**< message type nibble */
		unsigned int dup : 1;				/**< DUP flag bit */
		unsigned int qos : 2;				/**< QoS value, 0, 1 or 2 */
		unsigned int retain : 1;		/**< retained flag bit */
	} bits;
#else
	struct
	{
		unsigned int retain : 1;		/**< retained flag bit */
		unsigned int qos : 2;				/**< QoS value, 0, 1 or 2 */
		unsigned int dup : 1;				/**< DUP flag bit */
		unsigned int type : 4;			/**< message type nibble */
	} bits;
#endif
} MQTTHeader;

class MQTTMessage
{
public:
	char message[14];
	MQTTMessage(msgTypes type);
	void MQTTConnect();
protected:
	MQTTHeader header;
	int remlength;
};

MQTTMessage::MQTTMessage(msgTypes type)
{
	header.bits.type = type;
	switch (type)
	{
	case MQTTCONNECT: MQTTConnect();
	}
}

void MQTTMessage::MQTTConnect()
{
	remlength = 0xc;
	header.bits.qos = 0;
	header.bits.dup = 0;
	header.bits.retain = 0;

	message[0] = header.byte;
	message[1] = remlength;
	message[2] = 0;
	message[3] = 0x04;
	message[4] = 'M';
	message[5] = 'Q';
	message[6] = 'T';
	message[7] = 'T';
	message[8] = 0x04; //Version
	message[9] = 0; //Flags
	message[10] = 0;
	message[11] = 2;
	message[12] = 'I';
	message[13] = 'D';
}

#endif
