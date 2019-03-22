Attribute VB_Name = "Module1"
Option Explicit

Dim FontName() As String
Dim FontWidth() As Integer
Dim FontHeight() As Integer
Dim FontSize() As Integer
Dim AscLBound() As Integer
Dim AscUBound() As Integer
Dim Flag() As String

Private Sub GetList(ListFileName As String)
    Dim lst As String
    Dim lstb() As Byte
    ReDim lstb(FileLen(ListFileName) - 1)
    Open ListFileName For Binary Access Read As #1
    Get #1, , lstb()
    Close #1
    lst = StrConv(lstb(), vbUnicode)

    Dim LineStr() As String
    LineStr() = Split(lst, vbCrLf)
    
    ReDim FontName(UBound(LineStr()))
    ReDim FontWidth(UBound(LineStr()))
    ReDim FontHeight(UBound(LineStr()))
    ReDim FontSize(UBound(LineStr()))
    ReDim AscLBound(UBound(LineStr()))
    ReDim AscUBound(UBound(LineStr()))
    ReDim Flag(UBound(LineStr()))

    Dim i As Long
    
    For i = 0 To UBound(LineStr())
        Dim ss() As String
        ss() = Split(LineStr(i), ";")
        
        FontName(i) = ss(0)
        FontWidth(i) = ss(1)
        FontHeight(i) = ss(2)
        FontSize(i) = ss(3)
        AscLBound(i) = ss(4)
        AscUBound(i) = ss(5)
        Flag(i) = ss(6)
    Next i
End Sub

Private Sub StartWritePackFile(FileName As String)
    On Error Resume Next
    Kill FileName
    On Error GoTo 0
    
    Open FileName For Binary Access Write As #1
End Sub

Private Sub WritePackHeader()
    Put #1, , CLng(UBound(FontName()) + 1)
    
    Dim HeaderLength As Long
    HeaderLength = 4 + (UBound(FontName()) + 1) * 28
    
    Dim i As Long
    Dim length As Long
    length = HeaderLength
    For i = 0 To UBound(FontName())
        Dim BS() As Byte
        BS() = StrConv(FontName(i), vbFromUnicode)
        
        ReDim Preserve BS(7)
        
        Put #1, , BS()
        
        Put #1, , FontWidth(i)
        Put #1, , FontHeight(i)
        Put #1, , FontSize(i)
        Put #1, , AscLBound(i)
        Put #1, , AscUBound(i)
    
        Select Case Flag(i)
        Case "E"
            Put #1, , CInt(&H40)
        Case "ET"
            Put #1, , CInt(&HC0)
        Case "C"
            Put #1, , CInt(&H41)
        Case "CT"
            Put #1, , CInt(&HC1)
        Case Else
            MsgBox "Error flag", vbCritical
            End
        End Select
    
    
        Dim curlen As Long
        curlen = FileLen(FontName(i))
        
        Put #1, , length
        
        length = length + curlen
        
        Put #1, , length
    Next i
End Sub

Private Sub WritePackFileData()
    Dim i As Long
    For i = 0 To UBound(FontName())
        Dim buf() As Byte
        ReDim buf(FileLen(FontName(i)) - 1)
        
        Open FontName(i) For Binary Access Read As #2
        Get #2, , buf()
        Close #2
        
        Put #1, , buf()
    Next i
End Sub

Private Sub EndWritePackFile()
    Close #1
End Sub

Sub Main()
    ChDrive "F:\WorkDir\EleProjects\SaltyProject\SaltyUtility\FONT"
    ChDir "F:\WorkDir\EleProjects\SaltyProject\SaltyUtility\FONT"
    
    GetList "fonts.txt"
    
    StartWritePackFile "Pack.bin"
    WritePackHeader
    WritePackFileData
    EndWritePackFile
    
    MsgBox "done"
End Sub
