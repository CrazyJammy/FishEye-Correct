echo off
title Dependency Walker �Ҽ��˵�����

:���˵�
color 1B
cls
echo.*-----------------------------------------------------------------------------*
echo * *************************** ��װ/ж���Ҽ��˵� *******************************
echo.*-----------------------------------------------------------------------------*
echo.*    ������������������                                                       *
echo.*         (1) ��װ�Ҽ��˵�                                                    *
echo.*    ������������������                                                       *
echo.*         (2) ж���Ҽ��˵�                                                    *
echo.*    ������������������                                                       *
echo.*-----------------------------------------------------------------------------*
echo.* (A)��װ  (U)ж��                                                   (X)�˳�  *
echo.*-----------------------------------------------------------------------------*
echo.*     ���ڹ���Ա������...........               by Webenvoy (www.newasp.net)  *
echo *******************************************************************************
SET /P runcd=   �����루���е����ּ������س� :
if /I "%runcd%"=="1" goto Installation
if /I "%runcd%"=="2" goto Uninstallation
if /I "%runcd%"=="A" goto Installation
if /I "%runcd%"=="U" goto Uninstallation
if /I "%runcd%"=="X" goto EX
goto ���˵�

:EX
exit

:Installation
cls
color 1B
REG ADD "HKCR\dllfile\shell\Open with Dependency Walker" /v "" /t REG_SZ /d "�� Dependency Walker ��" /f
REG ADD "HKCR\dllfile\shell\Open with Dependency Walker" /v "Icon" /t REG_SZ /d "%cd%\depends.exe" /f
REG ADD "HKCR\dllfile\shell\Open with Dependency Walker\command" /v "" /t REG_SZ /d "%cd%\depends.exe \"%%1\"" /f

REG ADD "HKCR\exefile\shell\Open with Dependency Walker" /v "" /t REG_SZ /d "�� Dependency Walker ��" /f
REG ADD "HKCR\exefile\shell\Open with Dependency Walker" /v "Icon" /t REG_SZ /d "%cd%\depends.exe" /f
REG ADD "HKCR\exefile\shell\Open with Dependency Walker\command" /v "" /t REG_SZ /d "%cd%\depends.exe \"%%1\"" /f

echo ***************************************************************************
echo.
echo     �Ҽ��˵���װ���......
echo.
echo ***************************************************************************
pause
exit

:Uninstallation
cls
color 1B
REG DELETE "HKCR\dllfile\shell\Open with Dependency Walker" /f
REG DELETE "HKCR\exefile\shell\Open with Dependency Walker" /f
echo ***************************************************************************
echo.
echo     �Ҽ��˵�ж�����......
echo.
echo ***************************************************************************
pause
exit
