#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

sleep, 2000
loop, read, <FILE PATH TO AUTOGEN OUTPUT GOES HERE>
{
	sendInput,%  a_loopReadLine
	sleep, 5 
	sendInput,{Down}
}

