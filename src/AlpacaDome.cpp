/**************************************************************************************************
  Filename:       AlpacaDome.cpp
  Revised:        $Date: 2024-07-24$
  Revision:       $Revision: 01 $
  Description:    Common ASCOM Alpaca Dome V3

  Copyright 2024 peter_n@gmx.de. All rights reserved.
**************************************************************************************************/
#include "AlpacaDome.h"

const char *const AlpacaDome::kAlpacaShutterStatusStr[5] = {"Open", "Opening", "Closed", "Closing", "Error"};

AlpacaDome::AlpacaDome()
{
    strlcpy(_device_type, ALPACA_DOME_DEVICE_TYPE, sizeof(_device_type));
    strlcpy(_device_description, ALPACA_DOME_DESCRIPTION, sizeof(_device_description));
    strlcpy(_driver_info, ALPACA_DOME_DRIVER_INFO, sizeof(_driver_info));
    strlcpy(_device_and_driver_version, esp32_alpaca_device_library_version, sizeof(_device_and_driver_version));
    _device_interface_version = ALPACA_DOME_INTERFACE_VERSION;
}

void AlpacaDome::Begin()
{
    snprintf(_device_and_driver_version, sizeof(_device_and_driver_version), "%s/%s", _getFirmwareVersion(), esp32_alpaca_device_library_version);
    AlpacaDevice::Begin();
}

void AlpacaDome::RegisterCallbacks()
{
    AlpacaDevice::RegisterCallbacks();

#ifdef ALPACA_DOME_PUT_ACTION_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutAction), HTTP_PUT, "action");
#endif
#ifdef ALPACA_DOME_PUT_COMMAND_BLIND_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandBlind), HTTP_PUT, "commandblind");
#endif
#ifdef ALPACA_DOME_PUT_COMMAND_BOOL_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandBool), HTTP_PUT, "commandbool");
#endif
#ifdef ALPACA_DOME_PUT_COMMAND_STRING_IMPLEMENTED
    this->createCallBack(LHF(AlpacaPutCommandString), HTTP_PUT, "commandstring");
#endif

	this->createCallBack(LHF(_alpacaPutAbortSlew), HTTP_PUT, "abortslew");
	this->createCallBack(LHF(_alpacaPutCloseShutter), HTTP_PUT, "closeshutter");
	this->createCallBack(LHF(_alpacaPutFindHome), HTTP_PUT, "findhome");
	this->createCallBack(LHF(_alpacaPutOpenShutter), HTTP_PUT, "openshutter");
	this->createCallBack(LHF(_alpacaPutPark), HTTP_PUT, "park");
	this->createCallBack(LHF(_alpacaPutSetPark), HTTP_PUT, "setpark");
	this->createCallBack(LHF(_alpacaPutSlewToAltitude), HTTP_PUT, "slewtoaltitude");
	this->createCallBack(LHF(_alpacaPutSlewToAzimuth), HTTP_PUT, "slewtoazimuth");
	this->createCallBack(LHF(_alpacaPutSyncToAzimuth), HTTP_PUT, "synctoazimuth");
	this->createCallBack(LHF(_alpacaGetAltitude), HTTP_GET, "altitude");
	this->createCallBack(LHF(_alpacaGetAtHome ), HTTP_GET, "athome");
	this->createCallBack(LHF(_alpacaGetAtPark ), HTTP_GET, "atpark");
	this->createCallBack(LHF(_alpacaGetAzimuth ), HTTP_GET, "azimuth");
	this->createCallBack(LHF(_alpacaGetCanFindHome ), HTTP_GET, "canfindhome");
	this->createCallBack(LHF(_alpacaGetCanPark ), HTTP_GET, "canpark");
	this->createCallBack(LHF(_alpacaGetCanSetAltitude ), HTTP_GET, "cansetaltitude");
	this->createCallBack(LHF(_alpacaGetCanSetAzimuth ), HTTP_GET, "cansetazimuth");
	this->createCallBack(LHF(_alpacaGetCanSetPark ), HTTP_GET, "cansetpark");
	this->createCallBack(LHF(_alpacaGetCanSetShutter ), HTTP_GET, "cansetshutter");
	this->createCallBack(LHF(_alpacaGetCanSlave ), HTTP_GET, "canslave");
	this->createCallBack(LHF(_alpacaGetCanSyncAzimuth ), HTTP_GET, "cansyncazimuth");
	this->createCallBack(LHF(_alpacaGetShutterStatus ), HTTP_GET, "shutterstatus");
	this->createCallBack(LHF(_alpacaGetSlaved ), HTTP_GET, "slaved");
	this->createCallBack(LHF(_alpacaPutSlaved ), HTTP_PUT, "slaved");
	this->createCallBack(LHF(_alpacaGetSlewing ), HTTP_GET, "slewing");
}

void AlpacaDome::_alpacaPutAbortSlew(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_ABORT;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
        goto mycatch;

    _slewing = false;
    _shutter_state = AlpacaShutterStatus_t::kError;
    if( false == _putAbort()) {
        MYTHROW_RspStatusDriverError( request, _rsp_status, "Abort" );
    }


mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutCloseShutter(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_CLOSE;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
        goto mycatch;
        
    _slewing = true;
	_shutter_state = AlpacaShutterStatus_t::kClosing;
    if( false == _putClose()) {
        _slewing = false;
	    _shutter_state = AlpacaShutterStatus_t::kError;
        MYTHROW_RspStatusDriverError( request, _rsp_status, "CloseShutter" );
    }

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutFindHome(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_FIND_HOME;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "FindHome");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutOpenShutter(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_OPEN;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
        goto mycatch;
        
    _slewing = true;
	_shutter_state = AlpacaShutterStatus_t::kOpening;
    if( false == _putOpen()) {
        _slewing = false;
	    _shutter_state = AlpacaShutterStatus_t::kError;
        MYTHROW_RspStatusDriverError( request, _rsp_status, "OpenShutter" );
    }

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutPark(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_PARK;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "Park");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutSetPark(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_SET_PARK;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "SetPark");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutSlewToAltitude(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_SLEW_TO_ALT;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "SlewToAltitude");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutSlewToAzimuth(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_SLEW_TO_AZ;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "SlewToAzimuth");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaPutSyncToAzimuth(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_SYNC_TO_AZ;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "SyncToAzimuth");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetAltitude(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_ALT;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "GetAltitude");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetAtHome(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_AT_HOME;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "AtHome");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetAtPark(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_AT_PARK;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "AtPark");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetAzimuth(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_AZ;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "GetAzimuth");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetCanFindHome(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_CAN_FIND_HOME;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanPark(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_CAN_PARK;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSetAltitude(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_CAN_SET_ALT;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSetAzimuth(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_CAN_SET_AZ;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSetPark(AsyncWebServerRequest *request)
{
    //DBG_DOME_CAN_SET_PARK;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSetShutter(AsyncWebServerRequest *request)
{
    //DBG_DOME_CAN_SET_SHUTTER;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, true);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSlave(AsyncWebServerRequest *request)
{
    //DBG_DOME_CAN_SLAVE;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetCanSyncAzimuth(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_CAN_SYNC_AZ;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaGetShutterStatus(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_SHUTTER
    _service_counter++;
    AlpacaShutterStatus_t _shut = AlpacaShutterStatus_t::kError;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        _shut = _getShutter();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (int32_t)_shut);
    //DBG_END
}

void AlpacaDome::_alpacaGetSlaved(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_SLAVED;
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);
    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);

    if (client_idx > 0)
	{
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status, false);
	} else {
		MYTHROW_RspStatusClientIDInvalid(request, _rsp_status, client_idx);
        mycatch:
		_alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
	}
    //DBG_END
}

void AlpacaDome::_alpacaPutSlaved(AsyncWebServerRequest *request)
{
    //DBG_DOME_PUT_SLAVED;
    _service_counter++;
    uint32_t client_idx = 0;    
    _alpaca_server->RspStatusClear(_rsp_status);
    client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict);
    MYTHROW_RspStatusCommandNotImplemented(request, _rsp_status, "Slaved");

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    //DBG_END
}

void AlpacaDome::_alpacaGetSlewing(AsyncWebServerRequest *request)
{
    //DBG_DOME_GET_SLEWING
    _service_counter++;
    _alpaca_server->RspStatusClear(_rsp_status);

    uint32_t client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kIgnoreCase);
    if (client_idx > 0)
    {
        _slewing = _getSlewing();
    }
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)_slewing);
    //DBG_END
}


#ifdef ALPACA_DOME_PUT_ACTION_IMPLEMENTED
void AlpacaDome::AlpacaPutAction(AsyncWebServerRequest *request)
{
    DBG_DEVICE_PUT_ACTION_REQ;
    //_service_counter++;
    uint32_t client_idx = 0;
    _alpaca_server->RspStatusClear(_rsp_status);
    char action[64] = {0};
    char parameters[128] = {0};
    char str_response[1024] = {0};

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0 && _clients[client_idx].client_id != ALPACA_CONNECTION_LESS_CLIENT_ID)
        goto mycatch;

    if (_alpaca_server->GetParam(request, "Action", action, sizeof(action), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Action");

    if (_alpaca_server->GetParam(request, "Parameters", parameters, sizeof(parameters), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Action");

    if (_putAction(action, parameters, str_response, sizeof(str_response)) == false)
        MYTHROW_RspStatusCommandStringInvalid(request, _rsp_status, parameters);

    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, str_response, JsonValue_t::kAsPlainStringValue);

    DBG_END;
    return;

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
};
#endif

#ifdef ALPACA_DOME_PUT_COMMAND_BOOL_IMPLEMENTED
void AlpacaDome::AlpacaPutCommandBool(AsyncWebServerRequest *request)
{
    DBG_DEVICE_PUT_ACTION_REQ;
    _service_counter++;
    uint32_t client_idx = 0;
    _alpaca_server->RspStatusClear(_rsp_status);
    char command[64] = {0};
    char raw[16] = "true";
    bool bool_response = false;

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
        goto mycatch;

    if (_alpaca_server->GetParam(request, "Command", command, sizeof(command), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Command");

    if (_alpaca_server->GetParam(request, "Raw", raw, sizeof(raw), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Raw");

    if (_putCommandBool(command, raw, bool_response) == false)
        MYTHROW_RspStatusCommandStringInvalid(request, _rsp_status, command);

    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, (bool)bool_response);

    DBG_END;
    return;

mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);

    DBG_END
};
#endif

#ifdef ALPACA_DOME_PUT_COMMAND_STRING_IMPLEMENTED
void AlpacaDome::AlpacaPutCommandString(AsyncWebServerRequest *request)
{
    DBG_DEVICE_PUT_ACTION_REQ;
    _service_counter++;
    uint32_t client_idx = 0;
    _alpaca_server->RspStatusClear(_rsp_status);
    char command_str[256] = {0};
    char raw[16] = "true";
    char str_response[64] = {0};

    if ((client_idx = checkClientDataAndConnection(request, client_idx, Spelling_t::kStrict)) == 0)
        throw(&_rsp_status);

    if (_alpaca_server->GetParam(request, "Command", command_str, sizeof(command_str), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Command");

    if (_alpaca_server->GetParam(request, "Raw", raw, sizeof(raw), Spelling_t::kStrict) == false)
        MYTHROW_RspStatusParameterNotFound(request, _rsp_status, "Raw");

    if (_putCommandString(command_str, raw, str_response, sizeof(str_response)) == false)
       MYTHROW_RspStatusCommandStringInvalid(request, _rsp_status, command_str);

    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status, str_response);

    DBG_END;
    return;
    
mycatch:
    _alpaca_server->Respond(request, _clients[client_idx], _rsp_status);
    DBG_END
};
#endif
