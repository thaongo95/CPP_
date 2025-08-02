#### Project 1: The "Inspector" Tool

*   **Goal:** Create a simple interactive tool that lets you explore an image.
*   **Concepts Mastered:** `cv::Mat` properties, `cv::Point`, `cv::Scalar`, basic window handling, and mouse callbacks. This project builds your foundational debugging skills.
*   **Steps:**
    1.  Load an image (`imread`). Perform the `empty()` check.
    2.  Create a window (`namedWindow`) and display the image (`imshow`).
    3.  **Set up a mouse callback function** (`setMouseCallback`). This is a new, crucial skill.
    4.  Inside the callback, get the `x, y` coordinates of the mouse (`cv::Point`).
    5.  When the mouse moves, get the BGR color value at that point using `image.at<cv::Vec3b>(y, x)`.
    6.  Draw a small circle at the mouse cursor.
    7.  Display the `(x, y)` coordinates and the `(B, G, R)` values on the image itself using `cv::putText()`. You'll use `cv::Point` for the text position and `cv::Scalar` for the color.

*   **Why it builds mastery:** You're forced to think about the coordinate system (`x, y` vs `row, col`), directly access pixel data, and combine drawing functions with real-time user input.

#### Project 2: The Real-Time Color Detector

*   **Goal:** Create a program that uses your webcam to find and highlight objects of a specific color.
*   **Concepts Mastered:** `cv::VideoCapture`, HSV color space, `cv::inRange`, and basic contour analysis (`findContours`, `boundingRect`).
*   **Steps:**
    1.  Open your webcam using `cv::VideoCapture(0)`.
    2.  In a loop, read each `frame` from the camera.
    3.  Convert the BGR `frame` to the HSV color space (`cvtColor`).
    4.  Use `cv::inRange()` to create a binary mask that isolates a color (e.g., a bright green or blue object). **Crucially, create trackbars to let you adjust the Hue, Saturation, and Value ranges in real-time.** This is the best way to understand HSV.
    5.  Find the contours of the objects in the mask using `cv::findContours`. You'll get a `std::vector<std::vector<cv::Point>>`.
    6.  Loop through the found contours. Ignore very small ones (noise).
    7.  For each valid contour, calculate its bounding box using `cv::boundingRect()`. This returns a `cv::Rect`.
    8.  Draw this `cv::Rect` on the *original color frame* to show what you've detected.
    9.  Display the original frame and the binary mask in separate windows.

*   **Why it builds mastery:** You're now working with a live video stream, solidifying your `VideoCapture` skills. You gain an intuitive feel for the powerful HSV color space and see the direct pipeline from thresholding -> contours -> bounding boxes.

#### Project 3: The Document Scanner

*   **Goal:** Take a photo of a document on a contrasting background and automatically find its four corners.
*   **Concepts Mastered:** Edge detection (`Canny`), advanced contour analysis (`arcLength`, `approxPolyDP`), and sorting `std::vector`s.
*   **Steps:**
    1.  Load a static image of a document.
    2.  Pre-process it: convert to grayscale (`cvtColor`), blur it (`GaussianBlur`), and find the edges (`Canny`).
    3.  Find all contours (`findContours`).
    4.  Loop through the contours. Find the one with the largest area (`contourArea`), as this is likely your document.
    5.  Take this largest contour and approximate its shape using `cv::approxPolyDP`. This function simplifies a curve into a polygon with fewer vertices.
    6.  Check if your resulting polygon has **exactly 4 vertices** (`std::vector<cv::Point>`). If it does, you've found your document!
    7.  Draw circles on the original image at these four detected corner points.

*   **Why it builds mastery:** This project forces you to go beyond simple bounding boxes and analyze the *shape* of a contour. You learn to filter and select contours based on properties like area and shape complexity.

#### Project 4: The Lane Line Detector

*   **Goal:** Process a video of a road and highlight the lane lines.
*   **Concepts Mastered:** Region of Interest (ROI) with `cv::Rect`, Hough Line Transform (`HoughLinesP`), and combining multiple drawing results.
*   **Steps:**
    1.  Load a video file of a car driving on a road (`VideoCapture`).
    2.  For each frame:
    3.  Apply Canny edge detection.
    4.  **Define a Region of Interest.** The lane lines will only be in a specific trapezoidal area at the bottom of the frame. Create a black mask of the same size as the frame, draw a white-filled polygon on it, and use `cv::bitwise_and` to "cut out" only the edges within that region. This is a critical optimization step.
    5.  Run the Hough Line Transform (`HoughLinesP`) on this masked edge image. It will return a `std::vector<cv::Vec4i>`.
    6.  Loop through the detected lines and draw them on a blank `cv::Mat` of the same size as the frame.
    7.  Use `cv::addWeighted()` to overlay this line image onto the original frame with some transparency.
    8.  Display the result.

*   **Why it builds mastery:** You learn how to focus your algorithm on a specific part of the image (ROI), a vital skill for efficiency and accuracy. You master the Hough Transform for finding specific shapes and learn how to composite multiple images together.

#### Project 5: The Face and Eye Detector

*   **Goal:** Use the webcam to detect faces and then, *within each detected face*, detect eyes.
*   **Concepts Mastered:** `cv::CascadeClassifier`, nesting ROIs, and robust error checking.
*   **Steps:**
    1.  Initialize two `cv::CascadeClassifier` objects. Load one with `haarcascade_frontalface_default.xml` and the other with `haarcascade_eye.xml`.
    2.  In your `VideoCapture` loop:
    3.  Convert the frame to grayscale.
    4.  Use the face classifier's `detectMultiScale` method on the whole grayscale frame. It returns a `std::vector<cv::Rect>` of faces.
    5.  **Loop through the `faces` vector.**
    6.  For each `face_rect` found:
        a. Draw a rectangle for the face on the original color frame.
        b. **Create an ROI from the grayscale image using the `face_rect`.** This `cv::Mat face_roi = gray_image(face_rect);` is a crucial line.
        c. Run the eye classifier's `detectMultiScale` on this **small `face_roi`**, not the whole image. This is much faster and more accurate.
        d. It will return a `std::vector<cv::Rect>` of eyes *relative to the ROI*.
        e. Loop through the `eyes` vector. To draw them correctly, you must add the ROI's top-left corner coordinates to the eye rectangle's coordinates.
        f. Draw the eye rectangles on the original color frame.

*   **Why it builds mastery:** This teaches the powerful concept of hierarchical detection. You solidify your understanding of ROIs and coordinate systems. It demonstrates how to break a big problem (finding eyes) into a smaller, more manageable one (first find a face, *then* find eyes inside it).
