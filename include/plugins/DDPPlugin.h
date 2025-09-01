#pragma once

#include "PluginManager.h"
#if __has_include("AsyncUDP.h")
#include "AsyncUDP.h"
#define ASYNC_UDP_ENABLED
#endif

class DDPPlugin : public Plugin
{
private:
#ifdef ASYNC_UDP_ENABLED
  AsyncUDP *udp;
  volatile bool isActive;  // Flag to prevent callback execution after teardown
#endif

public:
#ifdef ASYNC_UDP_ENABLED
  DDPPlugin() : udp(nullptr), isActive(false) {}
#endif
  void setup() override;
  void teardown() override;
  void loop() override;
  const char *getName() const override;
};
