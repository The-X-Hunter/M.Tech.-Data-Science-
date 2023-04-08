import cv2
import time

#Reading image
image = cv2.imread('Input.png')
#Showing image
cv2.imshow('image', image)
#Waiting for a key press, wait time here is 1 second
cv2.waitKey(1)
#Show picture for 3 seconds
time.sleep(3)
#Closing already opened window
cv2.destroyAllWindows()
#Writing on new image file. in short, creating duplicate of an image here
cv2.imwrite('Output.png', image)
#Writing text on input image file
#Here first parameter is image file
#Second parameter is text to be written, in this case it is my name
#Third parameter is position of text on the image
#Fourth parameter is font in which text should be written
#Fifth parameter is fontscale
#Sixth parameter is colour of text
#Seventh parameter is thickness of text
image = cv2.putText(image, 'Julfikaraehmad', (500, 500), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 2)
cv2.imshow('image', image)
cv2.waitKey(1)
time.sleep(3)
cv2.destroyAllWindows()
