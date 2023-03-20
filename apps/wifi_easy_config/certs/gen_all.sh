#!/bin/sh

# Some Comments (20.03.2023): 
#
# - with parameter "-nodes" (no DES) instead 
#   of "-passout pass:passphrase", no passphrase is used  
#
# - When prompted for the CN (Common Name), please enter 
#   either your server (or broker) hostname or domain name
#   or the parametr -subj is used inclu. variables
#
# - Read CN with
#      openssl x509 -noout -subject -in ca.crt
#
# - when then random seed file is not available it can be
#   produced with: 
#      openssl rand -writerand /home/zabooh/.rnd 
#
# - the CA file is protected by a passphrase. The client and
#   and server keys are not protected. but could be, if wished.
#   The client keys are not protected becasue it would need additional
#   effort to decrypt on the microcontroller side
#   The Server key is not protected to make it more convinient for 
#   the test setup. but it should be. 
#
# - all cert files and the mosquitto.conf file are copied to 
#     /etc/mosquitto/
#
# - start mosquitto with 
#      mosquitto -v -c /etc/mosquitto/mosquitto.conf
#
#
#

# === Certificate Authority Setup ===
ca_common_name="192.168.0.227"
ca_org_name="Microchip"
ca_country="DE"
ca_st="Some-State"
ca_pass="ca_passphrase"

# === Server Setup ===
sv_common_name="192.168.0.227"
sv_org_name="Microchip"
sv_pass="sv_passphrase"

# === Client Setup ===
cl_common_name="192.168.0.227"
cl_org_name="Microchip"
cl_pass="cl_passphrase"


echo ===  Remove all Files ===
rm ca.crt
rm ca.key
rm ca.srl

rm client.key
rm client.crt
rm client.csr

rm server.key
rm server.crt
rm server.csr

echo === Generate a certificate authority certificate and key === 
openssl req -new -x509 -days 360 -extensions v3_ca -keyout ca.key -out ca.crt -subj /CN=$ca_common_name/O=$ca_org_name/C=$ca_country/ST=$ca_st -passout pass:$ca_pass

echo ===  Generate a server key === 
#openssl genrsa -des3 -passout pass:$sv_pass -out server.key 2048
# => no passphrase used for server. Key is stored without encryption
openssl genrsa -out server.key 2048

echo === generate a certificate signing request to send to the CA === 
openssl req -new -out server.csr -key server.key -subj /CN=$sv_common_name/O=$sv_org_name

echo === Send the CSR to the CA, or sign it with your CA key === 
openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 360 -passin pass:$ca_pass

echo === Generate a client key === 
#openssl genrsa -des3 -passout pass:$cl_pass -out client.key 2048
# => no assphrase used for server. Key is stored without encryption
openssl genrsa -out client.key 2048

echo === Generate a certificate signing request to send to the CA === 
#openssl req -out client.csr -key client.key -new -subj /CN=$cl_common_name/O=$cl_org_name -passin pass:$cl_pass
openssl req -out client.csr -key client.key -new -subj /CN=$cl_common_name/O=$cl_org_name 

echo === Send the CSR to the CA, or sign it with your CA key === 
openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client.crt -days 360 -passin pass:$ca_pass

echo === copy files to mosquitto folders ===
cp ca.crt /etc/mosquitto/ca_certificates/
cp server.crt /etc/mosquitto/certs/
cp server.key /etc/mosquitto/certs/
cp mosquitto.conf /etc/mosquitto/
