#https://naman5.wordpress.com/2014/06/24/experimenting-with-kinect-using-opencv-python-and-open-kinect-libfreenect/
#import the necessary modules
import freenect
import cv2
import numpy as np
import datetime
#import imutils
import time
from email.mime.text import MIMEText
import logging
import smtplib

from config import MAIL_TEMPLATE, MAIL_FROM, MAIL_TO
from config import SMTP_SERVER, SMTP_PORT, SMTP_USER, SMTP_PASSWORD, SMTP_TLS

def send_alert(subject):
    logging.info("Sending mail alert (%s)" % subject)

    body = MAIL_TEMPLATE % subject
    msg = MIMEText(body)
    msg['Subject'] = 'Security alert: %s' % subject
    msg['From'] = MAIL_FROM
    msg['To'] = MAIL_TO

    smtp = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)

    if SMTP_TLS:
        smtp.starttls()

    if SMTP_USER is not None and SMTP_PASSWORD is not None:
        smtp.login(SMTP_USER, SMTP_PASSWORD)

    smtp.sendmail(MAIL_FROM, [MAIL_TO], msg.as_string())
    smtp.quit()
 
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
    # resize the frame, convert it to grayscale, and blur it
    # initialize the first frame in the video stream
    firstFrame = None
    min_area = 500
    while 1:
        #get a frame from RGB camera
        frame = get_video()
        text = "Unoccupied"
        #get a frame from depth sensor
        #depth = get_depth()

        #display RGB image
        #cv2.imshow('RGB image',frame)
        #display depth image
        #cv2.imshow('Depth image',depth)

	#move detector


        #frame = imutils.resize(frame, width=500)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray, (21, 21), 0)
        
        # if the first frame is None, initialize it
	if firstFrame is None:
            firstFrame = gray
            continue
        
        # compute the absolute difference between the current frame and
	# first frame
	frameDelta = cv2.absdiff(firstFrame, gray)
	thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]
 
	# dilate the thresholded image to fill in holes, then find contours
	# on thresholded image
	thresh = cv2.dilate(thresh, None, iterations=2)
	(cnts, _) = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
 
	# loop over the contours
	for c in cnts:
		# if the contour is too small, ignore it
		if cv2.contourArea(c) < min_area:
			continue
 
		# compute the bounding box for the contour, draw it on the frame,
		# and update the text
		(x, y, w, h) = cv2.boundingRect(c)
		cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
		text = "Occupied"
       
       # draw the text and timestamp on the frame
	cv2.putText(frame, "Room Status: {}".format(text), (10, 20),
		cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
	cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"),
		(10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)
 
	# show the frame and record if the user presses a key
	cv2.imshow("Security Feed", frame)
	#cv2.imshow("Thresh", thresh)
	#cv2.imshow("Frame Delta", frameDelta)        
        

        # quit program when 'esc' key is pressed
        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break
    cv2.destroyAllWindows()
