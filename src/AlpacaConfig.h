/**************************************************************************************************
  Filename:       AlpacaConfig.h
  Revised:        $Date: 2024-01-25$
  Revision:       $Revision: 02 $

  Description:    Config for Alpac Lib

  Copyright 2024 peter_n@gmx.de. All rights reserved.
**************************************************************************************************/
#pragma once
#include <Arduino.h>

// Library version see also library.json/version
const char esp32_alpaca_device_library_version[] = "1.0.0";

// ALPACA Server
#define ALPACA_MAX_CLIENTS 8
#define ALPACA_MAX_DEVICES 4
#define ALPACA_UDP_PORT 32227
#define ALPACA_TCP_PORT 80
#define ALPACA_CLIENT_CONNECTION_TIMEOUT_SEC 120
#define ALPACA_CONNECTION_LESS_CLIENT_ID 42424242   // used for services without connection 

//#define ALPACA_ENABLE_OTA_UPDATE

// ALPACA Management Interface - Description Request
#define ALPACA_INTERFACE_VERSION "[1]"              // /management/apiversions Value: Supported Alpaca API versions
#define ALPACA_MNG_SERVER_NAME "ALPACA-TS-ESP32"    // only for init; managed by config
#define ALPACA_MNG_MANUFACTURE "TS"
#define ALPACA_MNG_MANUFACTURE_VERSION esp32_alpaca_device_library_version
#define ALPACA_MNG_LOCATION "IT"

// AscomDriver Common Properties:
// - Description: A description of the device, such as manufacturer and model number. Any ASCII characters may be used.
// - DriverInfo: Descriptive and version information about this ASCOM driver
// - DriverVersion: A string containing only the major and minor version of the driver
// - InterfaceVersion: The interface version number that this device supports
// - Name: The short name of the driver, for display purposes
// DeviceType - as defined ASCOM

// =======================================================================================================
// CoverCalibrator - Common Properties
#define ALPACA_COVER_CALIBRATOR_DESCRIPTION "Alpaca CoverCalibrator"        		// init value; managed by config
#define ALPACA_COVER_CALIBRATOR_DRIVER_INFO "ESP32 CoverCalibrator driver" 			// init value; managed by config
#define ALPACA_COVER_CALIBRATOR_INTERFACE_VERSION 1                                 // don't change
#define ALPACA_COVER_CALIBRATOR_NAME "not used"                                     // init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_COVER_CALIBRATOR_DEVICE_TYPE "covercalibrator"                       // don't change

// // CoverCalibrator - Optional Methods
#define ALPACA_COVER_CALIBRATOR_PUT_ACTION_IMPLEMENTED
#define ALPACA_COVER_CALIBRATOR_PUT_COMMAND_BLIND_IMPLEMENTED
#define ALPACA_COVER_CALIBRATOR_PUT_COMMAND_BOOL_IMPLEMENTED
#define ALPACA_COVER_CALIBRATOR_PUT_COMMAND_STRING_IMPLEMENTED

// CoverCalibrator - Specific Properties
#define ALPACA_COVER_CALIBRATOR_MAX_BRIGHTNESS 1023 // init; managed by setup

// =======================================================================================================
// Dome - Common Properties
#define ALPACA_DOME_DESCRIPTION "Alpaca Dome"        					// init value; managed by config
#define ALPACA_DOME_DRIVER_INFO "ESP32 Dome driver" 					// init value; managed by config
#define ALPACA_DOME_INTERFACE_VERSION 1                       // don't change
#define ALPACA_DOME_NAME "not used"                           // init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_DOME_DEVICE_TYPE "dome"                        // don't change

// // Focuser - Optional Methods
// #define ALPACA_DOME_PUT_ACTION_IMPLEMENTED
// #define ALPACA_DOME_PUT_COMMAND_BLIND_IMPLEMENTED
// #define ALPACA_DOME_PUT_COMMAND_BOOL_IMPLEMENTED
// #define ALPACA_DOME_PUT_COMMAND_STRING_IMPLEMENTED

// =======================================================================================================
// SAFETYMONITOR - Common Properties
#define ALPACA_SAFETYMONITOR_DESCRIPTION "Alpaca SafetyMonitor"        	// init value; managed by config
#define ALPACA_SAFETYMONITOR_DRIVER_INFO "ESP32 SafetyMonitor driver" 	// init value; managed by config
#define ALPACA_SAFETYMONITOR_INTERFACE_VERSION 1                        // don't change
#define ALPACA_SAFETYMONITOR_NAME "not used"                            // init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_SAFETYMONITOR_DEVICE_TYPE "safetymonitor"                // don't change

// // SAFETYMONITOR - Optional Methods
// #define ALPACA_SAFETYMONITOR_PUT_ACTION_IMPLEMENTED
// #define ALPACA_SAFETYMONITOR_PUT_COMMAND_BLIND_IMPLEMENTED
// #define ALPACA_SAFETYMONITOR_PUT_COMMAND_BOOL_IMPLEMENTED
// #define ALPACA_SAFETYMONITOR_PUT_COMMAND_STRING_IMPLEMENTED

// =======================================================================================================
// Switch - Comon Properties
#define ALPACA_SWITCH_DESCRIPTION "Alpaca Switch"        			      // init value; managed by config
#define ALPACA_SWITCH_DRIVER_INFO "ESP32 Switch driver" 			      // init value; managed by config
#define ALPACA_SWITCH_INTERFACE_VERSION 1                         	// don't change
#define ALPACA_SWITCH_NAME "not used"                             	// init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_SWITCH_DEVICE_TYPE "switch"                        	// don't change

// Switch - Specific Properties
// empty

// =======================================================================================================
// ObservingConditions - Comon Properties
#define ALPACA_OBSERVING_CONDITIONS_DESCRIPTION "Alpaca ObservingConditions"        // init value; managed by config
#define ALPACA_OBSERVING_CONDITIONS_DRIVER_INFO "ESP32 ObservingConditions driver" // init value; managed by config
#define ALPACA_OBSERVING_CONDITIONS_INTERFACE_VERSION 1                                      // don't change
#define ALPACA_OBSERVING_CONDITIONS_NAME "not used"                                          // init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_OBSERVING_CONDITIONS_DEVICE_TYPE "observingconditions"                        // don't change

// =======================================================================================================
// Focuser - Comon Properties
#define ALPACA_FOCUSER_DESCRIPTION "Alpaca Focuser"        // init value; managed by config
#define ALPACA_FOCUSER_DRIVER_INFO "ESP32 Focuser driver" // init value; managed by config
#define ALPACA_FOCUSER_INTERFACE_VERSION 3                          // don't change
#define ALPACA_FOCUSER_NAME "not used"                              // init with <deviceType>-<deviceNumber>; managed by config
#define ALPACA_FOCUSER_DEVICE_TYPE "focuser"                        // don't change

// // Focuser - Optional Methods
//#define ALPACA_FOCUSER_PUT_ACTION_IMPLEMENTED
//#define ALPACA_FOCUSER_PUT_COMMAND_BLIND_IMPLEMENTED
//#define ALPACA_FOCUSER_PUT_COMMAND_BOOL_IMPLEMENTED
//#define ALPACA_FOCUSER_PUT_COMMAND_STRING_IMPLEMENTED

// include user config
#include "UserConfig.h"

const uint32_t kAlpacaMaxClients = ALPACA_MAX_CLIENTS;
const uint32_t kAlpacaMaxDevices = ALPACA_MAX_DEVICES;
const uint32_t kAlpacaUdpPort = ALPACA_UDP_PORT;
const uint32_t kAlpacaTcpPort = ALPACA_TCP_PORT;
const uint32_t kAlpacaClientConnectionTimeoutMs = ALPACA_CLIENT_CONNECTION_TIMEOUT_SEC * 1000;


