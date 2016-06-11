@echo off
echo Executing %* with OpenNI, JavaCV, JavaCPP and OpenCV...

java -cp "C:\Program Files\OpenNI\Bin\org.OpenNI.jar;c:\javacv-bin\javacv.jar;c:\javacv-bin\javacpp.jar;c:\javacv-bin\javacv-windows-x86.jar;." -Djava.library.path="C:\Program Files\OpenNI\Bin;C:\OpenCV2.2\bin;C:\WINDOWS\System32;." %*

echo Finished.
