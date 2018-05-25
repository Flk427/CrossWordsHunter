set qt=%1

echo Delpoy.
echo path: %~dp0
echo QT: %qt%

%~d0
cd %~dp0

cd ../bin/CrossWordsHunter
%qt%\bin\windeployqt.exe CrossWordsHunter.exe
xcopy /E /Y ..\..\examples\Storage .\Storage\
xcopy /E /Y ..\..\tools\vcredist_x86_2012.exe .\
xcopy /E /Y ..\..\tools\msofileimport.vbs .\
xcopy /E /Y ..\..\tools\oofileimport.vbs .\
