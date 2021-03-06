#define TSMP_IMPL
#include "TSMaster.h"
#include "MPLibrary.h"
#include "Database.h"
#include "Test.h"

// Global definitions

s32 vWaitDone;


// Main step function being executed every 5 ms
void step(void) { // interval = 5 ms

TCAN c;
c.init_w_std_id(pGlobalParameters->std_data_id, 8);
if (!app.check(com.transmit_can_async(&c))) return;
app.wait(1000, "wait for the transmitting frame on bus");

if (!vWaitDone){
  test.set_verdict_nok("The transmitting message is not observed on bus");
  test.write_result_string("R_Std_Data", "NOK", lvlError);
} else {
  test.write_result_string("R_Std_Data", "OK", lvlOK);
}

app.terminate_application();

}

// On CAN message reception handler "OnCANRx" for identifier = ANY
void on_can_rx_OnCANRx(const PCAN ACAN) { // for identifier = ANY

test_log("CAN rx frame monitored: 0x%03x", ACAN->FIdentifier);

}

// On CAN message transmission handler "OnCANTx" for identifier = ANY
void on_can_tx_OnCANTx(const PCAN ACAN) { // for identifier = ANY

if (pGlobalParameters->std_data_id == ACAN->FIdentifier){
  vWaitDone = 1;
  test_log_ok("CAN tx frame is observed: 0x%03x", ACAN->FIdentifier);
} else {
  test_log("CAN tx frame monitored: 0x%03x", ACAN->FIdentifier);
}

}

// On start handler "StartTest"
void on_start_StartTest(void) { // on start event

app.set_check_failed_terminate(true);

if (!app.check(app.connect())) return;

}

/*TSMaster APIs*/
/*
app.log("hello log", 5);  
app.wait() //wait in milliseconds
app.pause() //pause the current test by poping up a dialog for user to control, this is usually helpful in script debugging
app.get_timestamp()  //get the PC timestamp of the current measurement in us


com.get_can_signal_value()
com.set_can_signal_value()
com.wait_can_message()
com.add_cyclic_message_can()
com.del_cyclic_message_can()
com.can_rbs_start()
com.can_rbs_stop()

com.transmit_can_async(&BCM_NM_0x431_1.FCAN);

test.set_verdict_ok()
test.set_verdict_nok()
test.set_verdict_cok()
test.write_result_string()
test.write_result_value()
app.terminate_application()
*/

/*VC vxlapi.lib convert to BCC vxlapi_bcc.lib*/
/*
TSMaster uses bcc(Borland C++ Compiler) to build source codes.
vxlapi.lib provided by Vector is generated by VC++.
It can not be recognized by bcc.
Using coff2omf.exe provided by coff2omf to covert VC lib to bcc lib:
1.cd path(the root folder of coff2omf.exe) 
2.coff2omf.exe -lib:ms c:/temp/bin/vxlapi.lib bcb c:/temp/bin/vxlapi_bcc.lib
*/
C:\Users\jchen57>cd C:\Program Files (x86)\TOSUN\TSMaster\bin\Data\compilers\bcc\Bin
C:\Program Files (x86)\TOSUN\TSMaster\bin\Data\compilers\bcc\Bin>coff2omf.exe -lib:ms c:/temp/bin/vxlapi.lib bcb c:/temp/bin/vxlapi_bcc.lib
COFF to OMF Converter Version 1.0.0.74 Copyright (c) 1999, 2000 Inprise Corporation




/*vxlapi contains window API,, windows.h should be included*/
#include <windows.h>  
#include "C:\temp\bin\vxlapi.h"
/*Import vxlapi_bcc.lib;*/
#pragma comment(lib, "C:\temp\bin\vxlapi_bcc.lib")
