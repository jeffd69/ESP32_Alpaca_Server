/**************************************************************************************************
  Filename:       AlpacaSafetyMonitor.h
  Revised:        $Date: 2024-12-04$
  Revision:       $Revision: 01 $
  Description:    Common ASCOM Alpaca SafetyMonitor Interface V1
**************************************************************************************************/
#pragma once
#include "AlpacaDevice.h"

class AlpacaSafetyMonitor : public AlpacaDevice
{
private:
  bool _is_safe = false;

  void _alpacaGetIsSafe(AsyncWebServerRequest *request);

  // virtual instance specific methods
  virtual const char* const _getFirmwareVersion() { return "-"; };  
  virtual const bool _getIsSafe() = 0;

protected:
  // Interface for specific implementation
  AlpacaSafetyMonitor();
  void Begin();
  void RegisterCallbacks();

public:
};
