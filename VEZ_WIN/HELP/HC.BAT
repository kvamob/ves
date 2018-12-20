@echo off
if NOT "%1" == "-n" hc31 %1 %2
if "%1" == "-n" hc31 %2 %3
copy veshelp.hlp \user\vez\win\veshelp.hlp
@echo on
