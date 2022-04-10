# ESP8266-nonos-start

Starting point for ESP8266 projects that use the Non-RTOS SDK (e.g. nonos-sdk) This has been copied from `~/.platformio/platforms/espressif8266/examples/esp8266-nonos-sdk-blink` and tweaked a bit before first commit.

## Plan

Add support for WiFi, NTP, MQTT and perhaps analog inputs.

## Status 

* Blink LED, on 0.5ms and off for 499.5ms.
* Establish WiFi connection

## Abandoned

This post https://community.platformio.org/t/vs-code-esp8266-non-rtos-nonos-sdk-project-creation/27091 indicates that PlatformIO support for this SDK is badly behind and should not be used (and the RTOS variant as well.) The current nonos-sdk is found at <https://github.com/espressif/ESP8266_NONOS_SDK>. From the README

> It is suggested that the ESP8266_RTOS_SDK, instead of ESP8266 NonOS SDK, be used for your projects.

It seems that the NonOS SDK is deprecated and the RTOS SDK should be used instead. I will be starting a new project using the RTOS SDK at <https://github.com/espressif/ESP8266_RTOS_SDK> and proceeding w/out PlatformIO. That project will be found at <https://github.com/HankB/ESP8266_RTOS_Start>
