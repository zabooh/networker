 /*******************************************************************************
 Source file for the Net Pres Certificate Store functions to work with Harmony


  Summary:


  Description:

*******************************************************************************/

/*****************************************************************************
 Copyright (C) 2015-2018 Microchip Technology Inc. and its subsidiaries.

Microchip Technology Inc. and its subsidiaries.

Subject to your compliance with these terms, you may use Microchip software 
and any derivatives exclusively with Microchip products. It is your 
responsibility to comply with third party license terms applicable to your 
use of third party software (including open source software) that may 
accompany Microchip software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR 
PURPOSE.

IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE 
FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN 
ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, 
THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*****************************************************************************/

#include "net_pres/pres/net_pres_certstore.h"
#define USE_CERT_BUFFERS_2048
#include "wolfssl/ca_cert.h"
#include "wolfssl/device-certs.h"
#define USE_CERT_BUFFERS_2048
#include "wolfssl/server_cert.h"
#include "wolfssl/server_key.h"

bool NET_PRES_CertStoreGetCACerts(const uint8_t ** certPtr, int32_t * certSize, uint8_t certIndex)
{
    *certPtr = ca_cert_der;
    *certSize = ca_cert_der_len;
    return true;
}
bool NET_PRES_CertStoreGetDeviceTlsParams(const uint8_t ** certPtr, int32_t * certSize, const uint8_t ** pvtKeyPtr, int32_t * pvtKeySize, uint8_t certIndex)
{
    *certPtr = client_cert_der;
    *certSize = client_cert_der_len;
    *pvtKeyPtr = client_key_der;
    *pvtKeySize = client_key_der_len;
    return true;
}
bool NET_PRES_CertStoreGetServerCert(const uint8_t ** serverCertPtr, int32_t * serverCertSize, const uint8_t ** serverKeyPtr, int32_t * serverKeySize, uint8_t certIndex)
{
    *serverCertPtr = server_cert_der;
    *serverCertSize = server_cert_der_len;
    *serverKeyPtr = server_key_der;
    *serverKeySize = server_key_der_len;
    return true;
}
