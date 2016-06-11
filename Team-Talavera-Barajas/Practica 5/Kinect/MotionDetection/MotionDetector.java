
// MotionDetector.java
// Andrew Davison, May 2011, ad@fivedots.psu.ac.th

/* Show a sequence of images snapped from the Kinect in a picture panel (MotionPanel). 
   Any change between the current frame and the previous is detected using OpenCV and
   crosshairs are drawn at the center-of-gravity (COG) of the difference.

   Usage:
      > java MotionDetector

   Unchanged from the version in NUI Chapter 3
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.*;


public class MotionDetector extends JFrame 
{
  // GUI components
  private MotionPanel motionPanel;


  public MotionDetector()
  {
    super("Motion Detector");

    Container c = getContentPane();
    c.setLayout( new BorderLayout() );   

    motionPanel = new MotionPanel(this); // the sequence of pictures appear here
    c.add( motionPanel, BorderLayout.CENTER);

    addWindowListener( new WindowAdapter() {
      public void windowClosing(WindowEvent e)
      { motionPanel.closeDown();    // stop snapping pics
        System.exit(0);
      }
    });

    pack();  
    setResizable(false);
    setVisible(true);
  } // end of MotionDetector()


  // -------------------------------------------------------

  public static void main( String args[] )
  {  new MotionDetector();  }

} // end of MotionDetector class
