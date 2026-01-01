#ifndef BATTERYMONITOR_h
#define BATTERYMONITOR_h

#include "dependencies/libraries.h"
#include "voltageDivider.h"

class batteryMonitor {
    public: 
        batteryMonitor(uint8_t pin, float slope, float intercept, char* type_def = "") 
        : reader(pin, slope, intercept) {
            // Copy type_def into type, ensuring no buffer overflow
            strncpy(type, type_def, sizeof(type)-1);
            type[sizeof(type)-1] = '\0';
        };
        void set_slope(float m_def){
            reader.set_slope(m_def);
        }
        void set_offset(float b_def){
            reader.set_offset(b_def);
        }
        void set(unit8_t pin_def, float m_def, float b_def){
            reader.set(pin_def, m_def, b_def);
        }
        float read_voltage(){
            return get_voltage();
        }
        float read_percentage(){
            return get_percentage();
        }

    private:
        linearDivider reader;
        char type[32];
        // int percentage_indicies =   [100,   90,     80,     70,     60,     50,     40,     30,     20,     10,     0];
        // float flooded_lead_acid =   [12.64, 12.53,  12.41,  12.29,  12.18,  12.07,  11.97,  11.87,  11.76,  11.63,  11.59];
        // float agm =                 [12.90, 12.75,  12.60,  12.45,  12.30,  12.15,  12.00,  11.85,  11.70,  11.55,  11.40];
        // float gel =                 [12.85, 12.70,  12.55,  12.40,  12.25,  12.10,  11.95,  11.80,  11.65,  11.50,  11.35];
        // Trendline equations for battery percentage vs voltage graphs
        float flooded_lead_acid_percent(float voltage){
            return 0.01077*voltage + 11.55;
        }
        float agm_percent(float voltage){
            return 0.015*voltage + 11.4;
        }
        float gel_percent(float voltage){
            return 0.015*voltage + 11.35;
        }
        float get_voltage(){
            return reader.read();
        }
        float get_percentage(char* type_def = type){
            float voltage = read_voltage();
            float percentage;
            if(strcmp(type_def, "flooded_lead_acid") == 0){
                percentage = flooded_lead_acid_percent(voltage);
            } else if(strcmp(type_def, "agm") == 0){
                percentage = agm_percent(voltage);
            } else if(strcmp(type_def, "gel") == 0){
                percentage = gel_percent(voltage);
            } else {
                return -1;  // Unknown battery type
            }
            if (percentage > 100) {
                percentage = 100;
            } else if (percentage < 0) {
                percentage = 0;
            }
            return percentage;
        }
};

#endif