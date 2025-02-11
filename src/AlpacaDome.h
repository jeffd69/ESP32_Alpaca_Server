/**************************************************************************************************
  Filename:       AlpacaDome.h
  Revised:        $Date: 2024-12-02$
  Revision:       $Revision: 01 $
  Description:    Common ASCOM Alpaca Dome V3
**************************************************************************************************/
#pragma once
#include "AlpacaDevice.h"

// ASCOM  / ALPACA ShutterStatus Enumeration
enum struct AlpacaShutterStatus_t
{
  kOpen = 0,
  kClosed,
  kOpening,
  kClosing,
  kError
};

class AlpacaDome : public AlpacaDevice
{
private:
	AlpacaShutterStatus_t _shutter_state = AlpacaShutterStatus_t::kError;
	static const char *const kAlpacaShutterStatusStr[5];
	bool _slewing = false;

    void _alpacaPutAbortSlew(AsyncWebServerRequest *request);
    void _alpacaPutCloseShutter(AsyncWebServerRequest *request);
    void _alpacaPutFindHome(AsyncWebServerRequest *request);
    void _alpacaPutOpenShutter(AsyncWebServerRequest *request);
    void _alpacaPutPark(AsyncWebServerRequest *request);
    void _alpacaPutSetPark(AsyncWebServerRequest *request);
    void _alpacaPutSlewToAltitude(AsyncWebServerRequest *request);
    void _alpacaPutSlewToAzimuth(AsyncWebServerRequest *request);
    void _alpacaPutSyncToAzimuth(AsyncWebServerRequest *request);
    void _alpacaGetAltitude(AsyncWebServerRequest *request);
    void _alpacaGetAtHome(AsyncWebServerRequest *request);
    void _alpacaGetAtPark(AsyncWebServerRequest *request);
	void _alpacaGetAzimuth(AsyncWebServerRequest *request);
	void _alpacaGetCanFindHome(AsyncWebServerRequest *request);
	void _alpacaGetCanPark(AsyncWebServerRequest *request);
	void _alpacaGetCanSetAltitude(AsyncWebServerRequest *request);
	void _alpacaGetCanSetAzimuth(AsyncWebServerRequest *request);
	void _alpacaGetCanSetPark(AsyncWebServerRequest *request);
	void _alpacaGetCanSetShutter(AsyncWebServerRequest *request);
	void _alpacaGetCanSlave(AsyncWebServerRequest *request);
	void _alpacaGetCanSyncAzimuth(AsyncWebServerRequest *request);
	void _alpacaGetShutterStatus(AsyncWebServerRequest *request);
	void _alpacaGetSlaved(AsyncWebServerRequest *request);
	void _alpacaPutSlaved(AsyncWebServerRequest *request);
	void _alpacaGetSlewing(AsyncWebServerRequest *request);

#ifdef ALPACA_DOME_PUT_ACTION_IMPLEMENTED
    void AlpacaPutAction(AsyncWebServerRequest *request);
    virtual const bool _putAction(const char *const action, const char *const parameters, char *string_response, size_t string_response_size)=0;
#endif
#ifdef ALPACA_DOME_PUT_COMMAND_BOOL_IMPLEMENTED
    void AlpacaPutCommandBool(AsyncWebServerRequest *request);
    virtual const bool _putCommandBool(const char *const command, const char *const raw, bool &bool_response)=0;
#endif
#ifdef ALPACA_DOME_PUT_COMMAND_STRING_IMPLEMENTED
    void AlpacaPutCommandString(AsyncWebServerRequest *request);
    virtual const bool _putCommandString(const char *const command_str, const char *const raw, char *string_response, size_t string_response_size)=0;
#endif

    virtual const char* const _getFirmwareVersion() { return "1"; };
	
	virtual const bool _putAbort() = 0;		// must be implemented in TSBoard
	virtual const bool _putClose() = 0;
	virtual const bool _putOpen() = 0;
	virtual const AlpacaShutterStatus_t _getShutter() = 0;
	virtual const bool _getSlewing() = 0;
    
protected:
    AlpacaDome();
    void Begin();
    void RegisterCallbacks();


public:
    //void _alpacaGetPage(AsyncWebServerRequest *request, const char* const page);

};