
class Pcf(){
  public:
    bool pcf_active = false;
    bool start_pcf(){
        bool addr_found = false;
        bool initiated = false;
        for (uint8_t tried = 0; tried < sensor_retry; tried++){
        if (!addr_found) {
            if (!Address::detect(Address::pcf)) {       
            
            delay(50); 
            } else {
            addr_found = true;
            }                                          
        } else if (!initiated) {
            if (!PCF.begin()) {
            delay(50); 
            } else {
            initiated = true;
            }
        } else {
            pcf_active = true; 
        }
        }
    }
}
