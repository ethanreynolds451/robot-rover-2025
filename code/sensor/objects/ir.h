void start_ir(){
  ir.begin(Pin::IR);    // No hardware initialization, just wont get any data if its not connected right
}

void read_ir(){
  if (ir.decode()) {
    value::ir = ir.decodedIRData.command;
    ir.resume();
  } else {
    value::ir = 0;   // no data recieved
  }
}

IRrecv ir;