#!/bin/sh

# Some Comments: 
#
# - with parameter "-nodes" (no DES) instead 
#   of "-passout pass:passphrase", no passphrase is used  
#
# - When prompted for the CN (Common Name), please enter 
#   either your server (or broker) hostname or domain name
#   or the parametr -subj is used inclu. variables
#

ca_common_name="192.168.0.227"
ca_org_name="Microchip"
ca_pass="start"

sv_common_name="192.168.0.227"
sv_org_name="Microchip"
sv_pass="start"

cl_common_name="192.168.0.32"
cl_org_name="Microchip"
cl_pass="start"

echo ===  Remove all Files ===
rm ca.crt
rm ca.key
rm ca.srl

rm client.key
rm client.crt
rm client.csr

rm server.key

echo === Generate a certificate authority certificate and key === 
openssl req -new -x509 -days 360 -extensions v3_ca -keyout ca.key -out ca.crt -subj /CN=$ca_common_name/O=$ca_org_name -passout pass:$ca_pass

echo ===  Generate a server key === 
openssl genrsa -des3 -passout pass:$sv_pass -out server.key 2048

echo === Generate a server key without encryption === 
openssl genrsa -out server.key 2048

echo === generate a certificate signing request to send to the CA === 
openssl req -out server.csr -key server.key -new -subj /CN=$sv_common_name/O=$sv_org_name

echo === Send the CSR to the CA, or sign it with your CA key === 
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 360 -passin pass:$ca_pass

echo === Generate a client key === 
openssl genrsa -des3 -passout pass:$cl_pass -out client.key 2048

echo === Generate a certificate signing request to send to the CA === 
openssl req -out client.csr -key client.key -new -subj /CN=$cl_common_name/O=$cl_org_name -passin pass:$cl_pass

echo === Send the CSR to the CA, or sign it with your CA key === 
openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client.crt -days 360 -passin pass:$ca_pass

