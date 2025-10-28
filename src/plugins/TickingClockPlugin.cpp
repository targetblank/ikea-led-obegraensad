#include "plugins/TickingClockPlugin.h"

void TickingClockPlugin::setup()
{
  // loading screen
  Screen.setPixel(4, 7, 1);
  Screen.setPixel(5, 7, 1);
  Screen.setPixel(7, 7, 1);
  Screen.setPixel(8, 7, 1);
  Screen.setPixel(10, 7, 1);
  Screen.setPixel(11, 7, 1);
}

void TickingClockPlugin::loop()
{
  if (getLocalTime(&timeinfo))
  {
    // Always redraw - swapBuffers() will skip copy if unchanged (memcmp optimization)
    if ((timeinfo.tm_hour * 60 + timeinfo.tm_min) < 6 * 60 + 30 ||
        (timeinfo.tm_hour * 60 + timeinfo.tm_min) > 22 * 60 + 30) // only between 6:30 and 22:30
    {
      Screen.clear();
      return;
    }

    std::vector<int> hh = {(timeinfo.tm_hour - timeinfo.tm_hour % 10) / 10, timeinfo.tm_hour % 10};
    std::vector<int> mm = {(timeinfo.tm_min - timeinfo.tm_min % 10) / 10, timeinfo.tm_min % 10};

    Screen.clear();

    // Draw hour digits (rows 0-7)
    Screen.drawCharacter(2, 0, Screen.readBytes(fonts[1].data[hh[0]]), 8, Screen.getCurrentBrightness());
    Screen.drawCharacter(9, 0, Screen.readBytes(fonts[1].data[hh[1]]), 8, Screen.getCurrentBrightness());

    // Draw minute digits (rows 9-16)
    Screen.drawCharacter(2, 9, Screen.readBytes(fonts[1].data[mm[0]]), 8, Screen.getCurrentBrightness());
    Screen.drawCharacter(9, 9, Screen.readBytes(fonts[1].data[mm[1]]), 8, Screen.getCurrentBrightness());

    // Draw second indicator (rows 7-8)
    if ((timeinfo.tm_sec * 32 / 60) % 2 == 0)
      Screen.setPixel(timeinfo.tm_sec * 16 / 60, 7, 1, Screen.getCurrentBrightness());
    else
      Screen.setPixel(timeinfo.tm_sec * 16 / 60, 8, 1, Screen.getCurrentBrightness());
  }
}

const char *TickingClockPlugin::getName() const
{
  return "Ticking Clock";
}
