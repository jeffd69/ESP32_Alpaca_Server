/**************************************************************************************************
  Filename:       AlpacaSafetyMonitor.cpp
  Revised:        $Date: 2024-12-04$
  Revision:       $Revision: 01 $
  Description:    Common ASCOM Alpaca SafetyMonitor Interface V1
**************************************************************************************************/
#include "AlpacaSafetyMonitor.h"

AlpacaSafetyMonitor::AlpacaSafetyMonitor()
{
    strlcpy(_device_type, ALPACA_SAFETYMONITOR_DEVICE_TYPE, sizeof(_device_type));
    strlcpy(_device_description, ALPACA_SAFETYMONITOR_DESCRIPTION, sizeof(_device_description));
    strlcpy(_driver_info, ALPACA_SAFETYMONITOR_DRIVER_INFO, sizeof(_driver_info));
    strlcpy(_device_and_driver_version, esp32_alpaca_device_library_version, sizeof(_device_and_driver_version));
    _device_interface_version = ALPACA_SAFETYMONITOR_INTERFACE_VERSION;

}

void AlpacaSafetyMonitor::Begin()
{
    snprintf(_device_and_driver_version, sizeof(_device_and_driver_version), "%s/%s", _getFirmwareVersion(), esp32_alpaca_device_library_version);
    AlpacaDevice::Begin();
}

void AlpacaSafetyMonitor::RegisterCallbacks()
{
    AlpacaDevice::RegisterCallbacks();

    this->createCallBack(LHF(_alpacaGetIsSafe), HTTP_GET, "issafe");

};


void AlpacaSafetyMonitor::_alpacaGetIsSafe(AsyncWebServerRequest *request)
{
    //DBG_SAFETYMONITOR_GET_IS_SAFE
    _service_counter++;
	_alpaca_server->RspStatusClear(_rsp_status);
	
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
	if (client_idx > 0)
		_is_safe = _getIsSafe();
	
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, _is_safe);
    //DBG_END
}


