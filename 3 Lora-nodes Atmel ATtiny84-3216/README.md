# ATTiny Sensor Node  (ATTNode)

## Overview

A Minimalistic Sensor Node for use on TheThingsNetwork with the following Features:

  * Small Size, only 47x36mm (v1) / 34x26mm (v2)
  * Based on widely available Atmel ATTiny84 MCU and RFM95W LoRa-module
  * 6 free GPIO-Pins from the ATTiny + Power to connect sensors on a 2.54mm pitch header
  * Optional on-board LED for status signaling
  * Powered by a single CR2032 lithium battery
  * Long battery runtime using the ATTinys deep sleep mode
  * Integrated 6-Pin programming header
  * Small component count
  * Possibility for edge-mount SMA connector or u.fl SMD connector (v2)

**You can get all up to date information as well as assembly and pogramming hints at https://www.attno.de/**

## Subdirectories In this Repository

* **Case:** A 3D-Printable Case, OpenSCAD and STL Files
* **Firmware:** Example Firmware for a BME280/SHT21 Climate Sensor, PlatformIO project
* **PCB_SMD:** PCB for SMD components, KiCAD project

## Thanks & Acknowledgements:

* The [TinyTX Project](https://nathan.chantrell.net/tinytx-wireless-sensor/), which served as an inspiration
* Everyone making [The Things Network](https://www.thethingsnetwork.org/) happen
* Some ideas where taken from the c't magazines ["Brief-Fernmelder"](http://ct.de/wyjb) Project

