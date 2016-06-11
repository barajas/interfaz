
// MotionPanel.java
// Andrew Davison, December 2011, ad@fivedots.psu.ac.th

/* This panel repeatedly uses KinectCapture to snap a picture and draw it onto
   the panel. OpenCV is used, via the JCVMotionDetector class, to detect
   movement.

   A crosshairs graphic is drawn onto the image, positioned at the
   center-of-gravity (COG) of the motion.

   Changes from the version in NUI CHapter 3:
      * all ocurrences of JMFCapture have been changed to KinectCapture
*/

import java.awt.*;
import javax.swing.*;
import java.awt.image.*;
import java.text.DecimalFormat;
import java.io.*;
import javax.imageio.*;
import java.util.*;


public class MotionPanel extends JPanel implements Runnable
{
  private static final Dimension PANEL_SIZE = new Dimension(200, 50);  
          // dimensions of panel initially;  later set to video's frame size

  private static final int DELAY = 100;  // time (ms) between redraws of the panel
      // needs about 45 ms for motion detection

  private static final String CROSSHAIRS_FNM = "crosshairs.png";
  // circle and cross-hairs dimensions (only used if crosshairs image cannot be loaded)
  private static final int CIRCLE_SIZE = 40;  
  private static final int LINES_LEN = 60;  

  private static final int MIN_MOVE_REPORT = 3;    // for reporting a move


  private JFrame top;
  private BufferedImage image = null;  // current webcam snap
  private KinectCapture camera; 
  private volatile boolean isRunning;
  
  // used for the average ms snap time information
  private int imageCount = 0;
  private long totalTime = 0;
  private DecimalFormat df;
  private Font msgFont;

  private Point prevCogPoint = null; // holds the coordinates of the motion COG
  private Point cogPoint = null; 
  private BufferedImage crosshairs;



  public MotionPanel(JFrame top)
  {
    this.top = top;
    setBackground(Color.white);
    setPreferredSize(PANEL_SIZE);

    df = new DecimalFormat("0.#");  // 1 dp
    msgFont = new Font("SansSerif", Font.BOLD, 18);

    // load the crosshairs image (a transparent PNG)
    crosshairs = null;
    try {
      crosshairs = ImageIO.read(new File(CROSSHAIRS_FNM));
    } 
    catch (IOException e) 
    {  System.out.println("Could not find " + CROSSHAIRS_FNM);  }

    new Thread(this).start();   // start updating the panel's image
  } // end of MotionPanel()




  public void run()
  /* display the current webcam image every DELAY ms
     The time statistics gathered here include the time taken to
     detect movement.
  */
  {
    camera = new KinectCapture();  // Resolution.HIGH

    BufferedImage im = camera.getImage();
    JCVMotionDetector md = new JCVMotionDetector(im);  
         // create motion detector (uses OpenCV so can be slow to start)

    // update panel and window sizes to fit video's frame size
    Dimension frameSize = camera.getFrameSize();
    if (frameSize != null) {
      setPreferredSize(frameSize);
      top.pack();   // resize and center JFrame
      top.setLocationRelativeTo(null);
    }

    Point pt;
    long duration;
    isRunning = true;
    while (isRunning) {
	    long startTime = System.currentTimeMillis();
      im = camera.getImage();  // take a snap
      if (im == null) {
        System.out.println("Problem loading image " + (imageCount+1));
        duration = System.currentTimeMillis() - startTime;
      }
      else {
        md.calcMove(im);    // update detector with new image
        if ((pt = md.getCOG()) != null) {    // get new COG
          prevCogPoint = cogPoint; 
          cogPoint = pt;
          reportCOGChanges(cogPoint, prevCogPoint);
        }

        image = im;   // only update image if im contains something
        imageCount++;
        duration = System.currentTimeMillis() - startTime;
        totalTime += duration;
        repaint();
      }

      if (duration < DELAY) {
        try {
          Thread.sleep(DELAY-duration);  // wait until DELAY time has passed
        } 
        catch (Exception ex) {}
      }
    }
    camera.close();    // close down the camera
  }  // end of run()


  private void reportCOGChanges(Point cogPoint, Point prevCogPoint)
  // compare cogPoint and prevCogPoint
  {
    // System.out.println("COG: (" + cogPoint.x + ", " + cogPoint.y + ")");

    if (prevCogPoint == null)
      return;

    // calculate the distance moved and the angle (in degrees)
    int xStep = cogPoint.x - prevCogPoint.x;    
    int yStep = -1 *(cogPoint.y - prevCogPoint.y);      // so + y-axis is up screen

    int distMoved = (int) Math.round( Math.sqrt( (xStep*xStep) + (yStep*yStep)) );
    int angle = (int) Math.round( Math.toDegrees( Math.atan2(yStep, xStep)) );

    if (distMoved > MIN_MOVE_REPORT) {
      System.out.println("COG: (" + cogPoint.x + ", " + cogPoint.y + ")");
      System.out.println("  Dist moved: " + distMoved + "; angle: " + angle);
    }
  }  // end of reportCOGChanges()



  public void paintComponent(Graphics g)
  /* Draw the image, the movement crosshairs, and the 
     average ms snap time at the bottom left of the panel. 
  */
  { 
    super.paintComponent(g);
    Graphics2D g2 = (Graphics2D) g;

    if (image != null)
      g2.drawImage(image, 0, 0, this);

    if (cogPoint != null)
      drawCrosshairs(g2, cogPoint.x, cogPoint.y);   // positioned at COG

    writeStats(g2);
  } // end of paintComponent()




  private void drawCrosshairs(Graphics2D g2, int xCenter, int yCenter)
  // draw crosshairs graphic or make one from lines and a circle
  {
    if (crosshairs != null)
      g2.drawImage(crosshairs, xCenter - crosshairs.getWidth()/2, 
                               yCenter - crosshairs.getHeight()/2, this);
    else {    
      // draw thick red circle and cross-hairs in center
      g2.setColor(Color.RED);
      g2.drawOval(xCenter - CIRCLE_SIZE/2, yCenter - CIRCLE_SIZE/2, 
                                              CIRCLE_SIZE, CIRCLE_SIZE);
      g2.drawLine(xCenter, yCenter - LINES_LEN/2,
                  xCenter, yCenter + LINES_LEN/2);    // vertical line
      g2.drawLine(xCenter - LINES_LEN/2, yCenter,
                  xCenter + LINES_LEN/2, yCenter);    // horizontal line
    }
  }  // end of drawCrosshairs()




  private void writeStats(Graphics2D g2)
  /* write statistics in bottom-left corner, or
     "Loading" at start time */
  {
	  g2.setColor(Color.BLUE);
    g2.setFont(msgFont);
    int panelHeight = getHeight();
    if (imageCount > 0) {
      double avgGrabTime = (double) totalTime / imageCount;
	    g2.drawString("Pic " + imageCount + "  " +
                   df.format(avgGrabTime) + " ms", 
                   5, panelHeight-10);  // bottom left
    }
    else  // no image yet
	    g2.drawString("Loading...", 5, panelHeight-10);
  }  // end of writeStats()



  public void closeDown()
  /* Terminate run() and wait for the camera to be closed.
     This stops the application from exiting until everything
     has finished. */
  { 
    isRunning = false;
    while (!camera.isClosed()) {
      try {
        Thread.sleep(DELAY);
      } 
      catch (Exception ex) {}
    }
  } // end of closeDown()


} // end of MotionPanel class

