#include "plugins/DDPPlugin.h"

void DDPPlugin::setup()
{
#ifdef ASYNC_UDP_ENABLED
    isActive = true;
    udp = new AsyncUDP();
    if (udp->listen(4048))
    {
        Serial.print("DDP server listening at port: 4048");

        udp->onPacket([this](AsyncUDPPacket packet)
                      {
            // Check if plugin is still active to avoid accessing freed memory
            if (!this->isActive) return;
            
            if (packet.length() >= 10) {  // Basic DDP header check
                const uint8_t* data = packet.data() + 10;  // Skip header
                const size_t dataLength = packet.length() - 10;
                int count = std::min((int)(dataLength / 3), ROWS * COLS);  // Each pixel is RGB

                if (count == 1) {  // Single pixel mode
                    uint8_t brightness = (data[0] + data[1] + data[2]) / 3;
                    for (int i = 0; i < ROWS * COLS; i++) {
                        Screen.setPixelAtIndex(i, brightness > 4, brightness);
                    }
                } else {  // Full pixel mapping
                    for (int i = 0; i < count; i++) {
                        uint8_t brightness = (data[i * 3] + data[i * 3 + 1] + data[i * 3 + 2]) / 3;
                        Screen.setPixelAtIndex(i, brightness > 4, brightness);
                    }
                }
            } });
    }
#endif
}

void DDPPlugin::teardown()
{
#ifdef ASYNC_UDP_ENABLED
    isActive = false;  // Prevent callback execution
    if (udp)
    {
        udp->close();  // Properly close the UDP connection first
        delete udp;
        udp = nullptr;
    }
#endif
}

void DDPPlugin::loop()
{
    delay(1);
}

const char *DDPPlugin::getName() const
{
    return "DDP";
}