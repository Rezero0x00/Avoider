#include <mega328p.h> 
#include <delay.h> 

#define MOTOR1 PORTD.7 
#define MOTOR2 PORTD.6 
#define MOTOR3 PORTD.5 
#define MOTOR4 PORTD.4 

#define TRIG PORTD.3 
#define ECHO PIND.2 

unsigned int jarak; 
unsigned int baca_jarak(void) 
{ 
    unsigned int count = 0; 
    TRIG = 0; 
    delay_us(2); 
    TRIG = 1; 
    delay_us(10); 
    TRIG = 0; 

    while (!ECHO); 
    while (ECHO) 
    { 
        delay_us(1); 
        count++; 
        if(count > 25000) break;  
    } 
    return count / 58; 
} 

void main(void) 
{ 
    DDRD = 0b11111000;  
    DDRB.1 = 1;    
    PORTB.1 = 1;  

    while (1) 
    { 
        jarak = baca_jarak(); 
        if (jarak >= 20) 
        { 
            // Maju 
            MOTOR1 = 1; MOTOR2 = 0;  
            MOTOR3 = 1; MOTOR4 = 0;  
        } 
        else 
        { 
            // Stop 
            MOTOR1 = 0; MOTOR2 = 0; MOTOR3 = 0; MOTOR4 = 0; 
            delay_ms(200); 
            // Mundur 
            MOTOR1 = 0; MOTOR2 = 1; 
            MOTOR3 = 0; MOTOR4 = 1;  
            delay_ms(500);  
            // Belok kiri 
            MOTOR1 = 1; MOTOR2 = 0;  
            MOTOR3 = 0; MOTOR4 = 1;  
            delay_ms(300);  
            // stop 
            MOTOR1 = 0; MOTOR2 = 0; MOTOR3 = 0; MOTOR4 = 0; 
            delay_ms(200); 
        } 
        delay_ms(50);  
    } 
} 