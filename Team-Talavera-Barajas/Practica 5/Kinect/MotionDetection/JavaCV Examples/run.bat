@echo off
echo Executing %* with JavaCV and OpenCV...

java -cp "c:\javacv-bin\javacv.jar;c:\javacv-bin\javacpp.jar;c:\javacv-bin\javacv-windows-x86.jar;." -Djava.library.path="C:\OpenCV2.2\bin;C:\WINDOWS\System32;." %*

echo Finished.
