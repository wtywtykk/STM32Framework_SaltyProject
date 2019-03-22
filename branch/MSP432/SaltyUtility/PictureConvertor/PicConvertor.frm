VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3675
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   5580
   LinkTopic       =   "Form1"
   ScaleHeight     =   245
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   372
   StartUpPosition =   3  'Windows Default
   Begin VB.PictureBox Pic 
      AutoRedraw      =   -1  'True
      AutoSize        =   -1  'True
      Height          =   3015
      Left            =   0
      ScaleHeight     =   197
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   253
      TabIndex        =   0
      Top             =   0
      Width           =   3855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Const RED As Integer = &HF800
Const GREEN As Integer = &H7E0
Const BLUE As Integer = &H1F

Private Function ConvertRGB888ToRGB565(RGB888 As Long) As Integer
    Dim RGB888Val() As Byte
    RGB888Val = GetRGB(RGB888)
    Dim R As Byte
    Dim G As Byte
    Dim B As Byte
    R = RGB888Val(0)
    G = RGB888Val(1)
    B = RGB888Val(2)
    ConvertRGB888ToRGB565 = (SHL16(R, 8) And RED) Or (SHL16(G, 3) And GREEN) Or (SHR16(B, 3) And BLUE)
End Function

Private Sub OpenOutputFile()
    Dim SplitPath() As String
    Dim OutputPath As String
    SplitPath = Split(VBA.Command$, ".")
    If UBound(SplitPath()) > 0 Then
        SplitPath(UBound(SplitPath())) = "SP"
        OutputPath = Join(SplitPath(), ".")
    Else
        OutputPath = VBA.Command$ & ".SP"
    End If
    On Error Resume Next
    Kill OutputPath
    On Error GoTo 0
    Open OutputPath For Binary Access Write As #1
End Sub

Private Sub CloseOutputFile()
    Close #1
End Sub

Private Sub Form_Load()
    If VBA.Command$ = "" Then
        MsgBox "No input file!", vbCritical
        End
    End If
    On Error GoTo Err
    Set Pic.Picture = LoadPicture(VBA.Command$)
    
    OpenOutputFile
    Dim PicWidth As Integer
    Dim PicHeight As Integer
    PicWidth = Pic.ScaleWidth
    PicHeight = Pic.ScaleHeight
    Put #1, , PicWidth
    Put #1, , PicHeight
    Dim x As Long
    Dim y As Long
    For y = 0 To PicHeight - 1
        For x = 0 To PicWidth - 1
            Put #1, , ConvertRGB888ToRGB565(Pic.Point(x, y))
        Next x
    Next y
    CloseOutputFile
    MsgBox "Done", vbInformation
    End
Err:
    MsgBox Err.Description, vbCritical
    End
End Sub
