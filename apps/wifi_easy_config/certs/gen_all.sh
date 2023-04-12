#!/bin/sh

################################################################################
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
# - Verify that a server certificate is signed by a particular CA. 
#   Use the Ca.crt file and the server.crt file
#      openssl verify -CAfile ca.crt server.crt
#
# - if for any reason the LINE FEED (0x0A) is replaced by CRLF (0x0D 0x0A), 
#   then the following line deletes the 0x0D
#       awk 'BEGIN {RS="\r\n";ORS="\n"} {print $0}' gen_all.sh > gen_all_.sh
#
################################################################################
#
#   mosquitto -v -c /etc/mosquitto/mosquitto.conf
#
#   mosquitto_pub -h 192.168.0.227 -t flat/bulb --cafile /etc/mosquitto/ca_certificates/ca.crt -m "Hello World!" -p 8883 -d
#   mosquitto_sub -h 192.168.0.227 -t flat/bulb --cafile /etc/mosquitto/ca_certificates/ca.crt -p 8883 -d		
#	
#   sysmqtt get info
#	defnet set eth
#   con test.mosquitto.org flat/bulb 1	
#   con 192.168.0.227 flat/bulb 1
#   sub flat/bulb
#   pub Hello_World
#
#   (ip.src == 192.168.0.227 && ip.dst == 192.168.0.32)  || (ip.src == 192.168.0.32 && ip.dst == 192.168.0.227) 
#
#   STA:   wifiprov set 0 1 GEN 0 1 3 MyWorld x3vbrjzW8hrd
#   AP:    wifiprov set 1 1 GEN 1 1 1 DEMO_SOFTAP password
#
#                                   authtype (1-Open 2-WEP 3-Mixed mode(WPA/WPA2) 4-WPA2 5-Mixed mode 6-WPA3)
#                                 ssidVisibility(AP mode only)
#                                 auto connect (STA mode only) 
#                               channel (0 - Enable all channel(STA mode Only))
#                           country code
#                         save config
#                       bootmode (0 -STA,1 - AP)
#
#  
#   netinfo
#
#
#
#     (ip.src == 192.168.0.227 && ip.dst == 192.168.0.32)  || (ip.src == 192.168.0.32 && ip.dst == 192.168.0.227) 
#     
################################################################################


## Control Variables
remove_old_files=0
generate_CA_Certs=0
generate_Server_Certs=0
generate_Client_Certs=0
copy_files=0
convert_files=1

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


if [ $remove_old_files -eq 1 ]
then
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
	
	rm *.der
	rm *.h
fi


if [ $generate_CA_Certs -eq 1 ]
then
	echo === Generate a certificate authority certificate and key === 
	openssl req -new -x509 -days 360 -extensions v3_ca -keyout ca.key -out ca.crt -subj /CN=$ca_common_name/O=$ca_org_name/C=$ca_country/ST=$ca_st -passout pass:$ca_pass
fi


if [ $generate_Server_Certs -eq 1 ]
then
	echo ===  Generate a server key === 
	#openssl genrsa -des3 -passout pass:$sv_pass -out server.key 2048
	# => no passphrase used for server. Key is stored without encryption
	openssl genrsa -out server.key 2048

	echo === generate a certificate signing request to send to the CA === 
	openssl req -new -out server.csr -key server.key -subj /CN=$sv_common_name/O=$sv_org_name

	echo === Send the CSR to the CA, or sign it with your CA key === 
	openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 360 -passin pass:$ca_pass
fi


if [ $generate_Client_Certs -eq 1 ]
then
	echo === Generate a client key === 
	#openssl genrsa -des3 -passout pass:$cl_pass -out client.key 2048
	# => no assphrase used for server. Key is stored without encryption
	openssl genrsa -out client.key 2048

	echo === Generate a certificate signing request to send to the CA === 
	#openssl req -out client.csr -key client.key -new -subj /CN=$cl_common_name/O=$cl_org_name -passin pass:$cl_pass
	openssl req -out client.csr -key client.key -new -subj /CN=$cl_common_name/O=$cl_org_name 

	echo === Send the CSR to the CA, or sign it with your CA key === 
	openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client.crt -days 360 -passin pass:$ca_pass
fi


if [ $copy_files -eq 1 ]
then
	echo === copy files to mosquitto folders ===
	cp ca.crt /etc/mosquitto/ca_certificates/
	cp server.crt /etc/mosquitto/certs/
	cp server.key /etc/mosquitto/certs/
	cp mosquitto.conf /etc/mosquitto/
fi 


if [ $convert_files -eq 1 ]
then
	echo === convert files from ASN.1 to DER and C Header ===
	
	openssl asn1parse -in ca.crt -out ca_cert.der
	xxd -i ca_cert.der >ca_cert.h 
	cp ca_cert.h ../firmware/src/third_party/wolfssl/wolfssl/
	
	openssl asn1parse -in server.crt -out server_cert.der
	xxd -i server_cert.der >server_cert.h 
	cp server_cert.h ../firmware/src/third_party/wolfssl/wolfssl/	

	openssl asn1parse -in server.key -out server_key.der
	xxd -i server_key.der >server_key.h 
	cp server_key.h ../firmware/src/third_party/wolfssl/wolfssl/	

	openssl asn1parse -in client.crt -out client_cert.der
	xxd -i client_cert.der >client_cert.h 
	cp client_cert.h ../firmware/src/third_party/wolfssl/wolfssl/	

	openssl asn1parse -in client.key -out client_key.der
	xxd -i client_key.der >client_key.h 
	cp client_key.h ../firmware/src/third_party/wolfssl/wolfssl/	
	
	cat client_cert.h client_key.h >> device-certs.h
	cp device-certs.h ../firmware/src/third_party/wolfssl/wolfssl/	
	
fi 

