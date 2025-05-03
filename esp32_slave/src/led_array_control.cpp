#include "led_array_control.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define DATA_PIN 18
#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

static const char *TAG_LAC = "LAC";
static uint8_t ucParameterToPass;

// Matrix setup params
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 16, DATA_PIN,
    NEO_MATRIX_TOP    + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

// The important stuff, your message and colors

char* Text[]= {"  ", "Greetings Joe, how goes your project?           "};
const uint16_t colors[] = {
  matrix.Color(255, 0, 255), matrix.Color(100, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};
int brightness = 40;

int numMode = arr_len(Text)-1;
int numColor = arr_len(colors)-1;
int pixelPerChar = 4;
int maxDisplacement;
int mode = 0;
int string_length = strlen(Text[1]);

static TaskHandle_t xHandle = NULL;

void LAC_init() {
    pinMode(DATA_PIN, OUTPUT);
    Serial.println("Setting up LED_array...");
    ESP_LOGI(TAG_LAC, "Setting up LED_array...");
    matrix.begin();
    matrix.setTextWrap(false);
    matrix.setBrightness(brightness);
    matrix.setTextColor(colors[0]);
    xTaskCreate(LAC_update, "LED Array Update", 2048, &ucParameterToPass, 10, &xHandle);
    if(xHandle == NULL){
        Serial.println("Error!!!");
    }
}

int y = matrix.height();
int x = matrix.width();
int pass = 0;
int line_pass = 0;

void LAC_update(void *stuff) {
    // put your main code here, to run repeatedly:
    for(;;){
        // if mode greater than numMode reset
        if (mode > numMode) { mode = 0; }
    
        matrix.fillScreen(0);
        matrix.setCursor(x, 0);

        if(mode==0 || mode == 1){
            LAC_scroll(Text[mode],15);
        }
    }

}

// this does the magic of scrolling
void LAC_scroll(char* message,int delays) {
    maxDisplacement = string_length * pixelPerChar + matrix.width();
    if(++line_pass > matrix.width()) line_pass = 0;
    matrix.print(String(message));
    if(--x < -maxDisplacement) {
        x = matrix.width();
        if(++pass >= numColor) { pass = 0;  };
        matrix.setTextColor(colors[pass]);
        //mode++;
    }
    matrix.show();
    delay(delays);
}

void LAC_update_string(String change, int size){
    Text[1] = (char*)malloc(size + 9);
    for(int i = 0; i<size+9; i++){
        Text[1][i] = ' ';
    }
    for(int i = 0; i<size; i++){
        Text[1][i] = change[i];
    }
    string_length = size+8;
}

void LAC_update_mode(int mode_update){
    mode = mode_update;
}