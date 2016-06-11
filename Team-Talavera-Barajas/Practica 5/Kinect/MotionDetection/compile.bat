@echo off
echo Compiling %* with OpenNI, JavaCV, JavaCPP...

javac -cp "C:\Program Files\OpenNI\Bin\org.OpenNI.jar;c:\javacv-bin\javacv.jar;c:\javacv-bin\javacpp.jar;c:\javacv-bin\javacv-windows-x86.jar;." %*

echo Finished.
