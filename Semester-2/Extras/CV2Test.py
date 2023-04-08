import cv2
#import time

#cap = cv2.VideoCapture("/home/newbie/Videos/Entertainment/Movies/Hindi/A.mkv");
cap = cv2.VideoCapture(0);
#print("cap", cap)

count = 1
while True:
    ret, frame = cap.read()
    #print(ret, frame)
    #print(format(count) + "\n")
    count = count + 1
    frame = cv2.resize(frame, (120, 180))
    cv2.imshow("frame", frame)
    k = cv2.waitKey(25)
    if k & 0xFF == ord("q"):
        break
    #time.sleep(5)
cap.release()
cv2.destroyAllWindows()
