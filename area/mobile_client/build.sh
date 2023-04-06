#!/bin/sh -x

flutter build apk 
cp build/app/outputs/flutter-apk/app-release.apk /apk/client.apk