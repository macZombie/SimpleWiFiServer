
#include <WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 
#define SCREEN_ADDRESS 0x3C 
#define NUMFLAKES     4 // Number of snowflakes in the animation example
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define XPOS   0 // Indexes into the 'icons' array in testanimate
#define YPOS   1
#define DELTAY 2



#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C
#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18
#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18




const char* ssid     = "QuantumBit";

const char* password = "DeRosa_123";


WiFiServer server(80);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int status = 0;

static const unsigned char PROGMEM logo_bmp[] = { 
    0b00000000, 0b11000000,
    0b00000001, 0b11000000,
    0b00000001, 0b11000000,
    0b00000011, 0b11100000,
    0b11110011, 0b11100000,
    0b11111110, 0b11111000,
    0b01111110, 0b11111111,
    0b00110011, 0b10011111,
    0b00011111, 0b11111100,
    0b00001101, 0b01110000,
    0b00011011, 0b10100000,
    0b00111111, 0b11100000,
    0b00111111, 0b11110000,
    0b01111100, 0b11110000,
    0b01110000, 0b01110000,
    0b00000000, 0b00110000 
    
};



///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////

void setup(){
    
    status = 0;

    Serial.begin(115200);

	delay(10);



	Serial.println();
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);


	while (WiFi.status() != WL_CONNECTED) {

		delay(500);
		Serial.print(".");

	}


	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

	server.begin();
    
    
    
    
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }


    display.display();
    delay(500); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
    display.display();
    
    
    
    
    Wire.begin();
    
    Wire.begin();
    Serial.begin(115200);

    // Configurar acelerometro
    I2CwriteByte(MPU9250_ADDRESS, 28, ACC_FULL_SCALE_16_G);
   
    // Configurar giroscopio
    I2CwriteByte(MPU9250_ADDRESS, 27, GYRO_FULL_SCALE_2000_DPS);
   
    // Configurar magnetometro
    I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
    I2CwriteByte(MAG_ADDRESS, 0x0A, 0x01);
    
    

}








///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


void loop(){
    
    


	WiFiClient client = server.available();   // listen for incoming clients

    
    
	if (client) {                             // if you get a client,

		Serial.println("New Client.");           // print a message out the serial port

		String currentLine = "";                // make a String to hold incoming data from the client


		while (client.connected()) {            // loop while the client's connected

            
			if (client.available()) {             // if there's bytes to read from the client,

				char c = client.read();             // read a byte, then

				Serial.write(c);                    // print it out the serial monitor



				if (c == '\n') {                    // if the byte is a newline character

					// if the current line is blank, you got two newline characters in a row.
					// that's the end of the client HTTP request, so send a response:

					if (currentLine.length() == 0) {

						// HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
						// and a content-type so the client knows what's coming, then a blank line:
						client.println("HTTP/1.1 200 OK");
						client.println("Content-type:text/html");
						client.println();
                        
                        //client.println("<head>");
                        //client.println("<title>IoT System</title>");
                        //client.println("</head>");

						// the content of the HTTP response follows the header:
						client.print("Click <a href=\"/0\">here</a> for option 0.<br>");
                        client.print("Click <a href=\"/1\">here</a> for option 1.<br>");
                        client.print("Click <a href=\"/2\">here</a> for option 2.<br>");
                        client.print("Click <a href=\"/3\">here</a> for option 3.<br>");
                        client.print("Click <a href=\"/4\">here</a> for option 4.<br>");
                        client.print("Click <a href=\"/5\">here</a> for option 5.<br>");
                        client.print("Click <a href=\"/6\">here</a> for option 6.<br>");
                        client.print("Click <a href=\"/7\">here</a> for option 7.<br>");
                        client.print("Click <a href=\"/8\">here</a> for option 8.<br>");
                        client.print("Click <a href=\"/9\">here</a> for option 9.<br>");
                        client.print("<br>");
                        

            

						// The HTTP response ends with another blank line:
						client.println();
						// break out of the while loop:
						break;

					} else { // if you got a newline, then clear currentLine:

						currentLine = "";

					}
                    
                    
				} else if (c != '\r') { // if you got anything else but a carriage return character,
					currentLine += c; // add it to the end of the currentLine
				}

				// Check to see if the client request was "GET /H" or "GET /L":
				if (  currentLine.endsWith("GET /0")  ) { status = 0; }
				if (  currentLine.endsWith("GET /1")  ) { status = 1; }
				if (  currentLine.endsWith("GET /2")  ) { status = 2; }
				if (  currentLine.endsWith("GET /3")  ) { status = 3; }
				if (  currentLine.endsWith("GET /4")  ) { status = 4; }
				if (  currentLine.endsWith("GET /5")  ) { status = 5; }
				if (  currentLine.endsWith("GET /6")  ) { status = 6; }
				if (  currentLine.endsWith("GET /7")  ) { status = 7; }
				if (  currentLine.endsWith("GET /8")  ) { status = 8; }
				if (  currentLine.endsWith("GET /9")  ) { status = 9; }

                

                
			}
            

            
		}
		// close the connection:
		client.stop();
		Serial.println("Client Disconnected.");
	}
        
    //Serial.println(status);
    
    choseTask(status);
    
    
    //sensorFunctions();
    
}


///////////////////////////////////////////////////////////////////////////////////////


void choseTask(int choice){

    
    switch(choice){
        
        //case 0: Serial.println("zero" );  delay(2500); cls();             break;
        case 1:   report("Option","1");            break;
        case 2:   report("Option","2");            break;
        case 3:   report("Option","3");            break;
        case 4:   report("Option","4");            break;
        case 5:   report("Option","5");            break;
        case 6:   report("Option","6");            break;
        case 7:   report("Option","7");            break;
        case 8:   report("Option","8");     delay(2000); testfillroundrect();       break;
        case 9:   report("Option","9");    delay(2000);  testfillrect();       break;
      
        default: break;
    
    }
    
    status = 0; // reset the global choice
    
    return;
}

///////////////////////////////////////////////////////////////////////////////////////

void cls(){
    
    // Clear the buffer
    display.clearDisplay();
    display.display();
    
}


void testdrawline() {
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for(i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();

  for(i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }
  for(i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000); // Pause for 2 seconds
}


void testdrawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }

  delay(2000);
}



void testfillrect(void) {
  display.clearDisplay();

  
     int16_t i = 0; 
    // The INVERSE color is used so rectangles alternate white/black
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1000);


    display.setTextSize(2);             
    display.setTextColor(SSD1306_INVERSE);   
    display.setCursor(0,0);            
    display.println(F("Hello!"));
    
    display.setTextSize(4);             
    display.setTextColor(SSD1306_INVERSE);   
    display.setCursor(0,25); // x , y from top           
    display.println(F("0123"));
    
    display.display();
    delay(2000);
    

    display.clearDisplay();

    display.setTextSize(2);             
    display.setTextColor(SSD1306_WHITE);   
    display.setCursor(0,0);            
    display.println(F("Hello!"));
    
    display.setTextSize(4);             
    display.setTextColor(SSD1306_WHITE);   
    display.setCursor(0,25); // x , y from top           
    display.println(F("0123"));
    
    display.display();
    delay(2000);
    
    
}


void report(String units,String value) {

    display.clearDisplay();

    display.setTextSize(2);             
    display.setTextColor(SSD1306_WHITE);   
    display.setCursor(0,0);            
    display.println(units);
    
    display.setTextSize(4);             
    display.setTextColor(SSD1306_WHITE);   
    display.setCursor(0,25); // x , y from top           
    display.println(value);
    
    display.display();
    delay(2000);
    
    
}


void testdrawcircle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}


void testfillcircle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
    // The INVERSE color is used so circles alternate white/black
    display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
    display.display(); // Update screen with each newly-drawn circle
    delay(1);
  }

  delay(2000);
}


void testdrawroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}


void testfillroundrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2-2; i+=2) {
    // The INVERSE color is used so round-rects alternate white/black
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
      display.height()/4, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}


void testdrawtriangle(void) {
  display.clearDisplay();

  for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
    display.display();
    delay(1);
  }

  delay(2000);
}


void testfilltriangle(void) {
  display.clearDisplay();

  for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
    // The INVERSE color is used so triangles alternate white/black
    display.fillTriangle(
      display.width()/2  , display.height()/2-i,
      display.width()/2-i, display.height()/2+i,
      display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
    display.display();
    delay(1);
  }

  delay(2000);
}


void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }

  display.display();
  delay(2000);
}


void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}


void testscrolltext(void) {
  display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println(F("scroll"));
  display.display();      // Show initial text
  delay(100);

  // Scroll in various directions, pausing in-between:
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
}


void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}



void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
    
    int8_t f, icons[NUMFLAKES][3];
    
    int index;

    // Initialize 'snowflake' positions
    for(f=0; f< NUMFLAKES; f++) {
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
        Serial.print(F("x: "));
        Serial.print(icons[f][XPOS], DEC);
        Serial.print(F(" y: "));
        Serial.print(icons[f][YPOS], DEC);
        Serial.print(F(" dy: "));
        Serial.println(icons[f][DELTAY], DEC);
    }

  for( index = 0; index < 64 ; index++ ) { 
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for(f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(100);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for(f=0; f< NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
   
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.endTransmission();

    Wire.requestFrom(Address, Nbytes);
    uint8_t index = 0;
   
    while ( Wire.available() ){
        
        Data[index++] = Wire.read();
        
    }
    
}



void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data){
   
    Wire.beginTransmission(Address);
    Wire.write(Register);
    Wire.write(Data);
    Wire.endTransmission();

}
///////////////////////////////////////////////////////////////////////////////////////


// There might be a timing or I2C bus problem... ....or pull-up.... 
void sensorFunctions(){
    
   // ---  Lectura acelerometro y giroscopio --- 
    uint8_t Buf[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

    
    
    // Convertir registros acelerometro
    int16_t ax = -(Buf[0] << 8 | Buf[1]);
    int16_t ay = -(Buf[2] << 8 | Buf[3]);
    int16_t az = Buf[4] << 8 | Buf[5];

    
    // Convertir registros giroscopio
    int16_t gx = -(Buf[8] << 8 | Buf[9]);
    int16_t gy = -(Buf[10] << 8 | Buf[11]);
    int16_t gz = Buf[12] << 8 | Buf[13];



    // ---  Lectura del magnetometro --- 
    uint8_t ST1;
    
    do{
     
       I2Cread(MAG_ADDRESS, 0x02, 1, &ST1);

    } while ( ! (ST1 & 0x01) );

    
    uint8_t Mag[7];
   
    I2Cread(MAG_ADDRESS, 0x03, 7, Mag);


    // Convertir registros magnetometro
    int16_t mx = -(Mag[3] << 8 | Mag[2]);
    int16_t my = -(Mag[1] << 8 | Mag[0]);
    int16_t mz = -(Mag[5] << 8 | Mag[4]);


    // --- Mostrar valores ---
    
    
    if ( true ){
        // Acelerometro
        Serial.print(ax, DEC);
        Serial.print("\t");
        Serial.print(ay, DEC);
        Serial.print("\t");
        Serial.print(az, DEC);
        Serial.print("\t\t");
    }


    if ( false ){
        // Giroscopio
        Serial.print(gx, DEC);
        Serial.print("\t");
        Serial.print(gy, DEC);
        Serial.print("\t");
        Serial.print(gz, DEC);
        Serial.print("\t\t");
    }

    
    if ( false ){
        // Magnetometro
        Serial.print(mx + 200, DEC);
        Serial.print("\t");
        Serial.print(my - 70, DEC);
        Serial.print("\t");
        Serial.print(mz - 700, DEC);
        Serial.print("\t");
    }
   
    // Fin medicion
    Serial.println("");  
    
    
    
    
}

///////////////////////////////////////////////////////////////////////////////////////
void gyro(){
    
    int i;
    
   // ---  Lectura acelerometro y giroscopio --- 
    uint8_t Buf[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

    
    // Convertir registros giroscopio
    int16_t gx = -(Buf[8] << 8 | Buf[9]);
    int16_t gy = -(Buf[10] << 8 | Buf[11]);
    int16_t gz = Buf[12] << 8 | Buf[13];





    for ( i = 0; i < 16 ; i++ ){

    
        // Giroscopio
        Serial.print(gx, DEC);
        Serial.print("\t");
        Serial.print(gy, DEC);
        Serial.print("\t");
        Serial.print(gz, DEC);
        Serial.print("\t\t");
        delay(250);

        // Fin medicion
        Serial.println("");  
        
    }
    
    
    
    
}



void accel(){
    
   // ---  Lectura acelerometro y giroscopio --- 
    uint8_t Buf[14];
    I2Cread(MPU9250_ADDRESS, 0x3B, 14, Buf);

        
    // Convertir registros acelerometro
    int16_t ax = -(Buf[0] << 8 | Buf[1]);
    int16_t ay = -(Buf[2] << 8 | Buf[3]);
    int16_t az = Buf[4] << 8 | Buf[5];



    // Acelerometro
    Serial.print(ax, DEC);
    Serial.print("\t");
    Serial.print(ay, DEC);
    Serial.print("\t");
    Serial.print(az, DEC);
    Serial.print("\t\t");

   
    // Fin medicion
    Serial.println("");  
    
    
    
    
}