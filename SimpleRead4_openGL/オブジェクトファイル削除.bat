copy .\bin\Debug\*.exe .\
rmdir  /s obj
rmdir  /s bin
exit

rem �ȉ�MSVC�p
rmdir  /s ipch
rmdir  /s Debug
del x64\Debug\*.tlog
del x64\Debug\*.obj
del *.sdf
del *.opensdf
del *.vcxproj.user
del *.ilk
del *.pdb
del *.suo
