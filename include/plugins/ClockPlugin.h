#pragma once

#include "PluginManager.h"

class ClockPlugin : public Plugin
{
private:
  struct tm timeinfo;

public:
  void setup() override;
  void loop() override;
  const char *getName() const override;
};