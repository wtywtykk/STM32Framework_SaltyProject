VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Form1"
   ClientHeight    =   5280
   ClientLeft      =   45
   ClientTop       =   390
   ClientWidth     =   5775
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   352
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   385
   StartUpPosition =   3  'Windows Default
   Begin VB.ListBox LstDevice 
      Height          =   2595
      ItemData        =   "Down.frx":0000
      Left            =   120
      List            =   "Down.frx":0002
      TabIndex        =   5
      Top             =   2520
      Width           =   1455
   End
   Begin VB.FileListBox FileList 
      Height          =   2625
      Left            =   1680
      TabIndex        =   4
      Top             =   2520
      Width           =   3975
   End
   Begin VB.TextBox TxtInfo 
      Height          =   2295
      Left            =   3120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   3
      Text            =   "Down.frx":0004
      Top             =   120
      Width           =   2535
   End
   Begin VB.CommandButton CmdDownload 
      Caption         =   "下载"
      Height          =   615
      Left            =   120
      TabIndex        =   1
      Top             =   1200
      Width           =   2892
   End
   Begin VB.ComboBox CobPort 
      Height          =   315
      Left            =   480
      Style           =   2  'Dropdown List
      TabIndex        =   0
      Top             =   840
      Width           =   2532
   End
   Begin MSCommLib.MSComm Comm 
      Left            =   1920
      Top             =   1680
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      InBufferSize    =   10240
      BaudRate        =   115200
   End
   Begin VB.Label LabProgress 
      Alignment       =   2  'Center
      BackStyle       =   0  'Transparent
      Caption         =   "Ready"
      Height          =   255
      Left            =   120
      TabIndex        =   2
      Top             =   480
      Width           =   2895
   End
   Begin VB.Shape ShpProgressOuter 
      Height          =   255
      Left            =   120
      Top             =   480
      Width           =   2895
   End
   Begin VB.Shape ShpProgressInner 
      FillColor       =   &H0000FF00&
      FillStyle       =   0  'Solid
      Height          =   255
      Left            =   120
      Top             =   480
      Width           =   375
   End
   Begin VB.Shape ShpCommState 
      FillColor       =   &H00808080&
      FillStyle       =   0  'Solid
      Height          =   255
      Left            =   120
      Shape           =   3  'Circle
      Top             =   840
      Width           =   255
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Function lstrcpy Lib "kernel32" Alias "lstrcpyA" (ByVal lpString1 As String, ByVal lpString2 As Long) As Long
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (Destination As Any, Source As Any, ByVal Length As Long)
Private Declare Function GetTickCount Lib "kernel32" () As Long
Private Declare Sub Sleep Lib "kernel32" (ByVal dwMilliseconds As Long)


Private Const InsDetect As Byte = &HA0
Private Const InsConnect As Byte = &HA1
Private Const InsIsReady As Byte = &HA2
Private Const InsErase As Byte = &HA3
Private Const InsWriteBytes As Byte = &HA4
Private Const InsReadBytes As Byte = &HA5
Private Const InsCheckBytes As Byte = &HA6
Private Const InsReadInformationBlock As Byte = &HA7
Private Const InsDisConnect As Byte = &HB0
Private Const InsReset As Byte = &HB1


Private Const EraseSector = 0
Private Const EraseBlock = 1
Private Const EraseChip = 2


Private Const DetectReply As Byte = &HC0
Private Const ConnectReply As Byte = &HC1
Private Const Ready As Byte = &HC2
Private Const ErrorOccured As Byte = &HC3
Private Const InvalidInstruction As Byte = &HD0
Private Const WrongStatus As Byte = &HD1

Dim FileData() As Byte

Private Sub SendByte(Data As Byte)
    Dim B(0) As Byte
    B(0) = Data
    Comm.Output = B()
End Sub

Private Sub SendLong(Data As Long)
    SendByte GetU32U8(Data, 0)
    SendByte GetU32U8(Data, 1)
    SendByte GetU32U8(Data, 2)
    SendByte GetU32U8(Data, 3)
End Sub

Private Sub EmptyInputBuffer()
    Comm.InputLen = 0
End Sub

Private Function ReceiveByte(ByRef Data As Byte, Timeout As Long) As Boolean
    On Error GoTo Err
    Dim ST As Long
    ST = GetTickCount()
    Dim B() As Byte
    Do
        B = Comm.Input
        If GetTickCount() > ST + Timeout Then
            ReceiveByte = False
            Exit Function
        End If
    Loop Until UBound(B()) > -1
    Data = B(0)
    ReceiveByte = True
    Exit Function
Err:
    ReceiveByte = False
End Function

Private Function Detect() As Boolean
    EmptyInputBuffer
    SendByte InsDetect
    Dim B As Byte
    If ReceiveByte(B, 100) Then
        If B = DetectReply Then
            Detect = True
            Exit Function
        End If
    End If
    Detect = False
End Function

Private Function Connect(DeviceIndex As Byte) As Boolean
    If Not Detect() Then
        Connect = False
        Exit Function
    End If
    
    On Error GoTo Err
    EmptyInputBuffer
    SendByte InsConnect
    SendByte DeviceIndex
    Dim B As Byte
    If ReceiveByte(B, 100) Then
        Select Case B
        Case ConnectReply
            Connect = True
        Case WrongStatus
            SendByte InsDisConnect
            Connect = Connect(DeviceIndex)
        Case Else
            Connect = False
        End Select
    End If
    Exit Function
Err:
    Connect = False
End Function

Private Sub DisConnect()
    SendByte InsDisConnect
End Sub

Private Function WaitReady(Times As Long) As Boolean
    Dim i As Long
    For i = 0 To Times
        Dim B As Byte
        SendByte InsIsReady
        If ReceiveByte(B, 100) Then
            If B = Ready Then
                WaitReady = True
                Exit Function
            End If
        End If
        DoEvents
    Next i
    WaitReady = False
End Function

Private Function LoadFile(FileName As String) As Boolean
    On Error GoTo Err
    ReDim FileData(FileLen(FileName) - 1)
    
    Open FileName For Binary Access Read As #1
    Get #1, , FileData()
    Close #1
    
    LoadFile = True
    Exit Function
Err:
    LoadFile = False
End Function

Private Function EraseData() As Boolean
    SendByte InsErase
    SendByte EraseChip
    SendLong 0
    
    EraseData = WaitReady(400)
End Function

Private Function WriteBlock(StartAddr As Long, Length As Long) As Boolean
    SendByte InsWriteBytes
    SendLong StartAddr
    SendLong Length
    
    Dim Buf() As Byte
    ReDim Buf(Length - 1)
    
    CopyMemory Buf(0), FileData(StartAddr), Length
    
    Comm.Output = Buf()
        
    WriteBlock = WaitReady(4)
End Function

Private Function WriteData() As Boolean
    WriteData = True
    
    Dim BlockSize As Long
    BlockSize = 1024
    Dim i As Long
    For i = 0 To UBound(FileData()) Step BlockSize
        Dim ActualSize As Long
        
        ActualSize = BlockSize
        If ActualSize > UBound(FileData()) + 1 - i Then
            ActualSize = UBound(FileData()) + 1 - i
        End If
        
        WriteData = WriteData And WriteBlock(i, ActualSize)
        
        If i Mod 100 = 0 Then
            ShpProgressInner.Width = ShpProgressOuter.Width * i / UBound(FileData())
            DoEvents
        End If
    Next i
End Function

Private Function CheckBlock(StartAddr As Long, Length As Long) As Boolean
    SendByte InsCheckBytes
    SendLong StartAddr
    SendLong Length
    
    Dim FlashCheckSum As Byte
    If ReceiveByte(FlashCheckSum, 1000) Then
        Dim CheckSum As Byte
        CheckSum = 0
        Dim i As Long
        
        For i = StartAddr To StartAddr + Length - 1
            CheckSum = CheckSum Xor FileData(i)
        Next i
        
        If CheckSum = FlashCheckSum Then
            CheckBlock = True
            Exit Function
        End If
    End If
    
    CheckBlock = False
End Function

Private Function VerifyData() As Boolean
    VerifyData = True
    
    Dim BlockSize As Long
    BlockSize = 1024
    Dim i As Long
    For i = 0 To UBound(FileData()) Step BlockSize
        Dim ActualSize As Long
        
        ActualSize = BlockSize
        If ActualSize > UBound(FileData()) + 1 - i Then
            ActualSize = UBound(FileData()) + 1 - i
        End If
        
        VerifyData = VerifyData And CheckBlock(i, ActualSize)
        If Not VerifyData Then
            Exit For
        End If
        
        If i Mod 100 = 0 Then
            ShpProgressInner.Width = ShpProgressOuter.Width * i / UBound(FileData())
            DoEvents
        End If
    Next i
End Function

Private Sub UpdateInfoArea()
    Dim FlashIndex As Byte
    Dim FlashExists As Boolean
    
    FlashIndex = 0
    FlashExists = True
    
    TxtInfo.Text = ""
    LstDevice.Clear
    
    Do While FlashExists
        EmptyInputBuffer
        SendByte InsReadInformationBlock
        SendByte FlashIndex
        Sleep 100
        DoEvents
        Dim B() As Byte
        B() = Comm.Input
        
        If UBound(B()) = 36 - 1 Then
            B(UBound(B()) - 4) = 0
            Dim FlashName As String
            FlashName = Space(40)
            lstrcpy FlashName, VarPtr(B(0))
            FlashName = Left(FlashName, InStr(1, FlashName, Chr(0)) - 1)
            
            Dim FlashSize As Long
            
            CopyMemory FlashSize, B(32), 4
            
            If FlashSize Then
                TxtInfo.Text = TxtInfo.Text & "Chip" & FlashIndex & ":" & FlashName & vbCrLf & "Size:0x" & Hex(FlashSize) & vbCrLf
                LstDevice.AddItem FlashIndex
            Else
                FlashExists = False
            End If
        Else
            FlashExists = False
        End If
        FlashIndex = FlashIndex + 1
    Loop
    
    On Error Resume Next
    LstDevice.Selected(0) = True
    On Error GoTo 0
End Sub

Private Sub CmdDownload_Click()
    CmdDownload.Enabled = False
    
    LabProgress.Caption = "Loading file."
    DoEvents
    If LoadFile(FileList.FileName) Then
        LabProgress.Caption = "Connecting."
        DoEvents
        If Connect(LstDevice.Text) Then
            LabProgress.Caption = "Erasing."
            DoEvents
            If EraseData() Then
                LabProgress.Caption = "Programming."
                DoEvents
                If WriteData() Then
                    LabProgress.Caption = "Verifing."
                    DoEvents
                    If VerifyData() Then
                        LabProgress.Caption = "Done."
                        MsgBox "完成", vbInformation
                    Else
                        MsgBox "校验出错", vbCritical
                    End If
                Else
                    MsgBox "写入失败", vbCritical
                End If
            Else
                MsgBox "擦除失败", vbCritical
            End If
            DisConnect
        Else
            MsgBox "链接失败", vbCritical
        End If
    Else
        MsgBox "文件载入失败", vbCritical
    End If
    CmdDownload.Enabled = True
End Sub

Private Sub CobPort_Click()
    CmdDownload.Enabled = False
    If Comm.PortOpen Then Comm.PortOpen = False
    Comm.CommPort = CobPort.ListIndex + 1
    On Error Resume Next
    Err.Clear
    Comm.PortOpen = True
    Select Case Err.Number
        Case 0
            On Error GoTo 0
            If Detect() Then
                ShpCommState.FillColor = vbGreen
                CmdDownload.Enabled = True
                UpdateInfoArea
            Else
                ShpCommState.FillColor = vbMagenta
                TxtInfo.Text = "No device detected."
            End If
        Case comPortAlreadyOpen
            ShpCommState.FillColor = vbYellow
            TxtInfo.Text = "The port is opened by orher program."
        Case Else
            ShpCommState.FillColor = vbRed
            TxtInfo.Text = "Error."
    End Select
    On Error GoTo 0
End Sub

Private Sub Form_Load()
    ShpProgressInner.Width = ShpProgressOuter.Width
    Dim i As Long
    For i = 1 To 10
        CobPort.AddItem "COM" & i
    Next i
    CobPort.ListIndex = 0
    Comm.InputMode = comInputModeBinary
End Sub

Private Sub Form_Unload(Cancel As Integer)
    End
End Sub
