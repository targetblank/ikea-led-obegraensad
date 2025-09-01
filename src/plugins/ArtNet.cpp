#include "plugins/ArtNet.h"

void ArtNetPlugin::setup()
{
    artnet.begin();
    artnet.setArtDmxCallback(onDmxFrame);
    Serial.print("ArtNet server listening at IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(" port: ");
    Serial.println(ART_NET_PORT);
    artnet.setUniverse(1);
    Serial.print("Universe: ");
    Serial.println(artnet.getOutgoing());
}

void ArtNetPlugin::teardown()
{
    artnet.stop();  // Properly close the ArtNet UDP connection
}

void ArtNetPlugin::loop()
{
    artnet.read();
}

const char *ArtNetPlugin::getName() const
{
    return "ArtNet";
}

void ArtNetPlugin::onDmxFrame(uint16_t universe, uint16_t length, uint16_t outgoing, uint8_t *data)
{
    Serial.print("Universe: ");
    Serial.println(universe);
    if (universe == 0 || universe == outgoing)
    {
        for (int i = 0; i < ROWS * COLS; i++)
        {
            Screen.setPixelAtIndex(i, data[i] > 4, data[i]);
        }
    }
}

void ArtNetPlugin::websocketHook(DynamicJsonDocument &request)
{
    const char *event = request["event"];

    if (currentStatus == NONE)
    {
        if (!strcmp(event, "artnet"))
        {
            uint16_t universe = request["universe"].as<uint16_t>();
            Serial.print("Changing ArtNet Universe to ");
            Serial.println(universe);
            artnet.setUniverse(universe);
            Serial.print("Current Universe: ");
            Serial.println(artnet.getOutgoing());
        }
    }
}
