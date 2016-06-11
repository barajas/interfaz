@echo off
echo Compiling %* with JavaCV and OpenCV...

javac -cp "c:\javacv-bin\javacv.jar;c:\javacv-bin\javacpp.jar;c:\javacv-bin\javacv-windows-x86.jar;." %*

echo Finished.
