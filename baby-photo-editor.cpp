// FCAI – Structured Programming – 2024 - Assignment 3 - part 2B

// Program Name: CS112_A3_part2B_S3_20230451_S3_20230452_S4_20231166.cpp

// Program Description: This Baby Photo Editor Program contains 14 filters:

// The first filter is the Grayscale conversion filter,it transforms
// an image into shades of grays,removing colour information.

// The second one is Black and White filter, it is similar to gray scale conversion filter,
// but typically emphasizes the contrast between light and dark areas more strongly.

// The third filter is the Invert image filter, it reverses the colours of the image,
// so that the areas that were originally dark becomes light and vice versa.

// The fourth filter is the Merge filter, it is an image processing technique used to combine two
// images into a single composite image.

// The fifth filter is the Flip image filter, it may be horizontally or vertically,
// it mirrors the image along either the horizontal so that the left side of the image
// becomes the right one, it may flip the image along the vertical axis,
// so that the top of the image becomes the bottom.

// The sixth filter is the Rotate image filter, it is an image processing technique used to rotate
// an image by a specified angle. It determines the direction and degree of rotation applied to the image.

// The seventh one is Darken and Lighten image filter,This filter darkens the image,
// by reducing the brightness of pixels by 50%. Conversely, also the lighten filter increases
// the brightness of an image by amplifying the brightness of pixels 50%.

// The eighth filter is the Crop image, it is an image processing technique used to remove unwanted parts of an image
// by selecting and retaining only a specific region of interest.

// The ninth filter is Adding frame to the picture, it is a process of enhancing the visual presentation of an image by
// surrounding it with a decorative or functional border.

// The tenth filter is the Detect image edge filter, which is essential in image processing as it focuses on
// recognizing boundaries in an image and emphasizing them.

// The eleventh filter is the Resize filter,it is a common image processing technique used to change the dimensions of
// an image whether by entering new dimensions (width and height) or entering the ratio of reduction or increase.

// The twelfth filter is Sunlight filter,it is used to simulate the effect of sunlight on an image. It typically involves
// enhancing brightness, increasing contrast, and adding warm tones to create a sunny or glowing appearance.

// The thirteenth filter is Purple filter,it adds a purple tint to an image, adjusts the color balance of the image to emphasize
// purple hues, resulting in a cooler and more atmospheric appearance.

// The fourteenth filter is Infrared filter, it  simulates the appearance of images captured using infrared-sensitive cameras
// or film, it modifies the color composition of the image to create a unique and ethereal visual style.

// System Diagram : https://drive.google.com/file/d/15TXSXMif9LktKUACyGFgTMsaRNdV3-wx/view?usp=sharing

// Our private repository link on GitHub : https://github.com/MariamMedhatShawky/Assignment-3-

// Last Modification Date: 14/4/2024

// Author1 and ID and Group : Noran Mohamed Mokhtar   20230451   Group A  Email: noranmokhtar28@gmail.com
// Author2 and ID and Group : Nourhan Adel Mohamed    20230452   Group A  Email: nourhan.adel.eg@gmail.com
// Author3 and ID and Group : Mariam Medhat Shawky    20231166   Group A  Email: medhatmariiam@gmail.com

// Teaching Assistant: Ahmed Fouad Lotfy

// Who did what: Noran Mohamed Mokhtar : 1.Gray scale filter
//                                       2.Merge two images
//                                       3.Darken and lighten image filters
//                                       4.Edge detection filter
//                                       5.Sunlight filter

//               Nourhan Adel Mohamed :  1.Black and White filter
//                                       2.Flip image filter
//                                       3.Crop image filter
//                                       4.Resize image filter
//                                       5.Purple filter

//               Mariam Medhat Shawky :  1.Invert image filter
//                                       2.Rotate image filter
//                                       3.Adding a frame
//                                       4.Infrared filter

#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <filesystem>
#include "Image_class.h"
using namespace std;
namespace fs = filesystem;

// Function to validate that image exists
bool Validate_Image_Exist(const string& fileName) {
    if (!fs::exists(fileName)) { // Check if the file exists
        return false; // File doesn't exist
    }
    return true; // Return true if the file exists
}
// Function to validate image format
bool Validate_Image_Format(const string& fileName) {
    string extension;
    size_t dot_position = fileName.find_last_of('.'); // Get the position of the last dot in the filename
    if (dot_position == string::npos) { // Check if no dot is found in the file name
        return false; // Invalid file name format
    }
    extension = fileName.substr(dot_position); // Extract the extension (everything after the last dot)

    // Check if the extension is valid
    if (extension != ".jpg" && extension != ".jpeg" && extension != ".bmp" &&
        extension != ".png" && extension != ".tga") {
        return false; // Invalid file format
    }
    return true;
}
// Function to convert a color image to grayscale
void convert_to_Grayscale(Image& image) {
    // Loop through each pixel of the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int average_intensity = 0;
            // Calculate the average intensity across color channels
            for (int k = 0; k < image.channels; ++k) {
                average_intensity += image(i, j, k);
            }
            average_intensity /= image.channels;
            for (int k = 0; k < image.channels; ++k) {
                // Set all color channels to the calculated average intensity
                image(i, j, k) = average_intensity;
            }
        }
    }
}
// Function to convert an image to black and white
void blackWhite(Image& image){
    double avg;
    // Loop through each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Calculate average of RGB values
            avg = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;
            // Convert pixel to black or white based on average
            for (int k = 0; k < image.channels; ++k) {
                if (avg >= 150) {
                    image(i, j, k) = 255; // Set pixel to white
                } else {
                    image(i, j, k) = 0; // Set pixel to black
                }
            }
        }
    }
}
// Function to invert an image
void invertImage(Image& image) {
    // Loop through each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Invert the pixel value
                int pixel_value = image(i, j, k);
                image(i, j, k) = 255 - pixel_value;
            }
        }
    }
}
// Function to resize an image to the fixed dimensions
void resize_image(Image& image, int new_width, int new_height) {
    // Calculate scaling factors for width and height
    double width_ratio = image.width / (double)new_width;
    double height_ratio = image.height / (double)new_height;
    Image resized_image(new_width, new_height); // Create a new image with the wanted dimensions
    // Resize the image using nearest neighbor interpolation
    for (int i = 0; i < new_width; ++i) {
        for (int j = 0; j < new_height; ++j) {
            // Calculate the corresponding pixel position in the original image
            int start_i = i * width_ratio, start_j = j * height_ratio;
            // Ensure the new pixel position is within bounds
            int end_i = min(start_i, image.width - 1);
            int end_j = min(start_j, image.height - 1);
            for (int k = 0; k < image.channels; ++k) {
                // Closest neighbor interpolation
                resized_image(i, j, k) = image(end_i, end_j, k);
            }
        }
    }
    image = resized_image; // Update the original image with the resized image
}
// Function to merge two images based on the dimensions
void merge_images( Image& first_image, const Image& second_image, Image& result_image, const string &choice_resize) {
    // Calculate the dimensions of the merged image
    int max_width = max(first_image.width, second_image.width);
    int max_height = max(first_image.height, second_image.height);
    int min_width = min(first_image.width, second_image.width);
    int min_height = min(first_image.height, second_image.height);
    // First case : Images are the same size
    if (first_image.width == second_image.width && first_image.height == second_image.height) {
        result_image = Image(max_width, max_height);
        for (int i = 0; i < max_width; ++i) {
            for (int j = 0; j < max_height; ++j) {
                for (int k = 0; k < result_image.channels; ++k) {
                    // Merge pixel values directly by averaging
                    result_image(i, j, k) = (first_image(i, j, k) + second_image(i, j, k)) / 2;
                }
            }
        }
    }
        // Second case : Images are different sizes
    else {
        // Case : Resize both images to the largest dimensions
        if (choice_resize == "1") {
            // Create a result image with the dimensions of the merged images
            Image resized_first_image = first_image;
            Image resized_second_image = second_image;
            resize_image(resized_first_image, max_width, max_height);
            resize_image(resized_second_image, max_width, max_height);
            result_image = Image(max_width, max_height);
            // Merge the resized images
            for (int i = 0; i < max_width; ++i) {
                for (int j = 0; j < max_height; ++j) {
                    for (int k = 0; k < result_image.channels; ++k) {
                        // Merge pixel values directly by averaging
                        result_image(i, j, k) = (resized_first_image(i, j, k) + resized_second_image(i, j, k)) / 2;
                    }
                }
            }
        }
            // Case : Merge the common area of the smaller width and height
        else if (choice_resize == "2") {
            // Create a result image with the dimensions of the merged images
            result_image = Image(min_width, min_height);
            // Merge the common area
            for (int i = 0; i < min_width; ++i) {
                for (int j = 0; j < min_height; ++j) {
                    for (int k = 0; k < result_image.channels; ++k) {
                        // Merge pixel values directly by averaging
                        result_image(i, j, k) = (first_image(i, j, k) + second_image(i, j, k)) / 2;
                    }
                }
            }
        }
    }
    first_image = result_image; // Update the original image with the merged image
}
// Function to flip an image vertically
void  Flip_Vertically(Image& image) {
    // Loop through each column
    for (int i = 0; i < image.width; ++i) {
        // Loop through half of the rows
        for (int j = 0; j < image.height / 2; ++j) {
            // Calculate the corresponding row from the bottom
            int j2 = image.height - j - 1;
            // Swap pixels vertically
            for (int k = 0; k < 3; ++k) {
                int temp = image(i, j, k);
                image(i, j, k) = image(i, j2, k);
                image(i, j2, k) = temp;
            }
        }
    }
}
// Function to flip an image horizontally
void Flip_Horizontally(Image& image) {
    // Loop through half of the columns
    for (int i = 0; i < image.width / 2; ++i) {
        // Loop through each row
        for (int j = 0; j < image.height; ++j) {
            // Calculate the corresponding column from the right
            int i2 = image.width - i - 1;
            // Swap pixels horizontally
            for (int k = 0; k < 3; ++k) {
                int temp = image(i, j, k);
                image(i, j, k) = image(i2, j, k);
                image(i2, j, k) = temp;
            }
        }
    }
}
// Function to rotate an image by 90 degrees
void rotateImage90(Image& image) {
    Image rotated(image.height, image.width); // Create an image object to store the rotated image
    // Rotate the image by 90 degrees
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Perform the rotation by swapping pixel values
                rotated(image.height - 1 - j, i, k) = image(i, j, k);
            }
        }
    }
    image = rotated; // Update the original image with the rotated image
}
// Function to rotate an image by 180 degrees
void rotateImage180(Image& image) {
    Image rotated(image.width, image.height); // Create an image object to store the rotated image
    // Rotate the image by 180 degrees
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                // Perform the rotation by swapping pixel values
                rotated(image.width - 1 - i, image.height - 1 - j, k) = image(i, j, k);
            }
        }
    }
    image = rotated; // Update the original image with the rotated image
}
// Function to rotate an image by 270 degrees
void rotateImage270(Image& image) {
    // Create a new image with swapped dimensions for rotation by 270 degrees
    Image rotated(image.height, image.width);
    // Rotate the image by 270 degrees
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < image.channels; k++) {
                // Assign pixels from the original image to the rotated image with rotation transformation
                rotated(j, image.width - 1 - i, k) = image(i, j, k);
            }
        }
    }
    image = rotated; // Update the original image with the rotated image
}
// Function to adjust the brightness of an image
void adjust_brightness(Image& image, double factor) {
    // Loop through each pixel of the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                int intensity = image(i, j, k); // Get the intensity value of the pixel
                intensity = intensity * factor; // Adjust the intensity based on the given factor
                // Clamp the intensity value between 0 and 255
                if (intensity > 255) {
                    intensity = 255; // Clamp to maximum intensity
                }
                else if (intensity < 0) {
                    intensity = 0; // Clamp to minimum intensity
                }
                image(i, j, k) = intensity; // Set the adjusted intensity back to the pixel
            }
        }
    }
}
// Function to crop an image
void cropImage(Image& image) {
    int x, y, width, height;
    // Loop until valid starting point is entered
    while (true) {
        cout << "Please enter the starting point (x,y) : " << endl;
        // Check if input is valid
        if (!(cin >> x >> y) || !isspace(cin.peek())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Enter only integers." << endl;
            continue;
        }
        // Check if the starting point is within image bounds
        if (x < 0 || y < 0 || x >= image.width || y >= image.height) {
            cout << "Invalid. Enter valid dimensions." << endl;
            continue;
        } break;
    }
    // Loop until valid dimensions are entered
    while (true) {
        cout << "Enter the dimensions (width and height) : " << endl;
        // Check if input is valid
        if (!(cin >> width >> height) || !isspace(cin.peek())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Enter only integers." << endl;
            continue;
        }
        // Check if the dimensions are within image bounds
        if (width <= 0 || height <= 0 || x + width > image.width || y + height > image.height) {
            cout << "Invalid dimensions. Enter valid dimensions." << endl;
            continue;
        }
        break;
    }
    Image croppedImage(width, height); // Create a new image with the cropped dimensions
    // Copy pixels from original image to cropped image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < 3; ++k) {
                croppedImage(i, j, k) = image(i + x, j + y, k);
            }
        }
    }
    image = croppedImage; // Update original image with cropped image
}
// Function to apply a traditional frame to the image with the specified RGB color
void apply_traditional_frame(Image& image, int r, int g, int b) {
    // Set the top 10 rows to the specified color
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }
    // Set the bottom 10 rows to the specified color
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }
    // Set the left 10 columns to the specified color
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, image.height - 1 - j, 0) = r; // Set the red channel
                image(i, image.height - 1 - j, 1) = g; // Set the green channel
                image(i, image.height - 1 - j, 2) = b; // Set the blue channel
            }
        }
    }
    // Set the right 10 columns to the specified color
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(image.width - 1 - i, j, 0) = r; // Set the red channel
                image(image.width - 1 - i, j, 1) = g; // Set the green channel
                image(image.width - 1 - i, j, 2) = b; // Set the blue channel
            }
        }
    }
}

// Function to apply a fancy pattern to specific regions of the image with the specified RGB color
void apply_fancy_pattern(Image& image, int r, int g, int b) {
    // Creating fancy patterns on specific regions of the image


    for (int i = 0; i < image.width; ++i) {
        for (int j = 50; j < 70; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }

    for (int i = 70; i < 90; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }

    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 70; j < image.height - 50; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }

    for (int i = image.width - 90; i < image.width - 70; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, 0) = r; // Set the red channel
                image(i, j, 1) = g; // Set the green channel
                image(i, j, 2) = b; // Set the blue channel
            }
        }
    }
    // White rectangles
    for (int i = 0; i < image.width; ++i) {
        for (int j = 25; j < 35; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255; // Setting pixel values to white (RGB: 255, 255, 255)
            }
        }
    }
    // White vertical line
    for (int i = 35; i < 45; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255; // Setting pixel values to white (RGB: 255, 255, 255)
            }
        }
    }
    // White rectangles
    for (int i = 0; i < image.width; ++i) {
        for (int j = image.height - 35; j < image.height - 25; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255; // Setting pixel values to white (RGB: 255, 255, 255)
            }
        }
    }
    // White vertical line
    for (int i = image.width - 45; i < image.width - 35; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = 255; // Setting pixel values to white (RGB: 255, 255, 255)
            }
        }
    }
}

// Function to detect edges in an image
void edge_detection(Image& image) {
    // Create a new image to store the edges with the same dimensions as the input image
    Image edges(image.width, image.height);
    // Initialize the edges image to white (255) for all channels
    for (int i = 0; i < edges.height; ++i) {
        for (int j = 0; j < edges.width; ++j) {
            edges(j, i, 0) = edges(j, i, 1) = edges(j, i, 2) = 255;
        }
    }
    // Define Sobel kernels for horizontal and vertical edge detection
    int h_sobel[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int v_sobel[3][3] = {{-1, -2, -1},{0,  0,  0},{1,  2,  1}};
    // Iterate over each pixel in the image, excluding the border pixels
    for (int i = 1; i < image.height - 1; ++i) {
        for (int j = 1; j < image.width - 1; ++j) {
            int h_sum = 0; // Initialize horizontal sum
            int v_sum = 0; // Initialize vertical sum
            // Iterate over the 3x3 neighborhood of the current pixel
            for (int x = -1; x <= 1; ++x) {
                for (int y = -1; y <= 1; ++y) {
                    int x_index = x + 1 , y_index = y + 1;
                    int pixel_value = image(j + y, i + x, 0); // Get pixel value from the image
                    // Accumulate horizontal and vertical gradients
                    h_sum += pixel_value * h_sobel[x_index][y_index];
                    v_sum += pixel_value * v_sobel[x_index][y_index];
                }
            }
            // Compute the gradient magnitude using the Sobel operators
            // If the magnitude is greater than a threshold, set the corresponding pixel in the edges image to black (0)
            if (sqrt(pow(h_sum, 2) + pow(v_sum, 2)) > 100) {
                edges(j, i, 0) = edges(j, i, 1) = edges(j, i, 2) = 0; // Set pixel to black
            }
        }
    }
    image = edges; // Update the input image with the detected edges
}
// Function to resize an image to the specified dimensions
void resizeDimensions(Image& image) {
    int new_width, new_height;
    // Loop until valid dimensions are entered
    while (true) {
        cout << "Enter the new dimensions (width and height) : " << endl;
        // Check if input is valid
        if (!(cin >> new_width >> new_height) || !isspace(cin.peek())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Enter only integers." << endl;
            continue;
        }
        // Check if the dimensions are positive
        if (new_width <= 0 || new_height <= 0) {
            cout << "Invalid dimensions. Enter positive values." << endl;
            continue;
        }
        break;
    }
    Image image2(new_width, new_height); // Create a new image with the resized dimensions
    // Calculate ratios for resizing
    double width_ratio = double(image.width) / new_width;
    double height_ratio = double(image.height) / new_height;
    // Copy pixels from original image to resized image
    for (int i = 0; i < new_width; ++i) {
        for (int j = 0; j < new_height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int new_x = round(i * width_ratio);
                int new_y = round(j * height_ratio);
                image2(i, j, k) = image(new_x, new_y, k);
            }
        }
    }
    image = image2; // Update original image with resized image
}
// Function to resize an image based on a ratio
void resizeRatio(Image& image) {
    double ratio;
    // Loop until valid ratio in entered
    while (true) {
        cout << "Enter the resize ratio (decimal number) : " << endl;
        // Check if input is valid
        if (!(cin >> ratio) || !isspace(cin.peek())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error! Enter a number." << endl;
            continue;
        }
        // Check if the ratio is positive
        if (ratio <= 0) {
            cout << "Invalid ratio." << endl;
            continue;
        }
        break;
    }
    // Calculate new dimensions based on the ratio
    int new_width = image.width * ratio;
    int new_height = image.height * ratio;
    Image image2(new_width, new_height); // Create a new image with the resized dimensions
    // Calculate ratios for resizing
    double width_ratio = double(image.width) / new_width;
    double height_ratio = double(image.height) / new_height;
    // Copy pixels from original image to resized image
    for (int i = 0; i < new_width; ++i) {
        for (int j = 0; j < new_height; ++j) {
            for (int k = 0; k < 3; ++k) {
                int new_x = i * width_ratio;
                int new_y = j * height_ratio;
                image2(i, j, k) = image(new_x, new_y, k);
            }
        }
    }
    image = image2; // Update original image with resized image
}
// Function to apply a sunlight effect to the image
void sunlight(Image& image) {
    // Iterate over each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Increase brightness and shift colors towards sunlight tone
            // Increasing red color
            image(i, j, 0) = min(255, image(i, j, 0) + 35);
            // Increasing green color
            image(i, j, 1) = min(255, image(i, j, 1) + 50);
            // Decreasing blue color
            image(i, j, 2) = min(255, image(i, j, 2) - 15);
        }
    }
}
// Function to apply an infrared filter to the image
void infrared_filter(Image& image) {
    // Loop through each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Store the green channel value temporarily
            int tempGreen = image(i,j,1);
            // Set the red channel to maximum intensity (255)
            image(i, j, 0) = 255;
            // Set the green channel to the difference between maximum intensity and blue channel value
            image(i, j, 1) = 255 - image(i, j, 2);
            // Set the blue channel to the difference between maximum intensity and temporary green channel value
            image(i, j, 2) = 255 - tempGreen;
        }
    }
}
// Function to apply a purple tint to the image
void lookPurple(Image& image) {
    // Loop through each pixel in the image
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 0) = min(255, int(image(i, j, 0) * 1.2)); // Increase red
            image(i, j, 1) = int(image(i, j, 1) * 0.8); // Decrease green
            image(i, j, 2) = min(255, int(image(i, j, 2) * 1.3)); // Increase blue
        }
    }
}
int main() {
    // Welcome message
    cout << "Welcome to our \"Baby photoshop\"!" << endl;
    Image currentImage;
    string current_image_name;
    while (true) {
        cout << "Please enter the current image name and specify its extension: " << endl;
        getline(cin, current_image_name);
        // Check if image exists
        if (!Validate_Image_Exist(current_image_name)) {
            cout << "File '" << current_image_name << "' does not exist! Please try again." << endl;
            continue;
        }
        if (!Validate_Image_Format(current_image_name)) {
            cout << "Invalid image format! Supported formats: .jpg, .jpeg, .bmp, .png, .tga" << endl;
            continue;
        }

        // Load image
        if (currentImage.loadNewImage(current_image_name)) {
            cout << "Image loaded successfully" << endl;
        } else {
            cout << "Failed to load image" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    // Main menu
    while (true) {
        cout << "Menu Options:" << endl;
        cout << "1. Load a new image" << endl;
        cout << "2. Grayscale Conversion " << endl;
        cout << "3. Black and White" << endl;
        cout << "4. Invert Image" << endl;
        cout << "5. Merge Images" << endl;
        cout << "6. Flip Image (Vertical/Horizontal)" << endl;
        cout << "7. Rotate Image" << endl;
        cout << "8. Darken and Lighten Image" << endl;
        cout << "9. Crop Image" << endl;
        cout << "10. Adding a frame to the image" << endl;
        cout << "11. Detect image edges" << endl;
        cout << "12. Resizing Image" << endl;
        cout << "13. Sunlight effect" << endl;
        cout << "14. Look purple" << endl;
        cout << "15. Infrared photography" << endl;
        cout << "16. Save the image" << endl;
        cout << "17. Exit " << endl;
        cout << "Enter an option (1-17): " << endl;
        // Get user input
        string option;
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // Check if input is valid
        if (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" &&
            option != "7" && option != "8" && option != "9" && option != "10" && option != "11" && option != "12" &&
            option != "13" && option != "14" && option != "15" && option != "16" && option != "17" ) {
            cout << "Error! Invalid option." << endl;
            continue;
        }
        // Perform actions based on user input
        if (option == "1") { // Load a new image
            if (!current_image_name.empty()) { // Check if the current image name is not empty
                while (true) {
                    cout << "Do you want to save the current image before loading a new one? (Yes/No): " << endl;
                    string saveBeforeLoad;
                    cin >> saveBeforeLoad;
                    for (char &c: saveBeforeLoad) c = tolower(c);
                    if (saveBeforeLoad == "yes") {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        while (true) { //Save the image before loading a new one
                            cout << "Do you want to save the image with the same filename or specify a new filename? (Same/New): " << endl;
                            string saveOption;
                            cin >> saveOption;
                            for (char &c: saveOption) c = tolower(c);
                            // Save the image with the same filename
                            if (saveOption == "same") {
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                if (currentImage.saveImage(current_image_name)) {
                                    cout << "Image saved as '" << current_image_name << "'" << endl;
                                } else {
                                    cout << "Failed to save image" << endl;
                                }
                                break;
                                // Save the image with a new filename
                            } else if (saveOption == "new") {
                                string newFileName;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                while (true) { // Validate the new filename
                                    cout << "Please enter the new filename and specify its extension: " << endl;
                                    getline(cin, newFileName);
                                    if (!Validate_Image_Format(newFileName)) {
                                        cout << "Invalid image format! Supported formats: .jpg, .jpeg, .bmp, .png, .tga! Please try again." << endl;
                                        continue;
                                    }
                                    if (currentImage.saveImage(newFileName)) {
                                        cout << "Image saved as '" << newFileName << "'" << endl;
                                        current_image_name = newFileName; // Update current file name
                                    } else {
                                        cout << "Failed to save image" << endl;
                                    }
                                    break;
                                }
                                break;
                            } else { // Invalid option
                                cout << "Invalid option. Please enter 'Same' or 'New'." << endl;
                            }
                        }
                    } else if (saveBeforeLoad == "no") { // Do not save the image
                        cout << "Loading a new image without saving the current one." << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break; // Exit the loop when the user chooses not to save
                    } else { // Invalid option
                        cout << "Invalid option. Please enter 'Yes' or 'No'." << endl;
                        continue;
                    }
                    break;
                }

            } while (true) { // Load a new image
                cout << "Please enter the name of the new image file: " << endl;
                getline(cin, current_image_name);
                if (!Validate_Image_Exist(current_image_name)) { // Check if image exists
                    cout << "File '" << current_image_name << "' does not exist! Please try again." << endl;
                    continue;
                }
                if (!Validate_Image_Format(current_image_name)) {
                    cout << "Invalid image format! Supported formats: .jpg, .jpeg, .bmp, .png, .tga" << endl;
                    continue;
                }
                if (currentImage.loadNewImage(current_image_name)) {
                    cout << "Image loaded successfully" << endl;
                } else {
                    cout << "Failed to load image" << endl;
                    continue;
                }
                break;
            }
        } else if (option == "2") { // Convert to grayscale
            convert_to_Grayscale(currentImage); // Call the function to convert to grayscale
            cout << "Grayscale Conversion filter is added." << endl;
        } else if (option == "3") { // Convert to black and white
            blackWhite(currentImage); // Call the function to convert to black and white
            cout << "Black and White filter is added." << endl;
        } else if (option == "4") { // Invert image
            invertImage(currentImage); // Call the function to invert image
            cout << "Invert Image filter is added." << endl;
        } else if (option == "5") { // Merge images
            string second_image_name;
            Image second_image, result_image;
            string choice_resize;
            while (true) { // Load second image
                cout << "Please enter the name of the second image file: " << endl;
                getline(cin, second_image_name);
                // Check if image exists
                if (!Validate_Image_Exist(second_image_name)) {
                    cout << "File '" << second_image_name << "' does not exist! Please try again." << endl;
                    continue;
                }
                if (second_image.loadNewImage(second_image_name)) {
                    cout << "Image loaded successfully" << endl;
                } else {
                    cout << "Failed to load image" << endl;
                    continue;
                }
                break;
            }
            while (true) { // Get user's choice
                // Display menu options
                cout << "Available options:" << endl;
                cout << "1. Resize both images to the largest dimensions then merge." << endl;
                cout << "2. Merge the common area of the smaller width and height." << endl;
                cout << "Enter your choice: " << endl;
                cin >> choice_resize;
                if (choice_resize == "1" || choice_resize == "2") { // Validate the user's choice
                    break; // Exit the loop if the choice is valid
                } else { // Invalid input option
                    cout << "Invalid input. Please enter '1' or '2' to continue." << endl;
                }
            }
            // Call the function to merge the images based on user's choice
            merge_images(currentImage, second_image, result_image, choice_resize);
            cout << "Merge Image filter is added." << endl;
        } else if (option == "6") { // Flip image
            while (true) { // Get user's choice
                // Display menu options
                cout << "Which option do you want:" << endl;
                cout << "1. Flip Vertically" << endl;
                cout << "2. Flip Horizontally" << endl;
                cout << "Option 1 or 2 :" << endl;
                string option3;
                cin >> option3;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (option3 != "1" && option3 != "2") { // Validate the user's choice
                    cout << "Error! Please enter a valid choice" << endl;
                    continue;
                } else if (option3 == "1") { // Call the function to flip vertically
                    Flip_Vertically(currentImage);
                    cout << "Flip Image vertically filter is added." << endl;
                } else if (option3 == "2") { // Call the function to flip horizontally
                    Flip_Horizontally(currentImage);
                    cout << "Flip Image horizontally filter is added." << endl;
                }
                break;
            }
        } else if (option == "7") { // Rotate image
            while (true) { // Get user's choice
                cout << "Which option do you want:" << endl;
                cout << "1. Rotate image by 90 degree" << endl;
                cout << "2. Rotate image by 180 degree" << endl;
                cout << "3. Rotate image by 270 degree" << endl;
                cout << "Option (1-3):" << endl;
                string option6;
                cin >> option6;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                // Validate the user's choice
                if (option6 != "1" && option6 != "2" &&  option6 != "3") {
                    cout << "Error! Please enter a valid choice" << endl;
                    continue;
                } else if (option6 == "1") { // Call the function to rotate by 90 degree
                    rotateImage90(currentImage);
                    cout << "Rotate image by 90 degree filter is added." << endl;
                } else if (option6 == "2") { // Call the function to rotate by 180 degree
                    rotateImage180(currentImage);
                    cout << "Rotate image by 180 degree filter is added." << endl;
                } else if (option6 == "3") { // Call the function to rotate by 270 degree
                    rotateImage270(currentImage);
                    cout << "Rotate image by 270 degree filter is added." << endl;
                }
                break;
            }
        } else if (option == "8") { // Adjust brightness
            while (true) { // Get user's choice
                cout << "Which option do you want:" << endl;
                cout << "1. Make the image darker" << endl;
                cout << "2. Make the image lighter" << endl;
                cout << "Option 1 or 2: " << endl;
                string option4;
                cin >> option4;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (option4 != "1" && option4 != "2") { // Validate the user's choice
                    cout << "Error! Please enter a valid choice" << endl;
                    continue;
                }
                if (option4 == "1") { // Call the function to decrease brightness
                    adjust_brightness(currentImage, 0.5);
                    cout << "Adjust brightness filter is added" << endl;
                } else if (option4 == "2") { // Call the function to increase brightness
                    adjust_brightness(currentImage, 1.5);
                    cout << "Adjust brightness filter is added" << endl;
                }
                break;
            }
        } else if (option == "9") { // Crop image
            cropImage(currentImage); // Call the function to crop the image
            cout << "CropImage filter is added." << endl;
        }else if (option == "10") { // Add frame
            while (true) { // Get user's choice
                cout << "Please choose the type of frame:\n";
                cout << "1. Traditional frame\n";
                cout << "2. Fancy frame\n";
                string choiceframe;
                cin >> choiceframe;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (choiceframe == "1" || choiceframe == "2") {
                    while (true) {
                        cout << "Choose the color you want to apply:\n";
                        cout << "1. Black\n";
                        cout << "2. Green\n";
                        cout << "3. Blue\n";
                        cout << "4. White\n";
                        cout << "5. Red\n";

                        string colour;
                        cin >> colour;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        if (colour == "1" || colour == "2" || colour == "3" || colour =="4" || colour == "5") {
                            if (choiceframe == "1") {
                                if (colour == "1") {
                                    apply_traditional_frame(currentImage, 0, 0, 0);
                                    cout << "Traditional black frame is applied." << endl;
                                    break;
                                } else if (colour == "2") {
                                    apply_traditional_frame(currentImage, 0, 255, 0);
                                    cout << "Traditional green frame is applied." << endl;
                                    break;
                                } else if (colour == "3") {
                                    apply_traditional_frame(currentImage, 0, 0, 255);
                                    cout << "Traditional blue frame is applied." << endl;
                                    break;
                                } else if (colour == "4") {
                                    apply_traditional_frame(currentImage, 255, 255, 255);
                                    cout << "Traditional white frame is applied." << endl;
                                    break;
                                } else if (colour == "5") {
                                    apply_traditional_frame(currentImage, 255, 0, 0);
                                    cout << "Traditional red frame is applied." << endl;
                                    break;
                                }
                                break;
                            } else if (choiceframe == "2") {
                                if (colour == "1") {
                                    apply_fancy_pattern(currentImage, 0, 0, 0);
                                    cout << "Fancy black frame is applied." << endl;
                                    break;
                                } else if (colour == "2") {
                                    apply_fancy_pattern(currentImage, 0, 255, 0);
                                    cout << "Fancy green frame is applied." << endl;
                                    break;
                                } else if (colour == "3") {
                                    apply_fancy_pattern(currentImage, 0, 0, 255);
                                    cout << "Fancy blue frame is applied." << endl;
                                    break;
                                } else if (colour == "4") {
                                    apply_fancy_pattern(currentImage, 255, 255, 255);
                                    cout << "Fancy white frame is applied." << endl;
                                    break;
                                } else if (colour == "5") {
                                    apply_fancy_pattern(currentImage, 255, 0, 0);
                                    cout << "Fancy red frame is applied." << endl;
                                    break;
                                }
                                break;
                            }
                        } else {
                            cout << "Please select a valid color." << endl;
                            continue;
                        }
                        break;
                    }
                }

                else {
                    cout << "Please select a valid frame type." << endl;
                    continue;
                }

                break;
            }
        } else if (option == "11") { // Edge detection
            convert_to_Grayscale(currentImage); // Convert the image to grayscale
            edge_detection(currentImage); // Call the function to detect edges
            cout << "Edge Detection filter is added." << endl;
        } else if (option == "12") { // Resize image
            while (true) { // Get user's choice
                cout << "Which option do you want:" << endl;
                cout << "1. Resize Image by Entering New Dimensions" << endl;
                cout << "2. Resize Image by Entering a Ratio" << endl;
                cout << "Option 1 or 2: " << endl;
                string option5;
                cin >> option5;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (option5 != "1" && option5 != "2") { // Validate the user's choice
                    cout << "Error! Please enter a valid choice" << endl;
                    continue;
                } else if (option5 == "1") { // Call the function to resize the image by entering new dimensions
                    resizeDimensions(currentImage);
                    cout << "Resize image filter is added" << endl;
                } else if (option5 == "2") { // Call the function to resize the image by entering a ratio
                    resizeRatio(currentImage);
                    cout << "Resize image filter is added" << endl;
                }
                break;
            }
        } else if (option == "13") { // Apply the sunlight effect to the image
            sunlight(currentImage);
            cout << "Sunlight filter is added." << endl;
        } else if (option == "14") { // Apply the look purple effect to the image
            lookPurple(currentImage);
            cout << "Look purple filter is added." << endl;
        } else if (option == "15") { // Apply the infrared effect to the image
            infrared_filter(currentImage);
            cout << "Infrared filter is added." << endl;
        } else if (option == "16") { // Save image
            while (true) { // Get user's choice
                cout << "Do you want to save the image with the same filename or specify a new filename? (Same/New): " << endl;
                string saveOption;
                cin >> saveOption;
                for (char &c: saveOption) c = tolower(c);
                if (saveOption == "same") { // Save the image with the same filename
                    if (currentImage.saveImage(current_image_name)) {
                        cout << "Image saved as '" << current_image_name << "'" << endl;
                    } else {
                        cout << "Failed to save image" << endl;
                    }
                    break; // Exit the loop after saving the image
                } else if (saveOption == "new") { // Save the image with a new filename
                    string newFileName;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    while (true) { // Get user's new filename
                        cout << "Please enter the new filename and specify its extension: " << endl;
                        getline(cin, newFileName);
                        if (!Validate_Image_Format(newFileName)) { // Validate the image format
                            cout << "Invalid image format! Supported formats: .jpg, .jpeg, .bmp, .png, .tga! Please try again." << endl;
                            continue;
                        } if (currentImage.saveImage(newFileName)) {
                            cout << "Image saved as '" << newFileName << "'" << endl;
                            current_image_name = newFileName;
                        } else {
                            cout << "Failed to save image" << endl;
                        }
                        break; // Exit the inner loop after saving the image
                    }
                    break; // Exit the outer loop after processing the user's choice
                } else {
                    cout << "Invalid option. Please enter 'Same' or 'New'." << endl;
                    continue;
                }
            }
        } else if (option == "17") { // Exit
            if (!current_image_name.empty()) { // Let the user save the image before exiting
                cout << "Do you want to save the current image before exiting baby photoshop? (Yes/Exit): " << endl;
                string saveBeforeExit;
                cin >> saveBeforeExit;
                for (char &c: saveBeforeExit) c = tolower(c);
                while (true) { // Validate the user's choice
                    if (saveBeforeExit == "yes") {
                        while (true){ // Get user's choice
                            cout << "Do you want to save the image with the same filename or specify a new filename? (Same/New): " << endl;
                            string saveOption;
                            cin >> saveOption;
                            for (char &c: saveOption) c = tolower(c);
                            if (saveOption == "same") { // Save the image with the same filename
                                if (currentImage.saveImage(current_image_name)) {
                                    cout << "Image saved as '" << current_image_name << "'" << endl;
                                    cout << "Exiting baby photoshop ...." << endl;
                                    return 0;
                                }
                                break;
                            } else if (saveOption == "new") { // Save the image with a new filename
                                string newFileName;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                while (true) { // Get user's new filename
                                    cout << "Please enter the new filename and specify its extension: " << endl;
                                    getline(cin, newFileName);
                                    if (!Validate_Image_Format(newFileName)) { // Validate the image format
                                        cout << "Invalid image format! Supported formats: .jpg, .jpeg, .bmp, .png, .tga! Please try again." << endl;
                                        continue;
                                    } if (currentImage.saveImage(newFileName)) {
                                        cout << "Image saved as '" << newFileName << "'" << endl;
                                        current_image_name = newFileName;
                                        cout << "Exiting baby photoshop ...." << endl;
                                        return 0;
                                    }
                                    break;
                                }
                                break;
                            } else {
                                cout << "Invalid option. Please enter 'Same' or 'New': " << endl;
                            }
                        }
                    } else if (saveBeforeExit == "exit") { // Exit
                        cout << "Exiting baby photoshop ...." << endl;
                        return 0;
                    } else { // Invalid choice
                        cout << "Invalid option. Please enter 'Yes' or 'Exit': " << endl;
                        cin >> saveBeforeExit;
                        for (char &c: saveBeforeExit) c = tolower(c);
                    }
                }
            }
        }
    }
}
