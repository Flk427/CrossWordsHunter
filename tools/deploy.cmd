set qt=%1

echo Delpoy.
echo path: %~dp0
echo QT: %qt%

%~d0
cd %~dp0

cd ../bin/CrossWordsHunter
%qt%\bin\windeployqt.exe CrossWordsHunter.exe
xcopy /E /Y ..\..\examples\Storage .\Storage\