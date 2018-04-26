@echo off

echo Create BIN dir.
echo path: %~dp0

%~d0
cd %~dp0

if not exist ..\bin (
	echo make bin
	mkdir ..\bin
)

if not exist ..\bin\CrossWordsHunter (
	echo make CrossWordsHunter
	mkdir ..\bin\CrossWordsHunter
)
