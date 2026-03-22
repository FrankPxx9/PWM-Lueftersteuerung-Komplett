# Configuration parameters for PWM Fan Controller

## WiFi Settings
#define WIFI_SSID "Your_SSID"
#define WIFI_PASSWORD "Your_Password"

## Pin Definitions
#define PWM_PIN 5  // GPIO pin for PWM
#define TEMP_SENSOR_PIN 4  // GPIO pin for temperature sensor

## PWM Frequency and Values
#define PWM_FREQUENCY 25000  // 25 kHz
#define MIN_PWM_VALUE 0  // Minimum PWM value
#define MAX_PWM_VALUE 255  // Maximum PWM value

## Temperature Thresholds
#define TEMP_THRESHOLD_HIGH 75  // High temperature threshold in Celsius
#define TEMP_THRESHOLD_LOW 30  // Low temperature threshold in Celsius

## Webserver Settings
#define WEBSERVER_PORT 80  // Port for the web server
#define WEBSERVER_TIMEOUT 30  // Timeout in seconds

## Debug Configuration
#define DEBUG_ENABLED 1  // Set to 1 to enable debug messages
#define DEBUG_LEVEL 2  // Set debug level (0: Error, 1: Warning, 2: Info, 3: Verbose)
