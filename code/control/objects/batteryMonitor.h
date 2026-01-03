// Compiled successfully 2025-01-02

#ifndef BATTERYMONITOR_h
#define BATTERYMONITOR_h

#include <Arduino.h>
#include "voltageDivider.h"

class batteryMonitor {
    public: 
        batteryMonitor(uint8_t pin, float slope, float intercept, const char* type_def = "") 
        : reader(pin, slope, intercept) {
            if (strcmp(type_def, "FLOODED") == 0) {
                type = FLOODED;
            } else if (strcmp(type_def, "AGM") == 0) {
                type = AGM;
            } else if (strcmp(type_def, "GEL") == 0) {
                type = GEL;
            } else {
                type = UNKNOWN;
            }            
            
        };
        void set_type(const char* type_def){
            if (strcmp(type_def, "FLOODED") == 0) {
                type = FLOODED;
            } else if (strcmp(type_def, "AGM") == 0) {
                type = AGM;
            } else if (strcmp(type_def, "GEL") == 0) {
                type = GEL;
            } else {
                type = UNKNOWN;
            }
        }
        void set_pin(uint8_t pin_def){
            reader.set_pin(pin_def);
        }
        void set_slope(float m_def){
            reader.set_slope(m_def);
        }
        void set_offset(float b_def){
            reader.set_offset(b_def);
        }
        void set(uint8_t pin_def, float m_def, float b_def){
            reader.set(pin_def, m_def, b_def);
        }
        inline float read_voltage() const { 
            return reader.read(); 
        }
        inline float read_percentage() const {
            return get_percentage();
        }
        inline float read_percentage(const char* type_def) const {
            uint8_t battery_type;
            if (strcmp(type_def, "FLOODED") == 0) {
                battery_type = FLOODED;
            } else if (strcmp(type_def, "AGM") == 0) {
                battery_type = AGM;
            } else if (strcmp(type_def, "GEL") == 0) {
                battery_type = GEL;
            } else {
                battery_type = UNKNOWN;
            }
            return get_percentage(battery_type);
        }
    private:
        enum BatteryType { UNKNOWN, FLOODED, AGM, GEL };
        BatteryType type;
        linearDivider reader;
        float flooded_lead_acid_percent(float voltage){
            return 0.01077*voltage + 11.55;
        }
        float agm_percent(float voltage){
            return 0.015*voltage + 11.4;
        }
        float gel_percent(float voltage){
            return 0.015*voltage + 11.35;
        }
        float get_percentage(){
            return get_percentage(type);
        }
        float get_percentage(uint8_t index){
            float voltage = read_voltage();
            switch(index){
                case FLOODED: return flooded_lead_acid_percent(voltage);
                case AGM:     return agm_percent(voltage);
                case GEL:     return gel_percent(voltage);
                default:      return -1;
            }
        }
};

 // int percentage_indicies =   [100,   90,     80,     70,     60,     50,     40,     30,     20,     10,     0];
// float flooded_lead_acid =   [12.64, 12.53,  12.41,  12.29,  12.18,  12.07,  11.97,  11.87,  11.76,  11.63,  11.59];
// float agm =                 [12.90, 12.75,  12.60,  12.45,  12.30,  12.15,  12.00,  11.85,  11.70,  11.55,  11.40];
// float gel =                 [12.85, 12.70,  12.55,  12.40,  12.25,  12.10,  11.95,  11.80,  11.65,  11.50,  11.35];
// Trendline equations for battery percentage vs voltage graphs

#endif