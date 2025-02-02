/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* $Source: src/occ_405/errl/errl.h $                                     */
/*                                                                        */
/* OpenPOWER OnChipController Project                                     */
/*                                                                        */
/* Contributors Listed Below - COPYRIGHT 2011,2019                        */
/* [+] International Business Machines Corp.                              */
/*                                                                        */
/*                                                                        */
/* Licensed under the Apache License, Version 2.0 (the "License");        */
/* you may not use this file except in compliance with the License.       */
/* You may obtain a copy of the License at                                */
/*                                                                        */
/*     http://www.apache.org/licenses/LICENSE-2.0                         */
/*                                                                        */
/* Unless required by applicable law or agreed to in writing, software    */
/* distributed under the License is distributed on an "AS IS" BASIS,      */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or        */
/* implied. See the License for the specific language governing           */
/* permissions and limitations under the License.                         */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef _ERRL_H
#define _ERRL_H

#include <occ_common.h>
#include <trac_interface.h>
#include <pstate_pgpe_occ_api.h>

// Used as default for invalid slot number
static const uint8_t  ERRL_INVALID_SLOT = 0xFF;

// Used for shifting slot bits
static const uint32_t ERRL_SLOT_SHIFT = 0x80000000;

// Used for defaulting handle to invalid
static const uint32_t INVALID_ERR = 0xFFFFFFFF;

// Max size of non call home data logs (2128 bytes)
#define MAX_ERRL_ENTRY_SZ 0x850

// Max size of call home data log (3072 bytes)
#define MAX_ERRL_CALL_HOME_SZ 0xC00

// Max size of an OCC detected PGPE error log (3616 bytes)
#define MAX_ERRL_PGPE_ENTRY_SZ 0xE20

// Max number of callouts
#define ERRL_MAX_CALLOUTS 6

// Max number of error logs
#define ERRL_MAX_SLOTS 8

// Used to default a old/bad error handle
#define INVALID_ERR_HNDL (errlHndl_t)INVALID_ERR

// USED to determine the number of all trace buffer types. Now have (INF/IMP/ERR)
#define NUM_OF_TRACE_TYPE 3

// maximum size of PGPE debug data will be added for ERRL_USR_DTL_PGPE_PK_TRACE when PGPE error slot available
#define MAX_PGPE_DBUG_DATA 0x860
// maximum size of PGPE debug data will be added for ERRL_USR_DTL_PGPE_PK_TRACE when PGPE error slot not available
#define MAX_PGPE_DBUG_DATA_NO_SLOT 0x300

// These bits are used to acquire a slot number.  When used with the global
// slot bit mask, we are able to get 5 slots for predictive/unrecoverable errors,
// 1 slot for an OCC detected PGPE error, 1 slot for informational logs,
// and 1 slot for call home data log
/* Slot Masks */
typedef enum
{
    ERRL_SLOT_MASK_DEFAULT        = 0xFFFFFFFF,
    ERRL_SLOT_MASK_INFORMATIONAL  = 0xFDFFFFFF,
    ERRL_SLOT_MASK_OCC_ERROR      = 0x07FFFFFF,
    ERRL_SLOT_MASK_CALL_HOME_DATA = 0xFEFFFFFF,
    ERRL_SLOT_MASK_PGPE_ERROR     = 0xFBFFFFFF,
} ERRL_SLOT_MASK;

// These are the possible sources that an error log can be coming from
typedef enum
{
    ERRL_SOURCE_405     = 0x00,
    ERRL_SOURCE_PGPE    = 0x10,
    ERRL_SOURCE_XGPE    = 0x20,
    ERRL_SOURCE_INVALID = 0xFF,
} ERRL_SOURCE;

// These are the possible severities that an error log can have.
// Users must ONLY use these enum values for severity.
/* Error Severity */
typedef enum
{
    ERRL_SEV_INFORMATIONAL  = 0x00,  // Used by TMGT
    ERRL_SEV_PREDICTIVE     = 0x01,  // Used by TMGT
    ERRL_SEV_UNRECOVERABLE  = 0x02,  // Used by TMGT
    ERRL_SEV_CALLHOME_DATA  = 0x03,  // internal OCC use. Not used by TMGT
    ERRL_SEV_PGPE_ERROR     = 0x04,  // internal OCC use. Not used by TMGT
} ERRL_SEVERITY;

// These are the possible actions that an error log can have.
// Users must ONLY use these enum values for actions.
/* Error Actions */
typedef enum
{
    ERRL_ACTIONS_CONSOLIDATE_ERRORS       = 0x01, //ignored by tmgt at this time
    ERRL_ACTIONS_MANUFACTURING_ERROR      = 0x08, //tmgt will set severity to predictive while in mfg mode
    ERRL_ACTIONS_FORCE_SEND               = 0x10, //htmgt will force error to be sent to BMC (for info errors to be seen)
    ERRL_ACTIONS_WOF_RESET_REQUIRED       = 0x20, //Soft reset without incrementing permanent safe mode count
    ERRL_ACTIONS_SAFE_MODE_REQUIRED       = 0x40, //immediate permanent safe mode without any recovery (checkstop)
    ERRL_ACTIONS_RESET_REQUIRED           = 0x80, //permanent safe mode after 3 recovery attempts
} ERRL_ACTIONS_MASK;

// These are the possible callout priorities that a callout can have.
// Users must ONLY use these enum values for callout priority
/* Callout Priority */
typedef enum
{
    ERRL_CALLOUT_PRIORITY_INVALID   = 0x00,
    ERRL_CALLOUT_PRIORITY_LOW       = 0x01,
    ERRL_CALLOUT_PRIORITY_MED       = 0x02,
    ERRL_CALLOUT_PRIORITY_HIGH      = 0x03,
} ERRL_CALLOUT_PRIORITY;

// These are the user detail types that a user details can have.
// Users must ONLY use these enum values for user detail type
/* User Detail Type */
typedef enum
{
    ERRL_USR_DTL_TRACE_DATA     = 0x01,
    ERRL_USR_DTL_CALLHOME_DATA  = 0x02,
    ERRL_USR_DTL_BINARY_DATA    = 0x03,
    ERRL_USR_DTL_HISTORY_DATA   = 0x04,
    ERRL_USR_DTL_WOF_DATA       = 0x05,
    ERRL_USR_DTL_PGPE_PK_TRACE  = 0x06,
    ERRL_USR_DTL_PGPE_DATA      = 0x07,
} ERRL_USR_DETAIL_TYPE;

// These are the possible OCC States.
/* OCC States */
typedef enum
{
    ERRL_OCC_STATE_INVALID          = 0xFF,
} ERRL_OCC_STATE;

/* Errl Structure Version */
typedef enum
{
    ERRL_STRUCT_VERSION_1       = 0x01,
} ERRL_STRUCT_VERSION;

/* Errl User Details Version */
typedef enum
{
    ERRL_USR_DTL_STRUCT_VERSION_1       = 0x01,
} ERRL_USR_DTL_STRUCT_VERSION;


/* Errl Trace Version */
typedef enum
{
    ERRL_TRACE_VERSION_1       = 0x00,
} ERRL_TRACE_VERSION;

/* Type of Callout */
typedef enum
{
    ERRL_CALLOUT_TYPE_HUID          = 0x01,
    ERRL_CALLOUT_TYPE_COMPONENT_ID  = 0x02,
    ERRL_CALLOUT_TYPE_GPU_ID        = 0x03,
} ERRL_CALLOUT_TYPE;

/* TMGT-OCC Component Ids */
typedef enum
{
    ERRL_COMPONENT_ID_FIRMWARE         = 0x01,
    ERRL_COMPONENT_ID_OVER_TEMPERATURE = 0x04,
    ERRL_COMPONENT_ID_OVERSUBSCRIPTION = 0x05,
    ERRL_COMPONENT_ID_NONE             = 0xFF,
} ERRL_COMPONENT_ID;

/* Callout Structure */
// TMGT_OCC_INTERFACE_v1_2_1
struct ErrlCallout
{
    // Type of callout. NOTE: Users must use ERRL_CALLOUT_TYPE enum
    uint8_t     iv_type;
    // Callout Value
    uint64_t    iv_calloutValue;
    // Callout Priority. NOTE: Users must use ERRL_CALLOUT_PRIORITY enum
    uint8_t     iv_priority;
    // Reserved 1
    uint16_t    iv_reserved1;
} __attribute__ ((__packed__));

typedef struct ErrlCallout ErrlCallout_t;

// The User Detail Entry Structure consists of the fields below followed
// by the actual data the user is trying to collect.
// NOTE: A data pointer field is NOT defined but rather inferred here.  In the
//       error log contents, the user will see all the subsequent fields followed
//       by the actual data
/* User Detail Entry Structure */
struct ErrlUserDetailsEntry
{
    uint8_t     iv_version; // User Details Entry Version
    uint8_t     iv_type;    // User Details Entry Type
                            // Note: Users must use ERRL_USR_DETAIL_TYPE enum
    uint16_t    iv_size;    // User Details Entry Size
} __attribute__ ((__packed__));

typedef struct ErrlUserDetailsEntry ErrlUserDetailsEntry_t;

// The User Detail Structure consists of the fields below followed
// by each individual User Details Entry structure & data
// NOTE: A data pointer field is NOT defined but rather inferred here.  In the
//       error log contents, the user will see all the subsequent fields followed
//       by each User Details Entry structure and its data
/* User Detail Structure */
struct ErrlUserDetails
{
    uint8_t     iv_version;             // User Details Version
    uint8_t     iv_reserved;            // Reserved
    uint16_t    iv_modId;               // Module Id
    uint32_t    iv_fclipHistory;        // Frequency Clip History
    uint64_t    iv_timeStamp;           // Time Stamp
    uint8_t     iv_occId;               // OCC ID
    uint8_t     iv_occRole;             // OCC Role
    uint8_t     iv_operatingState;      // OCC State
    uint8_t     iv_committed:1;         // Log Committed?
    uint8_t     iv_reserved1:7;
    uint32_t    iv_userData1;           // User Data Word 1
    uint32_t    iv_userData2;           // User Data Word 2
    uint32_t    iv_userData3;           // User Data Word 3
    uint16_t    iv_entrySize;           // Log Size
    uint16_t    iv_userDetailEntrySize; // User Details Size
} __attribute__ ((__packed__));

typedef struct ErrlUserDetails ErrlUserDetails_t;

/* Error Log Structure */
// TMGT_OCC_INTERFACE_v1_2_1
struct ErrlEntry
{
    // Log CheckSum
    uint16_t            iv_checkSum;
    // Log Version
    uint8_t             iv_version;
    // Log Entry ID
    uint8_t             iv_entryId;
    // Log Reason Code
    uint8_t             iv_reasonCode;
    // Log Severity - NOTE: Users must use ERRL_SEVERITY enum
    uint8_t             iv_severity;
    // Actions to process the errors
    union
    {
        struct
        {
            uint8_t reset_required     : 1;  // Error is critical and requires OCC reset
            uint8_t safe_mode_required : 1;  // immediate permanent safe mode (used for checkstops)
            uint8_t wof_reset_required : 1;
            uint8_t reserved4          : 1;
            uint8_t mfg_error          : 1;  // Fan go to max,oversubscription,core above warning,Throttled.
            uint8_t reserved2          : 1;
            uint8_t reserved1          : 1;
            uint8_t consolidate_error  : 1;  // Look for same SRC from all OCCs
        };
        uint8_t word;
    } iv_actions;
    // Maximum size for the whole error log including all user details
    uint16_t            iv_maxSize;
    uint16_t            iv_extendedRC;
    // Log Callout Number
    uint8_t             iv_numCallouts;
    // Callouts
    ErrlCallout_t       iv_callouts[ERRL_MAX_CALLOUTS];
    // User Details section for Log
    ErrlUserDetails_t   iv_userDetails;

} __attribute__ ((__packed__));

typedef struct ErrlEntry ErrlEntry_t;

/* Error Log Handle */
typedef ErrlEntry_t* errlHndl_t;

extern uint32_t     G_occErrSlotBits;
extern uint8_t      G_occErrIdCounter;

extern errlHndl_t   G_occErrSlots[ERRL_MAX_SLOTS];

// Shared SRAM offset to access the HCODE Error Log Table
#define HCODE_ELOG_TABLE_SRAM_OFFSET     0x48
#define HCODE_ELOG_TABLE_MAGIC_NUMBER    0x454C5443   // "ELTC"
extern hcode_elog_entry_t *G_hcode_elog_table;
extern uint32_t            G_hcode_elog_table_slots;

typedef enum {
    ERRH_AVSBUS_VDD_CURRENT          =  0x01,
    ERRH_AVSBUS_VDD_VOLTAGE          =  0x02,
    ERRH_AVSBUS_VDN_CURRENT          =  0x03,
    ERRH_AVSBUS_VDN_VOLTAGE          =  0x04,
    ERRH_DIMM_I2C_PORT0              =  0x05,
    ERRH_DIMM_I2C_PORT1              =  0x06,
    ERRH_AVSBUS_VDD_STATUS_READ_FAIL =  0x07,
    ERRH_AVSBUS_VDN_STATUS_READ_FAIL =  0x08,
    ERRH_AVSBUS_VDD_OVER_CURRENT     =  0x09,
    ERRH_AVSBUS_VDN_OVER_CURRENT     =  0x0A,
    ERRH_INVALID_APSS_DATA           =  0x0B,
    ERRH_APSS_COMPLETE_ERROR         =  0x0C,
    ERRH_APSS_COMPLETE_TIMEOUT       =  0x0D,
    ERRH_DCOM_TX_SLV_INBOX           =  0x0E,
    ERRH_DCOM_RX_SLV_INBOX           =  0x0F,
    ERRH_DCOM_TX_SLV_OUTBOX          =  0x10,
    ERRH_DCOM_RX_SLV_OUTBOX          =  0x11,
    ERRH_DCOM_MASTER_PBAX_SEND_FAIL  =  0x12,
    ERRH_DCOM_SLAVE_PBAX_SEND_FAIL   =  0x13,
    ERRH_DCOM_MASTER_PBAX_READ_FAIL  =  0x14,
    ERRH_DCOM_SLAVE_PBAX_READ_FAIL   =  0x15,
    ERRH_GPE0_NOT_IDLE               =  0x16,
    ERRH_GPE1_NOT_IDLE               =  0x17,
    ERRH_24X7_DISABLED               =  0x18,
    ERRH_CEFF_RATIO_VDD_EXCURSION    =  0x19,  // P9 prime: OCS Dirty+type '1' (Act)
    ERRH_AVSBUS_VDD_TEMPERATURE      =  0x1A,
    ERRH_OVER_PCAP_IGNORED           =  0x1B,
    ERRH_VFRT_TIMEOUT_IGNORED        =  0x1C,
    ERRH_WOF_CONTROL_TIMEOUT_IGNORED =  0x1D,
    ERRH_PSTATE_CHANGE_IGNORED       =  0x1E,
    ERRH_VDD_CURRENT_ROLLOVER_MAX    =  0x1F,
    ERRH_CORE_SMALL_DROOP            =  0x20,
    ERRH_CACHE_LARGE_DROOP           =  0x21,
    ERRH_OCS_DIRTY_BLOCK             =  0x22,  // P9 prime: OCS Dirty+type '0' (block)
    ERRH_RESERVED23                  =  0x23,
    ERRH_RESERVED24                  =  0x24,
    ERRH_RESERVED25                  =  0x25,
    ERRH_RESERVED26                  =  0x26,
    ERRH_RESERVED27                  =  0x27,
    ERRH_RESERVED28                  =  0x28,
    ERRH_RESERVED29                  =  0x29,
    ERRH_RESERVED2A                  =  0x2A,
    ERRH_RESERVED2B                  =  0x2B,
    ERRH_RESERVED2C                  =  0x2C,
    ERRH_RESERVED2D                  =  0x2D,
    ERRH_RESERVED2E                  =  0x2E,
    ERRH_RESERVED2F                  =  0x2F,
    ERR_HISTORY_SIZE                 =  0x30
} ERR_HISTORY_INDEX;

// Array of error counters that are only cleared on OCC reset
extern uint8_t G_error_history[ERR_HISTORY_SIZE];
#define INCREMENT_ERR_HISTORY(errorIndex) { \
    if ((errorIndex < ERR_HISTORY_SIZE) && (G_error_history[errorIndex] < 255)) { \
        ++G_error_history[errorIndex]; \
    } \
}

// Globals used by testcases
extern uint8_t      G_errslot1[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_errslot2[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_errslot3[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_errslot4[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_errslot5[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_pgpeslot[MAX_ERRL_PGPE_ENTRY_SZ];
extern uint8_t      G_infoslot[MAX_ERRL_ENTRY_SZ];
extern uint8_t      G_callslot[MAX_ERRL_CALL_HOME_SZ];

/* Create an Error Log */
errlHndl_t createErrl(
            const uint16_t i_modId,
            const uint8_t i_reasonCode,
            const uint16_t i_extReasonCode,
            const ERRL_SEVERITY i_sev,
            const trace_descriptor_array_t* i_trace,
            const uint16_t i_traceSz,
            const uint32_t i_userData1,
            const uint32_t i_userData2
            );

/* Create an Error Log due to a PGPE failure */
errlHndl_t createPgpeErrl(
            const uint16_t i_modId,
            const uint8_t i_reasonCode,
            const uint16_t i_extReasonCode,
            const ERRL_SEVERITY i_sev,
            const uint32_t i_userData1,
            const uint32_t i_userData2
            );

/* Add Trace Data to Error Log */
void addTraceToErrl(
            const trace_descriptor_array_t* i_trace,
            const uint16_t i_traceSz,
            errlHndl_t io_errl
            );

// Add Error history data to the Error Log
void addErrHistory(errlHndl_t io_err);

// Add PGPE specific data to the Error Log
void addPgpeDataToErrl(errlHndl_t io_err);

/* Commit the Error Log */
void commitErrl( errlHndl_t * io_err );

/* Delete the Error Log */
errlHndl_t deleteErrl( errlHndl_t * io_err);

/* Add Callout to Error Log */
void addCalloutToErrl(
            errlHndl_t io_err,
            const ERRL_CALLOUT_TYPE i_type,
            const uint64_t i_calloutValue,
            const ERRL_CALLOUT_PRIORITY i_priority);

/* Add User Details Data to the Error Log */
void addUsrDtlsToErrl(
            errlHndl_t io_err,
            uint8_t *i_dataPtr,
            const uint16_t i_size,
            const uint8_t i_version,
            const ERRL_USR_DETAIL_TYPE i_type);

/* Change Severity of Error Log to Informational */
void setErrlSevToInfo( errlHndl_t io_err );

/* Set Actions to an Errl */
void setErrlActions(errlHndl_t io_err, const uint8_t i_mask);

/* Return Error Log ID to report to TMGT */
uint8_t getErrlLogId( errlHndl_t io_err );

// @nh004a - start
/* Get Error Slot Num By Error Id */
uint8_t getErrSlotNumByErrId( uint8_t  i_errlId);

/* Get Error Slot OCI address */
uint32_t getErrSlotOCIAddr(const uint8_t  i_SlotNum);

/* Get the oldest error log ID so that we can pass it to TMGT */
uint8_t getOldestErrlID();

/* Return Length of an Error  Log based on ID, to send to TMGT */
uint16_t getErrlLengthByID(const uint8_t i_id);

/* Return Address of an Error Log based on ID, to send to TMGT */
uint32_t getErrlOCIAddrByID(const uint8_t i_id);

// NOTE: Not defining these in the .h since they are INTERNAL
//       methods!

#endif //_ERRL_H
