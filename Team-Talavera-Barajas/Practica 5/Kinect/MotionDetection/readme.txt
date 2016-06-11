
Kinect Chapter 12. Motion Detection Using OpenCV
(based on NUI Chapter 3)

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

This directory contains 4 Java files:
  * MotionDetector.java, MotionPanel.java,
    JCVMotionDetector.java, KinectCapture.java          


There is 1 image file, used by the application:
  * crosshairs.png


There are 2 subdirectories:
  * JavaCV Examples\    -- holds three small JavaCV examples;
                           see the readme.txt in that directory
                           for details


There are 2 batch files:
  * compile.bat
  * run.bat
     - make sure they refer to the correct locations for your
       downloads of OpenNI, NITE, JavaCV, and OpenCV


----------------------------
Before Compilation/Execution:

You need to download and install:
    1.	OpenNI
    2.	SensorKinect driver
    3.	NITE

For details, read section 3 of Chapter 2, or installInfo.txt
in this directory.

You also need to download and install:

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
    // you must have OpenNI, the SensorKinect driver, and NITE installed;
    // you must have JavaCV and OpenCV installed

----------------------------
Execution:

> run MotionDetector
    // you must have OpenNI, the SensorKinect driver, and NITE installed;
    // you must have JavaCV and OpenCV installed;
    // OpenCV can take several seconds to start up


The application 'freezes' for a few seconds when the application's
close box is pressed, to wait for the Kinect link to be completely
shut down.

----------------------------
Last updated: 18th December 2011
