On Error Resume Next

' text / table
Dim docType : docType = WScript.Arguments.Item(0)
Dim path : path = Replace(WScript.Arguments.Item(1), "\", "/")
Dim destFile : destFile = Replace(WScript.Arguments.Item(2), "\", "/")

Dim Url : Url = "file:///" & path
Dim Url2 : Url2 = "file:///" & destFile

'WScript.Echo Url
'WScript.Echo Url2

'Set oShell = WScript.CreateObject ("WScript.Shell")
'oShell.run "cmd.exe /C cat """ & Url & """ > test.aaa"

'Подключаемся к COM-серверу  и создаём xls-документ.
Dim mcServiceManager : Set mcServiceManager = CreateObject("com.sun.star.ServiceManager")
Dim mcProperties : Set mcProperties = mcServiceManager.Bridge_GetStruct( "com.sun.star.beans.PropertyValue" )
 
Dim oDesk : Set oDesk = mcServiceManager.createInstance("com.sun.star.frame.Desktop")

'Не показывать на экране
mcProperties.Name  = "Hidden"
'mcProperties.Value = False
mcProperties.Value = True
Dim args(1) : Set args(0) = mcProperties

'Новый документ
Dim Doc : Set Doc = oDesk.loadComponentFromURL(Url, "_blank", 0, args)

Dim FileProperties(1)

mcProperties.Name = "FilterName"

if docType = "text" then
	mcProperties.Value ="HTML (StarWriter)"
else
	mcProperties.Value ="HTML (StarCalc)"
end if

'mcProperties.Value ="Text - txt - csv (StarCalc)"
Set FileProperties(0) = mcProperties

'mcProperties.Name = "FilterOptions"
'mcProperties.value  = "44,34,0,1"
'Set FileProperties(1) = mcProperties

Doc.storeToUrl Url2, FileProperties

'Удаляем инстанцию
Doc.Dispose
