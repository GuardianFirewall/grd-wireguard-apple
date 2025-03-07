// SPDX-License-Identifier: MIT
// Copyright © 2018-2021 WireGuard LLC. All Rights Reserved.

#include "key.h"
#include "x25519.h"
#include <sys/types.h>


//
// Note from CJ 2024-06-13
// Xcode 16 beta 1 broke compatibility by removing the type definitions for u_int32_t
// which are old lingering references to the BSD origins of xnu
// https://opensource.apple.com/source/xnu/xnu-344/bsd/sys/kern_control.h.auto.html
// There are two ways to resolve this
//
// this way
// typedef unsigned int u_int32_t;
// typedef unsigned char u_char;
// typedef unsigned short u_int16_t;
//
// or
// typedef uint32_t u_int32_t;
// typedef uint8_t u_char;
// typedef uint16_t u_int16_t;
//
// I opted for skipping right past all of the typedefs and using the solution below

//
// Note from CJ 2025-03-07
// the saga continues with Xcode 16...https://github.com/WireGuard/wireguard-apple/pull/33 & https://stackoverflow.com/questions/79002585/wireguardkitc-h-failing-to-compile-in-xcode-16-0
//
// In order to easily resolve this I opted to resorting back to
// using types that matches those in kern_control.h which are old typedefs
// and importing sys/types.h to make it all make sense
//
// old fix:
// struct ctl_info {
//	unsigned int   	ctl_id;
//	char        	ctl_name[96];
// };
//
//
// struct sockaddr_ctl {
// unsigned char    sc_len;
// unsigned char    sc_family;
// unsigned short   ss_sysaddr;
// unsigned int   	sc_id;
// unsigned int   	sc_unit;
// unsigned int		sc_reserved[5];
// };
//

/* From <sys/kern_control.h> */
#define CTLIOCGINFO 0xc0644e03UL
struct ctl_info {
	u_int32_t   ctl_id;
    char        ctl_name[96];
};
struct sockaddr_ctl {
    u_char      sc_len;
    u_char      sc_family;
	u_int16_t	ss_sysaddr;
	u_int32_t   sc_id;
	u_int32_t   sc_unit;
	u_int32_t   sc_reserved[5];
};
