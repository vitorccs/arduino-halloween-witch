#include <Arduino.h>
#include <PCM.h>
#include <PWMServo.h>

#define PIN_BUZZER 11
#define PIN_ECHO 6
#define PIN_TRIGGER 5
#define PIN_SERVO 9
#define BUZZER_DISTANCE 60

PWMServo servoMotor;
unsigned int interval, distance;

const unsigned char sample[] PROGMEM = {
  126, 127, 127, 129, 129, 128, 130, 128, 127, 126, 126, 126, 126, 128, 129, 129, 130, 129, 128, 125, 126, 125, 125, 128, 130, 131, 130, 130, 127, 125, 125, 123, 126, 128, 130, 134, 132, 130, 128, 126, 124, 122, 124, 125, 128, 131, 133, 133, 132, 128, 123, 121, 119, 119, 127, 130, 132, 134, 140, 137, 122, 118, 115, 116, 122, 123, 131, 145, 153, 148, 126, 106, 104, 107, 100, 114, 147, 173, 180, 165, 127, 85, 89, 82, 58, 108, 171, 213, 217, 164, 136, 97, 49, 27, 46, 132, 186, 225, 230, 170, 143, 79, 21, 25, 45, 130, 201, 234, 228, 179, 143, 65, 18, 19, 44, 135, 198, 241, 232, 179, 151, 56, 7, 28, 37, 121, 219, 253, 221, 184, 143, 52, 16, 15, 40, 145, 225, 247, 217, 179, 132, 38, 12, 28, 56, 157, 243, 250, 202, 166, 113, 30, 15, 26, 71, 189, 255, 230, 191, 163, 92, 21, 18, 33, 100, 210, 248, 217, 182, 147, 75, 22, 25, 37, 125, 232, 234, 205, 175, 129, 81, 24, 6, 66, 161, 220, 224, 189, 151, 131, 76, 13, 34, 105, 170, 211, 202, 154, 135, 125, 65, 34, 75, 133, 187, 194, 149, 130, 141, 106, 63, 77, 113, 163, 187, 144, 126, 137, 114, 91, 89, 108, 153, 181, 152, 119, 122, 121, 99, 89, 115, 151, 183, 175, 110, 114, 139, 86, 84, 119, 147, 199, 176, 111, 119, 135, 88, 73, 118, 153, 200, 183, 99, 116, 138, 79, 75, 115, 160, 208, 178, 98, 106, 130, 75, 69, 120, 173, 217, 165, 90, 109, 114, 60, 67, 134, 192, 213, 141, 84, 128, 94, 37, 90, 148, 207, 198, 100, 113, 138, 54, 51, 118, 165, 211, 150, 92, 158, 109, 26, 95, 147, 185, 180, 98, 141, 165, 57, 56, 132, 177, 185, 115, 112, 179, 119, 58, 107, 155, 189, 148, 90, 153, 154, 82, 107, 144, 169, 168, 99, 115, 161, 101, 93, 154, 172, 169, 110, 81, 148, 121, 78, 141, 178, 187, 135, 61, 116, 126, 69, 124, 177, 190, 167, 75, 86, 122, 59, 87, 174, 200, 185, 100, 76, 120, 68, 53, 138, 200, 213, 133, 75, 119, 85, 40, 107, 175, 213, 172, 94, 123, 109, 34, 81, 159, 199, 185, 111, 131, 144, 49, 59, 137, 181, 194, 122, 120, 170, 81, 55, 130, 158, 179, 134, 113, 174, 111, 61, 129, 160, 165, 118, 106, 174, 126, 75, 130, 161, 170, 113, 84, 163, 129, 77, 146, 172, 168, 118, 73, 149, 126, 62, 145, 192, 184, 124, 60, 135, 127, 53, 128, 194, 199, 145, 68, 116, 118, 52, 114, 189, 202, 153, 81, 121, 115, 38, 103, 182, 199, 165, 83, 121, 132, 38, 83, 174, 194, 163, 95, 124, 129, 54, 84, 156, 193, 158, 88, 136, 135, 50, 95, 159, 176, 159, 90, 126, 146, 55, 90, 172, 178, 148, 90, 126, 142, 62, 95, 167, 187, 159, 81, 120, 144, 64, 101, 168, 181, 165, 94, 113, 136, 68, 102, 173, 183, 160, 101, 120, 136, 64, 98, 177, 186, 161, 100, 119, 141, 66, 94, 176, 189, 159, 96, 119, 142, 68, 91, 173, 192, 160, 94, 110, 139, 76, 87, 168, 194, 160, 95, 106, 128, 74, 95, 166, 188, 165, 95, 102, 130, 66, 91, 175, 183, 160, 104, 99, 122, 72, 89, 170, 192, 155, 101, 111, 117, 66, 98, 169, 188, 163, 96, 104, 127, 67, 97, 176, 181, 160, 105, 99, 121, 74, 100, 176, 184, 155, 102, 103, 118, 74, 102, 175, 187, 156, 101, 99, 112, 78, 108, 170, 185, 158, 105, 106, 105, 68, 115, 177, 182, 156, 104, 110, 110, 65, 109, 181, 187, 154, 108, 110, 106, 74, 113, 175, 188, 152, 113, 117, 100, 74, 121, 177, 187, 152, 110, 117, 100, 74, 125, 178, 188, 153, 109, 115, 94, 75, 126, 177, 193, 155, 108, 112, 91, 73, 121, 173, 195, 162, 113, 107, 87, 70, 113, 169, 194, 164, 119, 113, 87, 61, 101, 162, 194, 170, 120, 117, 97, 60, 84, 147, 189, 173, 133, 117, 105, 74, 71, 127, 176, 167, 145, 128, 111, 93, 72, 104, 156, 161, 150, 139, 122, 110, 90, 91, 131, 151, 152, 147, 130, 120, 113, 99, 113, 132, 148, 156, 138, 128, 120, 119, 114, 112, 139, 158, 148, 133, 122, 123, 130, 111, 121, 150, 151, 138, 127, 122, 131, 126, 114, 133, 145, 138, 131, 122, 125, 129, 123, 128, 134, 132, 126, 120, 125, 126, 129, 130, 131, 128, 119, 116, 119, 126, 129, 134, 132, 127, 122, 114, 114, 120, 127, 136, 140, 129, 124, 119, 114, 116, 123, 134, 140, 135, 127, 124, 121, 116, 120, 131, 136, 138, 133, 127, 124, 119, 121, 131, 136, 133, 136, 131, 125, 122, 122, 131, 134, 131, 134, 134, 128, 122, 122, 132, 134, 130, 131, 129, 129, 124, 120, 131, 134, 131, 129, 125, 124, 124, 123, 131, 134, 129, 127, 125, 125, 118, 120, 132, 133, 130, 125, 122, 127, 120, 117, 130, 131, 130, 129, 122, 124, 120, 119, 131, 130, 127, 129, 125, 125, 121, 119, 133, 133, 126, 127, 127, 126, 125, 123, 131, 133, 131, 127, 128, 129, 122, 126, 134, 131, 131, 130, 127, 131, 124, 124, 136, 134, 128, 130, 130, 130, 127, 126, 133, 133, 128, 127, 130, 131, 125, 126, 134, 131, 127, 126, 127, 131, 126, 125, 132, 131, 126, 125, 126, 128, 126, 126, 132, 131, 125, 125, 126, 126, 124, 125, 130, 131, 125, 124, 127, 125, 122, 124, 130, 129, 124, 125, 127, 127, 122, 122, 129, 130, 124, 124, 127, 127, 125, 124, 126, 128, 126, 124, 128, 127, 125, 127, 128, 127, 124, 126, 129, 129, 127, 127, 130, 128, 124, 126, 130, 130, 129, 129, 132, 128, 124, 127, 129, 129, 130, 131, 132, 131, 124, 126, 129, 128, 129, 131, 132, 132, 127, 125, 128, 127, 127, 130, 132, 132, 129, 126, 128, 126, 124, 128, 131, 131, 128, 127, 129, 126, 124, 126, 129, 129, 128, 128, 129, 127, 124, 126, 128, 127, 127, 128, 130, 127, 124, 126, 128, 127, 125, 127, 129, 127, 124, 126, 128, 127, 126, 127, 129, 127, 124, 126, 128, 127, 126, 128, 130, 126, 125, 127, 127, 127, 127, 128, 130, 126, 124, 128, 127, 127, 127, 129, 131, 127, 125, 127, 127, 126, 127, 130, 131, 128, 125, 127, 127, 126, 126, 130, 132, 128, 126, 126, 127, 127, 125, 130, 133, 129, 126, 127, 127, 127, 126, 129, 133, 129, 127, 127, 126, 127, 126, 129, 132, 129, 127, 127, 127, 126, 126, 129, 132, 129, 127, 127, 126, 125, 126, 129, 132, 129, 127, 127, 125, 124, 125, 129, 132, 129, 127, 127, 125, 123, 125, 128, 130, 129, 127, 128, 126, 123, 125, 128, 129, 129, 128, 129, 127, 124, 125, 128, 129, 128, 128, 130, 128, 126, 126, 127, 128, 128, 127, 130, 129, 126, 127, 128, 128, 127, 127, 129, 130, 127, 127, 128, 128, 126, 127, 129, 129, 128, 127, 128, 128, 126, 126, 128, 128, 128, 128, 128, 128, 127, 126, 127, 127, 128, 128, 128, 128, 127, 126, 127, 128, 127, 127, 128, 128, 126, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 128, 129, 129, 128, 126, 127, 126, 127, 127, 129, 129, 128, 128, 126, 126, 127, 127, 129, 130, 129, 128, 127, 127, 127, 126, 128, 130, 129, 129, 128, 127, 127, 126, 127, 129, 129, 129, 129, 127, 127, 127, 126, 127, 128, 129, 129, 127, 127, 127, 126, 126, 127, 129, 128, 128, 127, 126, 126, 126, 126, 129, 128, 128, 128, 126, 126, 127, 125, 128, 129, 128, 128, 125, 126, 127, 126, 128, 129, 129, 129, 126, 126, 127, 126, 128, 129, 129, 130, 127, 126, 126, 126, 129, 129, 129, 130, 127, 127, 126, 126, 129, 129, 129, 130, 127, 127, 126, 126, 128, 129, 129, 129, 127, 127, 126, 126, 127, 129, 129, 129, 127, 127, 126, 125, 127, 128, 129, 129, 127, 127, 126, 126, 127, 128, 129, 129, 128, 126, 126, 126, 127, 128, 128, 129, 128, 127, 126, 126, 127, 128, 128, 128, 128, 127, 126, 127, 127, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 127, 128, 127, 127, 129, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 128, 129, 128, 128, 128, 127, 127, 127, 128, 129, 129, 128, 128, 127, 127, 127, 128, 129, 129, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 126, 127, 128, 128, 129, 128, 127, 127, 126, 127, 128, 129, 128, 128, 128, 127, 126, 127, 128, 128, 128, 128, 128, 127, 126, 127, 128, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 128, 127, 128, 128, 127, 128, 128, 129, 128, 127, 127, 128, 127, 127, 128, 129, 128, 127, 127, 127, 127, 127, 128, 129, 128, 127, 128, 127, 127, 127, 128, 128, 128, 127, 128, 127, 127, 127, 127, 128, 127, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 127, 127, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 127, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 127, 128, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 127, 127, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 127, 127, 128, 127, 127, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 127, 128, 128, 128, 127, 127, 127, 128, 127, 128, 128, 128, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 126, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 126, 127, 128, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 128, 127, 128, 128, 128, 128, 127, 127, 127, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 128, 128, 128, 128, 128, 127, 126, 127, 128, 128, 127, 127, 128, 128, 127, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 127, 128, 127, 126, 127, 128, 128, 127, 127, 128, 128, 127, 127, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 127, 128, 128, 128, 128, 127, 127, 128, 127, 127, 127, 128, 128, 127, 128, 128, 127, 127, 127, 128, 127, 127, 128, 128, 128, 127, 127, 128, 128, 127, 128, 128, 127, 127, 128, 127, 128, 129, 128, 128, 128, 126, 125, 126, 128, 128, 128, 129, 128, 127, 127, 129, 127, 125, 128, 128, 127, 128, 127, 128, 128, 127, 128, 127, 127, 129, 127, 127, 128, 128, 128, 127, 127, 127, 126, 128, 129, 128, 128, 128, 128, 127, 126, 127, 127, 127, 129, 129, 127, 127, 128, 127, 128, 128, 129, 128, 127, 127, 125, 125, 128, 129, 129, 129, 130, 129, 126, 126, 125, 125, 126, 126, 128, 129, 131, 132, 131, 130, 126, 122, 122, 120, 124, 128, 130, 137, 136, 134, 136, 124, 114, 113, 118, 129, 129, 129, 143, 141, 127, 129, 133, 119, 106, 113, 133, 132, 125, 139, 144, 133, 132, 129, 111, 102, 119, 133, 130, 133, 144, 142, 130, 130, 129, 105, 100, 124, 136, 132, 132, 142, 142, 127, 128, 134, 107, 98, 126, 137, 134, 131, 138, 145, 125, 126, 136, 103, 100, 128, 137, 136, 130, 138, 144, 124, 130, 133, 100, 101, 130, 137, 133, 129, 141, 144, 125, 134, 130, 93, 104, 134, 135, 133, 133, 145, 139, 124, 141, 115, 87, 121, 133, 132, 136, 137, 147, 131, 131, 136, 96, 98, 128, 130, 135, 135, 143, 142, 131, 141, 110, 84, 120, 131, 129, 135, 142, 150, 132, 138, 127, 81, 103, 132, 126, 133, 141, 152, 141, 137, 133, 86, 96, 130, 123, 133, 142, 147, 142, 137, 138, 93, 90, 127, 123, 132, 144, 149, 144, 138, 140, 94, 89, 126, 121, 131, 145, 149, 143, 138, 141, 96, 90, 124, 123, 134, 141, 148, 146, 138, 139, 94, 89, 125, 122, 134, 145, 148, 144, 140, 139, 90, 88, 127, 124, 134, 143, 148, 143, 141, 136, 84, 93, 127, 122, 138, 144, 149, 141, 142, 131, 79, 101, 126, 121, 139, 143, 149, 139, 144, 122, 76, 113, 125, 120, 141, 146, 149, 136, 145, 109, 77, 124, 123, 124, 144, 149, 145, 137, 145, 92, 83, 132, 120, 128, 146, 154, 144, 139, 137, 80, 95, 132, 118, 133, 151, 156, 140, 147, 124, 70, 108, 128, 119, 138, 154, 155, 139, 150, 107, 72, 118, 121, 123, 144, 159, 150, 141, 146, 89, 86, 121, 113, 132, 148, 160, 146, 145, 131, 76, 102, 120, 113, 138, 154, 160, 142, 147, 110, 72, 113, 112, 120, 147, 162, 156, 141, 144, 87, 78, 118, 106, 126, 154, 172, 153, 143, 134, 69, 89, 119, 107, 132, 161, 175, 147, 146, 119, 64, 99, 116, 113, 140, 172, 171, 141, 145, 96, 69, 111, 111, 121, 147, 181, 166, 140, 137, 75, 81, 114, 109, 133, 157, 180, 157, 144, 121, 67, 94, 109, 112, 140, 168, 179, 147, 144, 100, 68, 107, 106, 122, 145, 174, 175, 143, 141, 80, 70, 109, 104, 132, 159, 179, 162, 148, 130, 65, 84, 103, 103, 139, 170, 185, 149, 153, 116, 55, 100, 98, 106, 146, 178, 183, 136, 153, 104, 52, 104, 101, 115, 156, 191, 175, 129, 139, 85, 62, 103, 104, 128, 167, 200, 165, 135, 126, 58, 73, 104, 106, 141, 179, 197, 149, 147, 125, 47, 78, 102, 109, 149, 191, 187, 133, 150, 116, 56, 87, 98, 114, 154, 199, 174, 127, 154, 98, 60, 97, 99, 122, 160, 201, 160, 124, 158, 92, 57, 94, 100, 129, 172, 197, 151, 126, 151, 94, 61, 90, 101, 131, 184, 193, 139, 130, 143, 93, 66, 90, 105, 127, 190, 198, 134, 131, 142, 91, 61, 88, 110, 123, 188, 204, 139, 129, 143, 100, 55, 82, 111, 115, 180, 205, 150, 130, 143, 118, 56, 75, 114, 103, 165, 203, 156, 133, 142, 136, 69, 66, 118, 103, 145, 199, 158, 127, 141, 145, 90, 59, 111, 116, 126, 195, 171, 119, 139, 149, 111, 58, 86, 127, 115, 177, 192, 126, 132, 149, 135, 72, 56, 118, 115, 147, 195, 158, 131, 138, 154, 108, 48, 82, 113, 121, 162, 187, 160, 135, 152, 141, 81, 52, 93, 115, 121, 175, 182, 153, 145, 149, 131, 66, 65, 99, 105, 146, 173, 171, 153, 145, 152, 112, 76, 70, 87, 121, 148, 171, 168, 160, 147, 132, 118, 77, 75, 94, 116, 149, 157, 176, 160, 133, 137, 111, 100, 92, 92, 118, 124, 152, 168, 153, 142, 125, 126, 118, 103, 110, 113, 116, 128, 147, 146, 132, 135, 138, 132, 121, 123, 120, 108, 120, 129, 125, 125, 132, 145, 141, 132, 131, 124, 124, 125, 120, 115, 112, 121, 139, 139, 132, 133, 135, 134, 128, 125, 124, 118, 124, 129, 119, 122, 129, 131, 132, 130, 133, 135, 134, 131, 119, 118, 126, 120, 122, 129, 126, 132, 140, 139, 126, 117, 129, 126, 118, 128, 126, 126, 133, 138, 134, 119, 120, 126, 123, 128, 129, 130, 131, 131, 134, 131, 121, 115, 123, 130, 125, 129, 133, 130, 127, 133, 136, 118, 120, 129, 124, 126, 127, 131, 124, 122, 140, 133, 130, 130, 123, 125, 121, 128, 124, 118, 128, 132, 142, 137, 128, 126, 119, 124, 119, 121, 126, 126, 141, 139, 138, 130, 119, 123, 113, 118, 125, 129, 139, 135, 141, 134, 123, 125, 115, 115, 119, 129, 138, 134, 138, 132, 126, 124, 121, 120, 118, 128, 130, 134, 137, 128, 128, 122, 125, 122, 120, 132, 127, 134, 134, 125, 128, 121, 126, 122, 121, 133, 130, 137, 132, 123, 128, 124, 126, 121, 120, 129, 130, 139, 133, 123, 127, 128, 130, 123, 120, 125, 128, 133, 132, 127, 127, 130, 131, 129, 123, 124, 131, 130, 125, 123, 127, 129, 129, 135, 128, 123, 133, 133, 126, 120, 124, 126, 122, 134, 131, 126, 133, 131, 129, 125, 126, 127, 118, 128, 130, 126, 134, 129, 128, 127, 128, 131, 122, 125, 128, 122, 130, 129, 126, 129, 126, 131, 129, 126, 131, 124, 125, 127, 122, 128, 125, 128, 134, 128, 133, 129, 121, 125, 121, 124, 127, 127, 136, 129, 130, 135, 121, 125, 126, 119, 124, 127, 137, 134, 128, 135, 123, 121, 130, 122, 122, 127, 132, 137, 132, 132, 125, 119, 126, 126, 125, 131, 128, 130, 136, 130, 126, 124, 122, 123, 125, 135, 133, 125, 136, 130, 122, 129, 125, 123, 123, 130, 135, 124, 132, 132, 120, 128, 128, 124, 128, 127, 130, 125, 127, 132, 122, 128, 131, 123, 129, 129, 127, 125, 124, 130, 125, 127, 135, 126, 127, 130, 125, 124, 121, 125, 128, 127, 136, 132, 128, 131, 126, 124, 120, 121, 127, 125, 133, 134, 129, 134, 130, 125, 121, 120, 128, 124, 129, 132, 126, 132, 132, 129, 123, 123, 130, 127, 128, 130, 125, 127, 129, 128, 125, 126, 131, 131, 130, 129, 126, 126, 127, 124, 122, 127, 130, 133, 133, 130, 127, 125, 128, 122, 121, 125, 128, 134, 133, 134, 129, 125, 127, 122, 122, 123, 125, 132, 131, 134, 132, 128, 128, 122, 123, 123, 125, 131, 129, 132, 131, 128, 128, 125, 124, 122, 126, 130, 130, 131, 131, 128, 125, 126, 125, 121, 125, 128, 131, 131, 132, 131, 124, 125, 125, 123, 126, 126, 129, 131, 131, 132, 127, 126, 123, 122, 127, 128, 128, 129, 131, 130, 128, 129, 125, 123, 125, 128, 129, 128, 130, 128, 127, 128, 126, 128, 126, 126, 129, 130, 130, 127, 127, 126, 124, 128, 129, 126, 127, 130, 130, 128, 129, 126, 124, 126, 129, 128, 126, 128, 129, 128, 130, 128, 126, 126, 128, 128, 127, 127, 127, 126, 128, 128, 128, 128, 128, 128, 128, 128, 126, 125, 127, 128, 127, 128, 128, 128, 129, 129, 127, 126, 126, 127, 126, 127, 128, 128, 129, 129, 128, 127, 127, 127, 126, 126, 127, 127, 128, 129, 128, 128, 127, 127, 127, 126, 126, 127, 128, 128, 128, 128, 127, 127, 128, 127, 125, 127, 129, 128, 128, 128, 128, 126, 128, 128, 126, 126, 129, 129, 128, 128, 129, 127, 127, 128, 127, 126, 128, 129, 128, 128, 129, 128, 128, 128, 127, 126, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 126, 127, 127, 127, 128, 128, 128, 128, 127, 127, 126, 127, 127, 126, 127, 128, 128, 128, 127, 127, 126, 127, 127, 127, 127, 128, 129, 129, 128, 127, 127, 126, 126, 127, 127, 128, 129, 130, 129, 128, 127, 127, 126, 126, 128, 128, 128, 130, 130, 128, 128, 128, 126, 126, 127, 128, 127, 129, 130, 129, 128, 128, 126, 126, 127, 127, 127, 129, 130, 129, 128, 128, 126, 126, 126, 126, 127, 128, 129, 129, 129, 128, 126, 126, 126, 126, 126, 128, 128, 128, 129, 128, 127, 126, 126, 126, 126, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 128, 127, 127, 128, 128, 127, 128, 128, 128, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 127, 128, 128, 127, 127, 127, 126, 127, 128, 128, 127, 127, 127, 128, 128, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 129, 129, 128, 127, 127, 127, 127, 127, 128, 128, 129, 129, 128, 128, 127, 127, 127, 127, 127, 128, 128, 129, 129, 128, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 126, 127, 127, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 128, 128, 129, 129, 129, 128, 128, 127, 127, 127, 128, 128, 129, 129, 129, 129, 128, 127, 127, 127, 127, 128, 128, 128, 129, 129, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 126, 126, 126, 127, 127, 127, 128, 128, 127, 127, 127, 126, 126, 126, 126, 127, 128, 128, 127, 128, 127, 126, 126, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 128, 127, 127, 128, 128, 128, 129, 129, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 126, 126, 126, 126, 127, 128, 128, 128, 128, 127, 127, 126, 126, 126, 127, 127, 127, 128, 128, 128, 127, 127, 127, 126, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 127, 128, 128, 127, 128, 128, 128, 127, 128, 128, 127, 128, 128, 127, 127, 128, 128, 127, 128, 128, 127, 128, 127, 127, 127, 127, 128, 127, 127, 128, 127, 127, 128, 128, 127, 127, 127, 127, 127, 128, 127, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 126, 126, 127, 127, 128, 128, 129, 129, 129, 129, 128, 128, 127, 126, 126, 126, 127, 127, 127, 129, 130, 131, 130, 131, 129, 126, 126, 124, 123, 124, 124, 126, 130, 132, 133, 135, 134, 128, 124, 123, 120, 119, 121, 123, 129, 133, 135, 139, 138, 132, 126, 122, 118, 117, 117, 118, 126, 133, 135, 139, 141, 135, 129, 124, 119, 116, 115, 115, 123, 132, 135, 141, 143, 139, 133, 126, 120, 115, 112, 112, 119, 129, 136, 143, 146, 144, 137, 128, 120, 114, 111, 109, 113, 126, 135, 142, 148, 147, 142, 131, 121, 114, 110, 108, 110, 121, 133, 141, 147, 149, 145, 134, 125, 114, 109, 108, 107, 116, 127, 140, 146, 147, 150, 139, 129, 117, 108, 110, 104, 111, 123, 134, 146, 147, 151, 147, 133, 121, 109, 110, 104, 105, 119, 129, 144, 149, 152, 151, 139, 125, 109, 108, 105, 102, 115, 126, 142, 150, 153, 154, 142, 129, 112, 108, 106, 101, 112, 123, 137, 150, 152, 154, 146, 132, 116, 109, 108, 100, 109, 121, 133, 150, 153, 154, 148, 132, 116, 107, 108, 100, 106, 122, 133, 150, 155, 156, 149, 132, 115, 105, 105, 98, 105, 120, 132, 154, 158, 157, 152, 134, 116, 101, 104, 98, 100, 117, 131, 153, 160, 162, 157, 136, 117, 102, 102, 96, 100, 114, 128, 153, 158, 160, 158, 140, 120, 105, 102, 94, 99, 114, 126, 152, 159, 159, 155, 140, 122, 107, 106, 95, 97, 111, 125, 152, 159, 158, 157, 141, 120, 106, 105, 96, 99, 113, 125, 148, 161, 159, 155, 145, 122, 107, 104, 93, 95, 111, 128, 151, 160, 158, 155, 148, 122, 108, 109, 94, 93, 106, 124, 149, 159, 160, 155, 146, 125, 110, 110, 99, 99, 106, 123, 146, 151, 153, 155, 146, 121, 113, 115, 100, 105, 112, 124, 150, 150, 145, 147, 141, 117, 110, 117, 104, 104, 116, 134, 156, 154, 147, 146, 134, 106, 104, 111, 101, 109, 115, 136, 164, 163, 154, 146, 138, 106, 94, 102, 95, 103, 112, 139, 169, 166, 159, 154, 139, 105, 100, 101, 85, 101, 109, 135, 171, 170, 163, 154, 137, 105, 100, 99, 86, 102, 109, 134, 170, 170, 161, 158, 142, 94, 96, 106, 82, 101, 116, 141, 171, 168, 164, 155, 138, 97, 89, 95, 83, 103, 117, 149, 178, 173, 165, 155, 137, 90, 84, 93, 75, 97, 115, 157, 186, 173, 176, 162, 137, 92, 80, 87, 69, 90, 110, 154, 188, 176, 179, 166, 146, 98, 79, 89, 69, 82, 103, 150, 184, 172, 179, 167, 152, 104, 76, 96, 76, 79, 105, 152, 176, 167, 179, 157, 152, 114, 71, 94, 83, 79, 104, 157, 183, 164, 178, 156, 144, 118, 68, 90, 86, 77, 104, 154, 184, 171, 179, 160, 146, 120, 66, 85, 85, 72, 102, 153, 180, 171, 184, 162, 150, 134, 65, 80, 92, 63, 93, 150, 176, 166, 180, 169, 150, 147, 79, 69, 103, 70, 76, 145, 177, 160, 172, 170, 146, 151, 101, 62, 100, 93, 70, 127, 179, 160, 165, 171, 142, 146, 119, 65, 83, 106, 83, 109, 177, 171, 154, 174, 150, 130, 131, 82, 61, 100, 98, 94, 161, 185, 159, 172, 164, 133, 128, 104, 61, 71, 104, 90, 122, 188, 171, 165, 183, 149, 129, 124, 88, 57, 82, 98, 89, 143, 182, 165, 178, 175, 144, 131, 123, 90, 61, 88, 97, 90, 142, 169, 159, 177, 169, 138, 138, 135, 101, 75, 90, 100, 91, 128, 158, 150, 164, 162, 141, 139, 139, 121, 95, 93, 100, 98, 114, 142, 146, 144, 158, 150, 139, 143, 129, 116, 103, 94, 102, 109, 123, 135, 143, 151, 151, 149, 141, 131, 130, 118, 99, 100, 107, 105, 122, 141, 142, 153, 156, 143, 135, 131, 125, 113, 108, 106, 105, 117, 127, 131, 145, 152, 146, 141, 134, 123, 120, 119, 113, 113, 123, 124, 125, 134, 136, 135, 137, 132, 123, 127, 130, 121, 123, 131, 126, 128, 132, 125, 123, 127, 119, 120, 133, 129, 129, 140, 137, 130, 132, 129, 120, 120, 116, 114, 124, 125, 128, 138, 142, 139, 136, 134, 125, 120, 115, 110, 117, 122, 126, 134, 144, 143, 136, 138, 133, 121, 114, 115, 113, 110, 123, 131, 137, 147, 143, 139, 138, 129, 118, 117, 116, 110, 114, 122, 133, 140, 137, 144, 141, 130, 126, 124, 121, 116, 118, 119, 125, 133, 131, 134, 139, 132, 124, 127, 127, 118, 124, 128, 128, 132, 129, 130, 130, 127, 122, 122, 127, 121, 121, 129, 134, 135, 134, 133, 129, 129, 122, 116, 126, 121, 116, 127, 135, 134, 135, 138, 131, 127, 127, 120, 120, 122, 121, 122, 129, 136, 135, 135, 133, 129, 126, 122, 123, 121, 120, 126, 128, 130, 136, 139, 134, 129, 128, 124, 122, 120, 120, 123, 127, 128, 131, 136, 135, 131, 131, 130, 124, 122, 123, 121, 124, 126, 125, 130, 133, 130, 129, 132, 131, 124, 125, 127, 125, 122, 124, 127, 126, 127, 130, 132, 130, 129, 129, 128, 126, 124, 124, 124, 125, 125, 126, 130, 132, 130, 130, 133, 133, 125, 122, 125, 123, 120, 126, 130, 127, 131, 135, 133, 133, 132, 128, 123, 120, 121, 122, 127, 126, 126, 134, 135, 135, 133, 132, 129, 123, 119, 119, 127, 123, 122, 130, 132, 133, 132, 134, 134, 128, 123, 122, 125, 123, 122, 126, 127, 129, 127, 131, 132, 130, 130, 127, 129, 129, 122, 125, 127, 124, 122, 126, 127, 125, 129, 130, 132, 133, 130, 129, 128, 128, 121, 122, 124, 120, 123, 128, 132, 133, 131, 135, 133, 129, 127, 126, 122, 121, 123, 121, 127, 132, 130, 133, 136, 131, 128, 129, 126, 122, 125, 124, 124, 127, 129, 131, 132, 131, 129, 129, 128, 124, 125, 126, 126, 128, 128, 130, 131, 130, 126, 125, 127, 125, 124, 126, 128, 127, 129, 131, 130, 130, 128, 124, 125, 125, 124, 125, 127, 127, 128, 130, 130, 131, 129, 127, 125, 125, 125, 125, 127, 127, 129, 130, 129, 129, 129, 127, 127, 126, 126, 126, 127, 128, 129, 130, 130, 129, 128, 127, 126, 126, 126, 126, 126, 128, 130, 130, 130, 131, 129, 127, 127, 125, 124, 125, 126, 125, 128, 131, 129, 130, 131, 130, 128, 127, 126, 125, 125, 125, 126, 127, 128, 128, 129, 130, 129, 128, 127, 127, 127, 126, 126, 127, 126, 126, 127, 127, 129, 129, 129, 128, 128, 128, 127, 128, 127, 126, 127, 127, 127, 128, 128, 129, 128, 128, 128, 127, 128, 127, 126, 126, 127, 128, 127, 129, 129, 128, 128, 129, 128, 127, 127, 127, 126, 127, 128, 127, 129, 128, 127, 129, 129, 127, 127, 127, 127, 127, 127, 127, 128, 129, 128, 128, 129, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 128, 127, 128, 129, 128, 128, 129, 127, 127, 128, 127, 126, 128, 127, 126, 128, 129, 127, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 127, 129, 128, 127, 127, 127, 127, 127, 128, 128, 128, 129, 128, 128, 129, 128, 126, 127, 127, 127, 128, 128, 128, 128, 129, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 129, 128, 127, 127, 127, 126, 126, 127, 128, 127, 128, 128, 128, 128, 128, 127, 126, 126, 126, 126, 127, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 128, 127, 128, 128, 128, 127, 128, 127, 127, 127, 128, 128, 128, 128, 128, 129, 128, 128, 128, 127, 127, 127, 127, 128, 129, 129, 128, 129, 128, 128, 128, 127, 126, 126, 127, 126, 128, 129, 129, 129, 129, 128, 127, 127, 126, 125, 126, 126, 126, 128, 128, 129, 130, 129, 129, 128, 126, 126, 126, 126, 126, 127, 127, 128, 129, 129, 129, 129, 129, 127, 127, 128, 126, 126, 127, 127, 126, 128, 128, 128, 129, 129, 128, 128, 128, 127, 127, 127, 127, 126, 127, 127, 127, 128, 128, 128, 129, 128, 128, 128, 128, 127, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 128, 128, 127, 128, 128, 128, 128, 127, 127, 127, 128, 128, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 129, 128, 128, 127, 127, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 127, 128, 129, 128, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 129, 128, 128, 128, 128, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 126, 126, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 126, 126, 126, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 129, 128, 128, 128, 128, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 128, 127, 127, 128, 128, 127, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 127, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 129, 129, 129, 129, 129, 128, 127, 127, 126, 126, 126, 126, 127, 128, 129, 130, 131, 131, 131, 130, 127, 126, 124, 123, 123, 123, 123, 126, 129, 130, 134, 135, 134, 132, 128, 126, 121, 119, 120, 117, 120, 127, 128, 132, 137, 138, 136, 134, 129, 125, 120, 118, 118, 115, 119, 126, 128, 135, 139, 139, 138, 135, 131, 125, 119, 117, 116, 113, 119, 126, 129, 136, 142, 142, 141, 137, 131, 124, 117, 116, 114, 113, 118, 125, 131, 137, 142, 143, 142, 139, 133, 124, 117, 116, 113, 110, 118, 123, 126, 137, 142, 142, 144, 141, 136, 127, 117, 116, 113, 108, 116, 123, 122, 134, 144, 141, 144, 144, 138, 130, 118, 115, 114, 106, 111, 123, 122, 128, 144, 144, 141, 146, 142, 133, 122, 113, 116, 109, 104, 119, 124, 122, 139, 146, 141, 145, 144, 136, 126, 114, 114, 112, 102, 113, 125, 121, 133, 146, 142, 143, 146, 140, 131, 118, 113, 116, 103, 106, 124, 122, 125, 145, 146, 141, 146, 145, 136, 122, 113, 117, 109, 101, 121, 127, 121, 140, 149, 141, 144, 146, 141, 126, 113, 118, 115, 100, 113, 130, 121, 132, 150, 145, 142, 145, 143, 130, 112, 112, 118, 100, 105, 131, 124, 126, 147, 148, 141, 142, 145, 133, 114, 110, 120, 104, 96, 126, 127, 121, 143, 151, 142, 143, 147, 138, 117, 106, 119, 108, 92, 120, 129, 120, 139, 155, 144, 143, 149, 141, 124, 104, 117, 113, 89, 114, 130, 119, 132, 156, 147, 141, 152, 146, 130, 104, 116, 119, 85, 109, 133, 117, 127, 159, 150, 138, 153, 148, 130, 105, 114, 122, 87, 103, 137, 119, 121, 159, 153, 136, 152, 152, 132, 103, 114, 124, 88, 99, 136, 125, 118, 158, 154, 133, 148, 148, 133, 102, 111, 126, 94, 102, 134, 131, 120, 153, 157, 134, 146, 144, 131, 101, 106, 124, 93, 101, 135, 132, 126, 156, 159, 135, 146, 146, 126, 96, 104, 118, 88, 100, 135, 132, 127, 163, 165, 140, 150, 150, 127, 90, 102, 115, 77, 93, 136, 131, 126, 169, 174, 145, 155, 160, 133, 87, 101, 119, 70, 80, 134, 128, 115, 169, 177, 146, 161, 168, 144, 90, 102, 123, 70, 74, 128, 127, 108, 163, 178, 141, 161, 170, 147, 97, 104, 131, 73, 76, 128, 119, 109, 157, 170, 140, 159, 166, 146, 103, 98, 133, 84, 71, 135, 125, 101, 164, 170, 132, 158, 163, 143, 100, 93, 129, 86, 69, 135, 137, 98, 168, 185, 123, 159, 167, 138, 106, 86, 123, 90, 64, 126, 140, 102, 156, 197, 137, 151, 169, 144, 112, 74, 116, 104, 52, 118, 155, 103, 147, 205, 144, 145, 169, 144, 120, 74, 99, 113, 58, 99, 155, 118, 137, 204, 159, 145, 169, 139, 136, 85, 70, 117, 68, 73, 145, 135, 135, 195, 184, 148, 166, 140, 127, 109, 55, 100, 97, 57, 123, 141, 132, 177, 189, 163, 163, 156, 129, 125, 74, 60, 110, 67, 78, 145, 136, 156, 190, 180, 157, 155, 145, 123, 104, 63, 85, 101, 64, 114, 149, 136, 172, 194, 164, 143, 157, 136, 107, 98, 75, 87, 92, 90, 129, 141, 149, 182, 183, 153, 145, 151, 121, 106, 104, 75, 84, 102, 99, 125, 147, 153, 172, 179, 153, 140, 145, 120, 112, 110, 84, 94, 103, 100, 121, 136, 141, 157, 174, 159, 138, 144, 137, 116, 115, 117, 91, 87, 120, 112, 102, 137, 147, 146, 163, 153, 136, 139, 135, 131, 125, 105, 100, 111, 104, 94, 118, 129, 129, 153, 165, 146, 141, 158, 139, 117, 129, 117, 96, 101, 106, 102, 106, 127, 140, 142, 156, 165, 153, 142, 140, 128, 114, 111, 108, 104, 103, 109, 125, 122, 125, 149, 151, 144, 154, 148, 127, 123, 129, 115, 102, 115, 123, 118, 125, 139, 130, 124, 140, 136, 125, 128, 132, 129, 121, 127, 131, 123, 125, 136, 132, 123, 130, 128, 119, 121, 125, 123, 118, 126, 134, 130, 135, 138, 136, 131, 132, 128, 118, 121, 120, 116, 118, 124, 128, 128, 139, 137, 133, 139, 130, 127, 125, 119, 123, 120, 116, 122, 129, 123, 131, 141, 131, 134, 140, 130, 127, 126, 125, 122, 115, 121, 126, 119, 127, 136, 130, 130, 136, 136, 129, 130, 127, 128, 126, 119, 130, 123, 117, 131, 132, 124, 122, 136, 132, 125, 133, 130, 127, 125, 133, 131, 117, 125, 131, 125, 122, 130, 131, 123, 130, 132, 127, 128, 129, 132, 128, 121, 125, 128, 121, 124, 132, 128, 124, 130, 132, 128, 130, 131, 130, 126, 123, 127, 122, 120, 123, 125, 127, 126, 131, 132, 133, 134, 132, 132, 125, 123, 128, 125, 118, 121, 127, 120, 121, 130, 131, 131, 136, 138, 133, 128, 131, 131, 123, 119, 124, 125, 119, 121, 129, 130, 125, 132, 140, 130, 129, 140, 131, 121, 127, 130, 119, 117, 128, 128, 123, 126, 135, 132, 125, 137, 134, 124, 127, 130, 126, 119, 125, 127, 124, 124, 129, 135, 127, 129, 136, 127, 124, 127, 125, 120, 124, 129, 125, 126, 129, 130, 133, 131, 127, 129, 128, 125, 123, 125, 123, 120, 128, 128, 125, 130, 134, 133, 128, 131, 132, 125, 123, 125, 127, 120, 123, 131, 125, 127, 132, 133, 129, 126, 133, 130, 122, 125, 131, 124, 122, 132, 129, 126, 130, 130, 128, 126, 128, 130, 124, 124, 130, 129, 125, 129, 132, 131, 129, 128, 130, 127, 123, 129, 126, 120, 126, 129, 126, 128, 132, 133, 131, 129, 129, 128, 122, 124, 126, 122, 123, 125, 128, 128, 129, 132, 132, 129, 127, 129, 126, 123, 126, 125, 123, 123, 127, 128, 127, 130, 132, 129, 128, 127, 127, 127, 124, 126, 127, 125, 127, 130, 129, 127, 131, 133, 127, 127, 128, 127, 125, 126, 130, 125, 126, 131, 131, 128, 129, 133, 129, 126, 129, 127, 126, 125, 128, 129, 126, 128, 131, 129, 126, 129, 129, 126, 126, 128, 127, 125, 126, 129, 127, 126, 131, 129, 125, 128, 128, 125, 125, 126, 125, 125, 126, 128, 128, 126, 129, 130, 127, 127, 128, 127, 126, 127, 127, 125, 127, 128, 127, 127, 128, 129, 127, 127, 127, 127, 128, 127, 129, 128, 127, 131, 128, 127, 130, 127, 126, 128, 127, 125, 128, 128, 126, 128, 130, 130, 128, 129, 130, 128, 126, 128, 127, 124, 127, 128, 126, 126, 128, 129, 127, 128, 129, 127, 128, 128, 128, 126, 126, 128, 126, 127, 128, 127, 126, 127, 128, 126, 127, 128, 128, 127, 128, 128, 128, 127, 128, 128, 126, 128, 128, 126, 127, 128, 128, 127, 128, 129, 128, 128, 128, 128, 127, 127, 127, 127, 127, 128, 128, 128, 127, 128, 128, 127, 128, 128, 126, 127, 128, 126, 126, 127, 127, 128, 127, 127, 128, 128, 127, 128, 128, 127, 127, 128, 126, 127, 127, 127, 127, 127, 127, 128, 127, 127, 128, 128, 127, 128, 128, 127, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 127, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 126, 128, 128, 127, 128, 128, 128, 128, 128, 128, 127, 128, 127, 127, 126, 126, 127, 126, 127, 127, 127, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 128, 127, 127, 127, 128, 128, 128, 128, 128, 129, 129, 129, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 129, 128, 129, 129, 128, 128, 127, 127, 127, 127, 127, 128, 127, 127, 129, 128, 128, 129, 128, 127, 127, 126, 126, 126, 126, 127, 128, 127, 128, 128, 127, 128, 128, 127, 127, 126, 126, 127, 126, 127, 127, 126, 128, 128, 127, 128, 129, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 127, 128, 128, 127, 129, 129, 128, 128, 128, 127, 128, 127, 127, 127, 127, 127, 128, 127, 128, 129, 128, 128, 128, 127, 127, 127, 126, 126, 127, 127, 127, 127, 128, 129, 128, 128, 128, 127, 127, 127, 126, 126, 127, 127, 127, 128, 128, 128, 129, 129, 129, 128, 128, 128, 127, 127, 127, 126, 127, 127, 128, 129, 129, 129, 129, 129, 128, 128, 128, 126, 127, 127, 126, 127, 128, 127, 128, 129, 129, 128, 128, 128, 127, 127, 127, 126, 126, 127, 127, 127, 128, 128, 128, 129, 128, 128, 128, 127, 127, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 127, 127, 127, 126, 127, 126, 127, 127, 127, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 128, 128, 128, 128, 127, 128, 127, 127, 128, 127, 127, 128, 127, 127, 127, 127, 128, 128, 128, 127, 128, 127, 127, 128, 127, 127, 128, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 128, 127, 127, 128, 127, 128, 128, 128, 128, 128, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 128, 127, 127, 128, 127, 128, 127, 127, 127, 126, 127, 127, 127, 127, 127, 128, 128, 129, 129, 129, 129, 129, 128, 127, 127, 126, 125, 126, 125, 126, 127, 128, 129, 130, 132, 132, 132, 132, 129, 127, 125, 124, 122, 123, 122, 122, 127, 129, 131, 135, 135, 135, 135, 133, 128, 126, 121, 118, 120, 118, 119, 123, 125, 131, 134, 137, 138, 137, 138, 132, 129, 125, 117, 117, 117, 114, 117, 123, 125, 131, 138, 137, 141, 140, 138, 136, 129, 127, 118, 114, 118, 112, 114, 123, 123, 129, 136, 139, 140, 142, 140, 136, 135, 127, 121, 116, 113, 115, 112, 115, 124, 125, 131, 139, 140, 141, 142, 138, 135, 133, 125, 119, 114, 113, 114, 110, 118, 125, 125, 134, 140, 139, 142, 142, 137, 135, 132, 124, 118, 112, 114, 113, 111, 122, 126, 126, 138, 141, 140, 143, 142, 136, 134, 132, 123, 115, 113, 115, 111, 113, 125, 125, 129, 140, 141, 140, 145, 141, 135, 136, 130, 121, 113, 113, 114, 108, 114, 124, 123, 131, 141, 141, 142, 146, 140, 135, 134, 129, 119, 110, 114, 113, 108, 118, 123, 123, 132, 142, 138, 140, 145, 137, 134, 132, 128, 117, 111, 116, 113, 108, 120, 125, 122, 136, 143, 136, 143, 143, 136, 134, 134, 128, 114, 114, 116, 111, 109, 121, 124, 123, 139, 141, 138, 147, 143, 138, 139, 137, 126, 113, 115, 114, 106, 108, 120, 119, 124, 140, 140, 140, 150, 145, 137, 140, 139, 120, 107, 117, 112, 96, 114, 122, 113, 132, 143, 137, 144, 154, 141, 135, 142, 133, 110, 107, 119, 100, 97, 124, 116, 121, 143, 145, 142, 150, 155, 134, 139, 141, 118, 105, 111, 113, 94, 106, 126, 115, 130, 150, 147,
};

void playAudio();
void shakeLegs();
int getDistance(int trigPin, int echoPin);
void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {
  Serial.begin(9600);

  // set distance sensor
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  // set servo motor
  servoMotor.attach(PIN_SERVO);
}

void loop() {
  distance = getDistance(PIN_TRIGGER, PIN_ECHO);
  Serial.print('distance ');
  Serial.println(distance);

  if (distance <= BUZZER_DISTANCE) {
    Serial.println('tocando');
    shakeLegs();
    shakeLegs();

    playAudio();
    delay(5000); 
    resetFunc();
  }

  delay(300);
}

void playAudio() {
  startPlayback(sample, sizeof(sample));
}

void shakeLegs() {
  servoMotor.write(30);
  delay(500);
  servoMotor.write(110);
  delay(500);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH)/58;
}