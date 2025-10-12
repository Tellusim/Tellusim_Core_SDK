@echo off

signtool.exe sign /fd sha256 /tr http://ts.ssl.com /td sha256 %*
