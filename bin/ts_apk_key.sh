#!/bin/bash

rm -f ts_apk.keystore

keytool -genkey -keyalg RSA -validity 3650 -v -keystore ts_apk.keystore -alias debug -keypass android -storepass android
