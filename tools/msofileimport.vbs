'https://stackoverflow.com/questions/24613007/convert-xlsx-file-to-html-with-vbscript-or-batch-script
'Excel lets you save as a web page natively.
'It also has a "single file" web page that combines all images/etc into a single file.
'It uses the mht or mhtml extension.

'https://www.vbsedit.com/scripts/office/word/scr_766.asp
'Save a Microsoft Word Document as an HTML File

'http://www.robvanderwoude.com/vbstech_automation_word.php

Option Explicit
On Error Resume Next

Const wdFormatHTML = 8
Const wdFormatFilteredHTML = 10 'for Filtered HTML output

Const xlHtml = 44
Const xlWebArchive = 45

Dim result : result = 0
Dim objWord
Dim objExcel

'''''''''''''''''''''''''''''''''''
Function importExcelFile(src, dest)
	'WScript.Echo src & " " & dest

	' Create an instance of Excel and open the workbook...
	Set objExcel = CreateObject("Excel.Application")
	objExcel.Visible = False
	objExcel.Workbooks.Open src
	' Save the workbook as an HTML or MHTML page...
	'objExcel.ActiveWorkbook.SaveAs "C:\Folder\MyPage.html",  xlHtml
	objExcel.ActiveWorkbook.SaveAs dest, xlHtml
	' -or-
	'objExcel.ActiveWorkbook.SaveAs "C:\Folder\MyPage.mhtml", xlWebArchive
	' Close Excel...
	objExcel.Quit

	'create the excel object
	'Set objExcel = CreateObject("Excel.Application") 
	'view the excel program and file, set to false to hide the whole process
	'objExcel.Visible = False
	'open an excel file (make sure to change the location) .xls for 2003 or earlier
	'Set objWorkbook = objExcel.Workbooks.Open(src)
	'set a cell value at row 3 column 5
	'objExcel.Cells(3,5).Value = "new value"
	'change a cell value
	'objExcel.Cells(3,5).Value = "something different"
	'delete a cell value
	'objExcel.Cells(3,5).Value = ""
	'get a cell value and set it to a variable
	'r3c5 = objExcel.Cells(3,5).Value
	'save the existing excel file. use SaveAs to save it as something else
	'objWorkbook.Save
	'close the workbook
	'objWorkbook.Close 
	'exit the excel program
	'objExcel.Quit
	'release objects
	'Set objExcel = Nothing
	'Set objWorkbook = Nothing
	
	result = 1
End Function


''''''''''''''''''''''''''''''''''
Function importWordFile(src, dest)
	'WScript.Echo src & " " & dest
	
	Set objWord = CreateObject("Word.Application")
	objWord.Visible = False

	objWord.Documents.Open src
	objWord.ActiveDocument.SaveAs dest, wdFormatFilteredHTML

	'Set objDoc = objWord.Documents.Open(src)
	'objDoc.SaveAs dest, wdFormatFilteredHTML
	objWord.Quit
	result = 1
End Function

Sub Doc2HTML( myFile , destFile)
' This subroutine opens a Word document,
' then saves it as HTML, and closes Word.
' If the HTML file exists, it is overwritten.
' If Word was already active, the subroutine
' will leave the other document(s) alone and
' close only its "own" document.
'
' Written by Rob van der Woude
' http://www.robvanderwoude.com
    ' Standard housekeeping
    Dim objDoc, objFile, objFSO, strFile, strHTML

    Const wdFormatDocument                    =  0
    Const wdFormatDocument97                  =  0
    Const wdFormatDocumentDefault             = 16
    Const wdFormatDOSText                     =  4
    Const wdFormatDOSTextLineBreaks           =  5
    Const wdFormatEncodedText                 =  7
    Const wdFormatFilteredHTML                = 10
    Const wdFormatFlatXML                     = 19
    Const wdFormatFlatXMLMacroEnabled         = 20
    Const wdFormatFlatXMLTemplate             = 21
    Const wdFormatFlatXMLTemplateMacroEnabled = 22
    Const wdFormatHTML                        =  8
    Const wdFormatPDF                         = 17
    Const wdFormatRTF                         =  6
    Const wdFormatTemplate                    =  1
    Const wdFormatTemplate97                  =  1
    Const wdFormatText                        =  2
    Const wdFormatTextLineBreaks              =  3
    Const wdFormatUnicodeText                 =  7
    Const wdFormatWebArchive                  =  9
    Const wdFormatXML                         = 11
    Const wdFormatXMLDocument                 = 12
    Const wdFormatXMLDocumentMacroEnabled     = 13
    Const wdFormatXMLTemplate                 = 14
    Const wdFormatXMLTemplateMacroEnabled     = 15
    Const wdFormatXPS                         = 18
    Const wdFormatOfficeDocumentTemplate      = 23
    Const wdFormatMediaWiki                   = 24

    ' Create a File System object
    Set objFSO = CreateObject( "Scripting.FileSystemObject" )

    ' Create a Word object
    Set objWord = CreateObject( "Word.Application" )

    With objWord
        ' True: make Word visible; False: invisible
        .Visible = False

        ' Check if the Word document exists
        If objFSO.FileExists( myFile ) Then
            Set objFile = objFSO.GetFile( myFile )
            strFile = objFile.Path
        Else
            WScript.Echo "FILE OPEN ERROR: The file does not exist" & vbCrLf
            ' Close Word
            .Quit
            Exit Sub
        End If
        ' Build the fully qualified HTML file name
        'strHTML = objFSO.BuildPath( objFile.ParentFolder, _
        '          objFSO.GetBaseName( objFile ) & ".html" )
        strHTML = destFile

        ' Open the Word document
        .Documents.Open strFile

        ' Make the opened file the active document
        Set objDoc = .ActiveDocument

        ' Save as HTML
        objDoc.SaveAs strHTML, wdFormatFilteredHTML

        ' Close the active document
        objDoc.Close

        ' Close Word
        .Quit
    End With

	result = 1
End Sub 

Sub quitWord
	objWord.Quit
End Sub

Sub quitExcel
	objExcel.Quit
End Sub


' text / table
Dim docType : docType = WScript.Arguments.Item(0)
Dim path : path = WScript.Arguments.Item(1)
Dim destFile : destFile = WScript.Arguments.Item(2)

'WScript.Echo docType
'WScript.Echo path
'WScript.Echo destFile

if docType = "text" Then
	If docType = "text" Then
		importWordFile path, destFile
'		Doc2HTML path, destFile
		quitWord
	End If
Else
	importExcelFile path, destFile
	quitExcel
End If

if Err.Number<>0 then
'   WScript.Echo Err.Description
end if

If result = 0 Then
'	WScript.Echo "Ошибка импорта"
	WScript.Quit 2
End If
