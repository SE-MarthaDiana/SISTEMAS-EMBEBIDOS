// Lets create a simple meter

// Import Meter library
import meter.*;

// Import serial library
import processing.serial.*;

Serial port; // Define a port
int x1=50;
int y1=400;
int x2=500;
int y2=400;
int x3=280;
int y3=500;
int w=400;
int h=60;
boolean button1 = false;
boolean button2 = false;
boolean button3 = false;
Meter m, m2;

void setup(){
  // First we need to create a empty window
  size(950, 600); // Size of the window (width, height)
  background(#EFF2CD); // Background color of window (R,G,B)
  
  // Create new port
  port = new Serial(this, "COM6", 9600); //name of the port would be different for linux
  
  // Lets add a default meter to empty window
  // TEMPERATURE METER
  m = new Meter(this, 25, 80);  // here 25, 10 are x and y coordinates of meter's upper left corner
  
  m.setTitleFontSize(20);
  m.setTitleFontName("Arial bold");
  m.setTitle("Temperature (C)");
  
  // Change meter scale values
  String[] scaleLabels = {"0", "10", "20", "30", "40", "50", "60", "70", "80"};
  m.setScaleLabels(scaleLabels);
  m.setScaleFontSize(18);
  m.setScaleFontName("Times new roman bold");
  m.setScaleFontColor(color(200, 30, 70));
  
  // We can also display the value of meter
  m.setDisplayDigitalMeterValue(true);
  
  // Lets do some more modifications so our meter looks nice
  m.setArcColor(color(141, 113, 178));
  m.setArcThickness(15);
  
  m.setMaxScaleValue(80);
  
  m.setMinInputSignal(0);
  m.setMaxInputSignal(80);
  
  m.setNeedleThickness(3);
  
  // HUMIDITY METER
  // lets take some refference from first meter
  int mx = m.getMeterX(); // x coordinate of m
  int my = m.getMeterY(); // y coordinate of m
  int mw = m.getMeterWidth();
  
  m2 = new Meter(this, mx + mw + 20, my);
  
  m2.setTitleFontSize(20);
  m2.setTitleFontName("Arial bold");
  m2.setTitle("Humidity (%)");
  
  // Change meter scale values
  String[] scaleLabels2 = {"0", "10", "20", "30", "40", "50", "60", "70", "80", "90", "100"};
  m2.setScaleLabels(scaleLabels2);
  m2.setScaleFontSize(18);
  m2.setScaleFontName("Times new roman bold");
  m2.setScaleFontColor(color(200, 30, 70));
  
  // We can also display the value of meter
  m2.setDisplayDigitalMeterValue(true);
  
  // Lets do some more modifications so our meter looks nice
  m2.setArcColor(color(141, 113, 178));
  m2.setArcThickness(15);
  
  m2.setMaxScaleValue(100);
  
  m2.setMinInputSignal(0);
  m2.setMaxInputSignal(100);
  
  m2.setNeedleThickness(3);
}

void draw(){
  // Lets give title to our window
  fill(#D64747);
  stroke(0);
  rect(x1,y1, w, h);
   fill(#6C5498);
   rect(x2,y2, w, h);
   fill(#FCE5F8);
   rect(x3,y3, w, h);
  textSize(30);
  fill(0); // Font color , (r,g,b)
  text("Temperature and Humidity", 250, 40); // ("text", x, y)
  textSize(30);
  fill(0); // Font color , (r,g,b)
  text("Encender LED", x1+100, y1+40); // ("text", x, y)
  textSize(30);
  fill(0); // Font color , (r,g,b)
  text("Apagar LED", x2+100, y2+40); // ("text", x, y)
  textSize(30);
  fill(0); // Font color , (r,g,b)
  text("Parpadear", x3+100, y3+40); // ("text", x, y)
  textSize(35);
  fill(0); // Font color , (r,g,b)
  text("Equipo 1", 750, 550);
  if (button1){
    port.write(65);
    button1 = false;
    }
 if (button2){
    port.write(64);
    button2 = false;
    }
  if (button3){
    port.write(63);
    button3 = false;
    }
 
  if (port.available() > 0){
    String val = port.readString(); // read incoming string on serial port
    // First we need to separate temperature and humidity values
    String[] list = split(val, ','); // splits value separated by ','
    float temp = float(list[0]); // first value is Temperature
    float hum = float(list[1]);  // second value is Humidity
    
    m.updateMeter(int(temp)); // int is used due to updateMeter accepts only int values
    m2.updateMeter(int(hum));
    
    println("Temperature: " + temp + " C  " + "Humidity: " + hum+ "%");
  }
  
}
void mousePressed(){
  if ((mouseX > x1) && (mouseX < x1+w) && (mouseY > y1) && (mouseY < y1+h)){
    if(button1){
  button1 = false;
  } else {
  button1 = true;
  }
  }
  if ((mouseX > x2) && (mouseX < x2+w) && (mouseY > y2) && (mouseY < y2+h)){
    if(button2){
  button2 = false;
  } else {
  button2 = true;
  }
  }
  
  if ((mouseX > x3) && (mouseX < x3+w) && (mouseY > y3) && (mouseY < y3+h)){
    if(button3){
  button3 = false;
  } else {
  button3 = true;
  }
  }
  }
