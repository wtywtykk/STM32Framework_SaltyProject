Attribute VB_Name = "Module1"
Option Explicit
Dim length As Integer

Function transedition(val As Integer) As Integer
    transedition = CInt("&h" & Hex(val \ &HFF& Or (val Mod &H100&) * &H100&))
End Function

Sub Main()
    'ChDrive "C:\Users\thik\Desktop\新建文件夹"
    'ChDir "C:\Users\thik\Desktop\新建文件夹"
    
    Dim lst As String
    Dim lstb() As Byte
    ReDim lstb(FileLen("lst.txt") - 1)
    Open "lst.txt" For Binary Access Read As #1
    Get #1, , lstb()
    Close #1
    lst = StrConv(lstb(), vbUnicode)
    Dim s() As String, i As Long
    s = Split(lst, vbCrLf)
    
    On Error Resume Next
    Kill "EEPROM.bin"
    On Error GoTo 0
    
    Open "EEPROM.bin" For Binary Access Write As #1
    
    For i = 1 To 512
        Dim b As Byte
        b = &HFF
        Put #1, , b
    Next i
    
    For i = 0 To UBound(s())
        If s(i) <> "" Then length = length + 4
    Next i
    
    For i = 0 To UBound(s())
        If s(i) <> "" Then
            Dim curlen As Integer
            curlen = FileLen(s(i))
            Put #1, , transedition(length)
            Put #1, , transedition(curlen)
            length = length + curlen
        End If
    Next i
    
    For i = 0 To UBound(s())
        If s(i) <> "" Then
            Dim buf() As Byte
            ReDim buf(FileLen(s(i)) - 1)
            Open s(i) For Binary Access Read As #2
            Get #2, , buf()
            Close #2
            Put #1, , buf()
        End If
    Next i
    
    Close #1
    
    MsgBox "done"
End Sub
