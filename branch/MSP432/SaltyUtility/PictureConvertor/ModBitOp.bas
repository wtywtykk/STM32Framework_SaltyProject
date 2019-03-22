Attribute VB_Name = "ModBitOp"
Option Explicit

Public Declare Function SHL8 Lib "BitOp.dll" (ByVal Val As Byte, ByVal Shift As Long) As Byte
Public Declare Function SHR8 Lib "BitOp.dll" (ByVal Val As Byte, ByVal Shift As Long) As Byte

Public Declare Function SHL16 Lib "BitOp.dll" (ByVal Val As Integer, ByVal Shift As Long) As Integer
Public Declare Function SHR16 Lib "BitOp.dll" (ByVal Val As Integer, ByVal Shift As Long) As Integer

Public Declare Function SHL32 Lib "BitOp.dll" (ByVal Val As Long, ByVal Shift As Long) As Long
Public Declare Function SHR32 Lib "BitOp.dll" (ByVal Val As Long, ByVal Shift As Long) As Long


Public Declare Function GetU16U8 Lib "BitOp.dll" (ByVal Val As Integer, ByVal Index As Long) As Byte
Public Declare Function SetU16U8 Lib "BitOp.dll" (ByVal Val16 As Integer, ByVal Val8 As Byte, ByVal Index As Long) As Integer
Public Declare Function GetU32U8 Lib "BitOp.dll" (ByVal Val As Long, ByVal Index As Long) As Byte
Public Declare Function SetU32U8 Lib "BitOp.dll" (ByVal Val32 As Long, ByVal Val8 As Byte, ByVal Index As Long) As Long
Public Declare Function GetU32U16 Lib "BitOp.dll" (ByVal Val As Long, ByVal Index As Long) As Integer
Public Declare Function SetU32U16 Lib "BitOp.dll" (ByVal Val32 As Long, ByVal Val16 As Integer, ByVal Index As Long) As Long

Public Declare Function SwitchU16Edition Lib "BitOp.dll" (ByVal Val As Integer) As Integer
Public Declare Function SwitchU32Edition Lib "BitOp.dll" (ByVal Val As Long) As Long

Public Declare Function CheckU8Bit Lib "BitOp.dll" (ByVal Val As Byte, ByVal Index As Long) As Boolean
Public Declare Function CheckU16Bit Lib "BitOp.dll" (ByVal Val As Integer, ByVal Index As Long) As Boolean
Public Declare Function CheckU32Bit Lib "BitOp.dll" (ByVal Val As Long, ByVal Index As Long) As Boolean

Public Declare Function U8Add Lib "BitOp.dll" (ByVal Val1 As Byte, ByVal Val2 As Byte) As Byte
Public Declare Function U8Sub Lib "BitOp.dll" (ByVal Val1 As Byte, ByVal Val2 As Byte) As Byte
Public Declare Function U8Cmp Lib "BitOp.dll" (ByVal Val1 As Byte, ByVal Val2 As Byte) As Long
Public Declare Function U16Add Lib "BitOp.dll" (ByVal Val1 As Integer, ByVal Val2 As Integer) As Integer
Public Declare Function U16Sub Lib "BitOp.dll" (ByVal Val1 As Integer, ByVal Val2 As Integer) As Integer
Public Declare Function U16Cmp Lib "BitOp.dll" (ByVal Val1 As Integer, ByVal Val2 As Integer) As Long
Public Declare Function U32Add Lib "BitOp.dll" (ByVal Val1 As Long, ByVal Val2 As Long) As Long
Public Declare Function U32Sub Lib "BitOp.dll" (ByVal Val1 As Long, ByVal Val2 As Long) As Long
Public Declare Function U32Cmp Lib "BitOp.dll" (ByVal Val1 As Long, ByVal Val2 As Long) As Long

Public Function GetRGB(ByVal Color As Long) As Byte()
    Dim Result(3) As Byte
    
    Result(0) = GetU32U8(Color, 0) 'R
    Result(1) = GetU32U8(Color, 1) 'G
    Result(2) = GetU32U8(Color, 2) 'B
    Result(3) = GetU32U8(Color, 3) 'A
    
    GetRGB = Result()
End Function


