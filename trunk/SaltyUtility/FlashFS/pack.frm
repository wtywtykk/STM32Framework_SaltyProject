VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4530
   ClientLeft      =   120
   ClientTop       =   465
   ClientWidth     =   5310
   LinkTopic       =   "Form1"
   ScaleHeight     =   4530
   ScaleWidth      =   5310
   StartUpPosition =   3  '窗口缺省
   Begin VB.TextBox Text1 
      Height          =   3735
      Left            =   240
      MultiLine       =   -1  'True
      TabIndex        =   1
      Text            =   "pack.frx":0000
      Top             =   240
      Width           =   2295
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   3360
      TabIndex        =   0
      Top             =   3000
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim length As Integer

Sub measurefile(filename As String)
    Dim cuelen As Integer
    curlen = FileLen(filename)
    Put #1, , length
    Put #1, , curlen
    length = length + curlen
End Sub


Private Sub Command1_Click()
    ChDrive "C:\Users\thik\Desktop\新建文件夹"
    ChDir "C:\Users\thik\Desktop\新建文件夹"
    
    On Error Resume Next
    Kill "EEPROM.bin"
    On Error GoTo 0
    
    Open "EEPROM.bin" For Binary Access Write As #1
    
    Dim s() As String, i As Long
    s = Split(Text1.Text, vbCrLf)
    For i = 0 To UBound(s())
        measurefile s(i)
    Next i
    
    For i = 0 To UBound(s())
        //measurefile s(i)
    Next i
    
    Close #1
End Sub
