'https://stackoverflow.com/questions/24613007/convert-xlsx-file-to-html-with-vbscript-or-batch-script
'Excel lets you save as a web page natively.
'It also has a "single file" web page that combines all images/etc into a single file.
'It uses the mht or mhtml extension.

'https://www.vbsedit.com/scripts/office/word/scr_766.asp
'Save a Microsoft Word Document as an HTML File

On Error Resume Next

Const wdFormatHTML = 8
Const wdFormatFilteredHTML = 10 'for Filtered HTML output

Const xlHtml = 44
Const xlWebArchive = 45

Dim result : result = 0

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
	Set objDoc = objWord.Documents.Open(src)
	objDoc.SaveAs dest, wdFormatFilteredHTML
	objWord.Quit
	result = 1
End Function


' text / table
Dim docType : docType = WScript.Arguments.Item(0)
Dim path : path = WScript.Arguments.Item(1)
Dim destFile : destFile = WScript.Arguments.Item(2)

if docType = "text" Then
	importExcelFile path, destFile
Else
	If docType = "table" Then
		importWordFile path, destFile
	End If
End If

If result = 0 Then
'	WScript.Echo "Ошибка импорта"
	WScript.Quit 2
End If
