// NoSpark - OpenEVSE charger firmware
// Copyright (C) 2015 Andre Eisenbach
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// See LICENSE for a copy of the GNU General Public License or see
// it online at <http://www.gnu.org/licenses/>

#pragma once

// Query version with $E254 (see below)
#define SAPI_VERSION            1

// Notes about the protocol:
//  - Lines must end in \r or \n
//  - Parameter order does not matter
//  - Optional parameters can be omitted
//  - Commands are synchronous in nature; send $E command, wait for $OK/$ERR response


// Status/error codes -------------------------------------------------


#define OK                      0
#define UNKNOWN_COMMAND         1
#define INVALID_PARAMETER       2


// 'E' commands -------------------------------------------------------


// Returns the current state
//
// Parameters:
//   none
//
//  Returns:
//    J - J1772 state 1=A, 2=B...
//    T - Temperature in C
//    R - Ready state; one off 0 (READY), 1 (SCHEDULE), 2 (KWH LIMIT), 3 (MANUAL)
//
//  Example:
//    -> $E1
//    <- $OK J3 T30 R0
//     = J1772 state C, temperature 30C, ready state "READY"
#define CMD_GET_STATE           1

// Return the current chare status
//
// Parameters:
//   none
//
// Returns:
//   C - Charging (1) or not charging (0)
//   A - Current charge current (optional; only when C1) in mA
//   D - Ongoing or last charge duration in seconds
//   W - Watthours for ongoing or last charge
//
// Example:
//   -> $E2
//   <- $OK C1 A27511 D3632 W6034
//    = Active charge, 27.511A, ~60min, ~6kWh total
#define CMD_GET_CHARGE_STATE    2

// Returns the maximum current supported by the EVSE
//
// Parameters:
//   none
//
// Returns:
//   A - Maximum supported charge current in A
//   L - Current maximum charge limit in A (ex. temperature limited) 
//
// Example:
//   -> $E10
//   <- $OK A40 L20
#define CMD_GET_MAX_CURRENT     10

// Set the maximum supported charge current
//
// Parameters:
//   A - Maximum supported charge current in A
//
// Returns:
//   none
//
// Example:
//   -> $E11 A40
//   <- $OK
#define CMD_SET_MAX_CURRENT     11

// Get the current time from the EVSEs RTC
//
// Parameters:
//   none
//
// Returns:
//   H - Hours of the day (0-23)
//   M - Minute (0-59)
//   S - Second (0-59)
//
// Example:
//   -> $E12
//   <- $OK H12 M34 S56
#define CMD_GET_TIME            12

// Set the current time on the EVSEs RTC
//
// Parameters:
//   H - Hours of the day (0-23; optional)
//   M - Minute (0-59; optional)
//   S - Second (0-59; optional)
//
// Returns:
//   none
//
// Example:
//   -> $E13 H12 M34 S56
//   <- $OK
#define CMD_SET_TIME            13

// Get the current date from the EVSEs RTC
//
// Parameters:
//   none
//
// Returns:
//   D - Day (1-31)
//   M - Month (1-12)
//   Y - Year (0-99)
//   W - Weekday (1-7)
//
// Example:
//   -> $E14
//   <- $OK D24 M12 Y15 W7
#define CMD_GET_DATE            14

// Set the current date on the EVSEs RTC
//
// Parameters:
//   D - Day (1-31; optional)
//   M - Month (1-12; optional)
//   Y - Year (0-99; optional)
//   W - Weekday (1-7; optional)
//
// Returns:
//   none
//
// Example:
//   -> $E15 D24 M12 Y15 W7
//   <- $OK
#define CMD_SET_DATE            15

// Set the LCD sleep state
//
// Parameters:
//   S - LCD sleep enable (1) or wakeup (0)
//
// Returns:
//   none
//
// Example:
//   -> $E20 S1
//   <- $OK
//    = Sets LCD into sleep mode
#define CMD_SET_SLEEP           20

// Set EVSE ready state
//
// Parameters:
//   S - New ready state; 0 = READY, 1 = NOT READY
//
// Returns:
//   none
//
// Example:
//   -> $E21 S1
//   <- $OK
//    = Sets EVSE into MANUAL ready state (interrupts charging)
#define CMD_SET_READY_STATE     21

// Enable or disable debug events
//
// Parameters:
//   S - 1 = enable debug events; 0 = disable events
//
// Returns:
//   none
//
// Example:
//   -> $E30 S1
//   <- $OK
#define CMD_ENABLE_EVENTS       30

// Returns serial API version number
//
// Parameters:
//   none
//
// Returns:
//   V - Serial API revision
//
// Example:
//   -> $E254
//   <- $OK V1
#define CMD_GET_SAPI_VERSION    254
