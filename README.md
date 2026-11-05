# cloud-chamber
Program for detecting types of particles in a cloud chamber

## Todo's
### 1. Prediction for 1 image
#### Converting to pixels
- Make a Pixel struct containing a color value / greyscale value, depending on if we need to keep the original color do only one value
- Function that greyscales a Pixel
- Make a Config struct where we can put all cfg like resolution, and later for videos fps and so on
- Function that converts the image to a vector of Pixels where the position of the Pixel in the grid is given by (i % w, i / w), also code this position into a conversion function in this struct
- Function that greyscales all Pixels in that vector

#### Detecting clusters
- Particles will be clusters of white, we need a way to detect what is a particle and what is not: idk yet, maybe hierachical clustering would work, this would act on all Pixels
- Use K-means clustering to group all clusters into a group that represents which particle it is, this would act on the different clusters made in the step before
- Output useful clusters, what particle it is and what the position of the for example the centre of mass is so that we can find it
- Make some kind of thing that puts the prediction on the actual image instead of outputting it to terminal

#### Calibration
- Look into Principal component analysis for this
- Write a function that lowers the resolution of our image
- Write a function that can find the optimum of resolution, not too low and not too high to preserve memory
- Write a function that calibrates our vector of pixels by looking for a signal (like a bright colored obvious spot in the image) so that we only take the inside of the cloud chamber into our grid by throwing out the outside pixels

### 2. Prediction for a folder of images
Goal here is to convert the folder into a prediction for each image using the output function from before, either making copies of the images with indicated spots or changing the images directly. Use the functions that we made before for images

- Make a function that loops over every image in the folder and predicts the particles for that image.
- Write something so that the calibration happens once, the positions of the bright colored spots will remain roughly the same accross images so instead of recalibrating everytime (which i think will be an expensive operation because we have to search through a vector) so we can reuse the found position for the spots and cut down every vector the same
- Also do this for the resolution, find the optimum once and use the same thing always
- Also need to find a way to get this folder of images, either by taking a lot of photos or making a video and already going to the next part.

### 3. Prediction for videos
- Convert the video to a folder of images and use the other function
- Find an optimum for the fps at which we dont lose information but use the least memory

### 4. Prediction for live
- Get a live feed in some sort of way and convert it to small videos or images (what is most efficient), using the optimum for fps at which the device the code is run on can handle for getting predictions live without getting too much behind the actual live feed
- Make something that can display the live feed

