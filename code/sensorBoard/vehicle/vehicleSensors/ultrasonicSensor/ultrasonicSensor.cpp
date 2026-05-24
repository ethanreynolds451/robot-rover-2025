#include "ultrasonicSensor.h"

namespace ultrasonic_sensor {

ultrasonic_object* ultrasonic_object::owners[ultrasonic_object::MAX] = { nullptr };
AsyncSonar* ultrasonic_object::keys[ultrasonic_object::MAX] = { nullptr };

} 