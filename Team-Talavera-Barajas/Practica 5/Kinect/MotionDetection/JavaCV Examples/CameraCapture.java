
// CameraCapture.java
// Andrew Davison, March 2011, ad@fivedots.coe.psu.ac.th

/* Use JavaCV to grab images from the local webcam and display them.
*/

import java.io.*;
import java.awt.event.*;

import com.googlecode.javacv.*;

import static com.googlecode.javacv.cpp.opencv_core.*;
import static com.googlecode.javacv.cpp.opencv_highgui.*;



public class CameraCapture  
{
  private static volatile boolean isRunning = true;


  public static void main(String[] args)
  {
    System.out.println("Starting OpenCV...");
    try {
      CanvasFrame canvas = new CanvasFrame("Camera Capture");
      canvas.addWindowListener( new WindowAdapter() {
        public void windowClosing(WindowEvent e) 
        { isRunning = false; }
      });

      System.out.println("Starting frame grabber...");
      OpenCVFrameGrabber grabber = new OpenCVFrameGrabber(CV_CAP_ANY);
      grabber.start();

      IplImage frame;
      while(isRunning) {
        if ((frame = grabber.grab()) == null)
          break;
        canvas.showImage(frame);
      }
	    grabber.stop();
      canvas.dispose();
    }
    catch(Exception e) 
    {  System.out.println(e);  }
  }  // end of main()

} // end of CameraCapture class