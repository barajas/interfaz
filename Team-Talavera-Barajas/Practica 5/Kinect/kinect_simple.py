#import the necessary modules
import freenect
import cv2
import numpy as np
import datetime
#import imutils
import time
 
#function to get RGB image from kinect
def get_video():
    array,_ = freenect.sync_get_video()
    array = cv2.cvtColor(array,cv2.COLOR_RGB2BGR)
    return array
 
#function to get depth image from kinect
def get_depth():
    array,_ = freenect.sync_get_depth()
    array = array.astype(np.uint8)
    return array
 
if __name__ == "__main__":
    	# initialize the first frame in the video stream
    irstFrame = None
    min_area = 500
    while 1:
        #get a frame from RGB camera
        frame = get_video()
        text = "Unoccupied"
        #get a frame from depth sensor
        #depth = get_depth()

        #move detector
        # resize the frame, convert it to grayscale, and blur it


        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (21, 21), 0)
	
	# if the first frame is None, initialize it
	if firstFrame is None:
            firstFrame = gray
            continue

        #display RGB image
        cv2.imshow('RGB image',frame)

        # quit program when 'esc' key is pressed
        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break
    cv2.destroyAllWindows()
