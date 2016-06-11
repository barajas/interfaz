
// ShowImage.java
// Andrew Davison, March 2011, ad@fivedots.coe.psu.ac.th

/* Use JavaCV to load and display an image.
*/


import com.googlecode.javacv.*;

import static com.googlecode.javacv.cpp.opencv_core.*;
import static com.googlecode.javacv.cpp.opencv_highgui.*;


public class ShowImage  
{

  public static void main(String[] args)
  {
    if (args.length != 1) {
      System.out.println("Usage: run ShowImage <input-file>");
      return;
    }

    System.out.println("OpenCV: Loading image from " + args[0] + "...");
    IplImage img = cvLoadImage(args[0]);
    System.out.println("Size of image: (" + img.width() + ", " + img.height() + ")");

    // display image in canvas
    CanvasFrame canvas = new CanvasFrame(args[0]);
    // canvas.setDefaultCloseOperation(CanvasFrame.EXIT_ON_CLOSE);   
    canvas.setDefaultCloseOperation(CanvasFrame.DO_NOTHING_ON_CLOSE);   

    canvas.showImage(img);

	  canvas.waitKey();   // wait for keypress on canvas
    canvas.dispose();
  }  // end of main()

}  // end of ShowImage class