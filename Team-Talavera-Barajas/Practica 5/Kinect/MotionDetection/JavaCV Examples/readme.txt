
Kinect Chapter 12. Motion Detection Using OpenCV: JavaCV Examples

Unchanged from
NUI Chapter 3. Motion Detection: JavaCV Examples

From the website:

  Kinect Open Source Programming Secrets
  http://fivedots.coe.psu.ac.th/~ad/kinect/

  Dr. Andrew Davison
  Dept. of Computer Engineering
  Prince of Songkla University
  Hat yai, Songkhla 90112, Thailand
  E-mail: ad@fivedots.coe.psu.ac.th


If you use this code, please mention my name, and include a link
to the website.

Thanks,
  Andrew

============================

This directory contains 3 Java examples:
  * ShowImage.java
  * CameraCapture.java
  * CVMotionDetector.java

There is 1 JPG files:
  * airplane.jpg

There are 2 batch files:
  * compile.bat
  * run.bat
     - make sure they refer to the correct locations for your
       downloads of JavaCV and OpenCV


----------------------------
Before Compilation/Execution:

You need to download and install:

   * OpenCV: http://opencv.willowgarage.com/
             I downloaded v2.2 for Windows with pre-compiled binaries:
                OpenCV-2.2.0-win32-vs2010.exe
             and installed it in C:\OpenCV2.2

   * JavaCV: http://code.google.com/p/javacv/
             I downloaded javacv-bin-20110219.zip 
                      and javacv-src-20110219.zip
              --> I unzipped the 'bin' file and installed it in C:\javacv-bin
              --> I unzipped the 'src' file so I could search the source code
                  and generate Java docs

        * note: if you use a more recent version of JavaCV, it may require
                a more recent version of OpenCV

----------------------------
Compilation:

> compile *.java
    // you must have JavaCV and OpenCV installed

----------------------------
Execution:
    // you must have JavaCV and OpenCV installed for all these examples to work
    // OpenCV can take several seconds to start up

> run ShowImage <image file>
e.g.
> run ShowImage airplane.jpg
      -- press a key inside the window to make the application exit


> run CameraCapture
      -- click on the window's close box to make the application exit


> run CVMotionDetector
      -- click on either of the 2 window's close box to make the application exit

----------------------------
Last updated: 14th May 2011
