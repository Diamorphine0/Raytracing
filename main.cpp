#include <QApplication>
#include <QImage>
#include <QLabel>
#include <cmath>
#include "utilities.hpp"
#include "hittable.hpp"

// Define constants for image size
const int WIDTH = 800;
const int HEIGHT = 600;


// Function to check if a ray intersects with a sphere
bool raySphereIntersection(const Vec3& rayOrigin, const Vec3& rayDirection,
                           const Vec3& sphereCenter, float sphereRadius) {
    Vec3 oc = rayOrigin - sphereCenter;
    float a = rayDirection.dot(rayDirection);
    float b = 2.0f * oc.dot(rayDirection);
    float c = oc.lengthSquared() - sphereRadius * sphereRadius;
    float discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}





// Function to render the image
void renderImage(QImage& image) {
    Vec3 cameraPosition(0.0f, 0.0f, 5.0f);
    Vec3 sphereCenter(0.0f, 0.0f, 0.0f);
    float sphereRadius = 100.0f;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            //Generating a ray for each pixel
            Vec3 rayOrigin(x - WIDTH / 2.0f, HEIGHT / 2.0f - y, 0.0f);
            Vec3 rayDirection(0.0f, 0.0f, -1.0f); // Looking down the negative z-axis
            if (raySphereIntersection(rayOrigin, rayDirection, sphereCenter, sphereRadius)) {
                // Pixel is inside the sphere, color it red
                image.setPixelColor(x, y, QColor(255, 0, 0));
            } else {
                // Pixel is outside the sphere
                // Draw the sphere (visualize it in blue)
                if (std::sqrt((x - WIDTH / 2) * (x - WIDTH / 2) + (y - HEIGHT / 2) * (y - HEIGHT / 2)) <= sphereRadius) {
                    // Inside the circle centered at the center of the image, draw the sphere
                    image.setPixelColor(x, y, QColor(0, 0, 255));
                } else {
                    // Other pixels outside the sphere, color it white
                    image.setPixelColor(x, y, QColor(255, 255, 255));
                }
            }
        }
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create an image with the specified width and height
    QImage image(WIDTH, HEIGHT, QImage::Format_RGB32);

    // Call the render function to generate the image
    renderImage(image);

    // Display the image in a QLabel
    QLabel label;
    label.setPixmap(QPixmap::fromImage(image));
    label.show();

    return a.exec();
}
