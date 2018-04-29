#define F_CPU (16000000UL)
#define SPEED 100

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include "lcd0.h"
#include "uart.h"


void portinic();
void Timer2_init();
void led_out(unsigned char led);
void rgb_on();
void rgb_off();
unsigned char btn_in();
void ss_out();
void _dly_7s (short int d); 
void ss_coords_out();	
void matrix();
void x_inc();
void x_dec();
void y_inc();
void y_dec();
void next_pos(unsigned char k);
unsigned char chck_hit();
unsigned char chck_new();
void place_rnd();
void snake_add();


unsigned char kp=0, cnt=0, t=0, ch=0x00, btn=0, ss[4], keyr=0, col=0, keyin=10, rlse_cntr=0, last_value=0;
//kp: keypressed happened, kp tárolja mely bill lett leütve
unsigned char y[64], x[64], l=1, last=0, nxt_y=0, nxt_x=0, c=0, h=0;
unsigned char r=0, rnd_cnt=0, rnd_y=0, rnd_x=0, nw=0;


int main()
{
	portinic();
	lcd_init();
	
	Uartinit();
	Timer2_init();
	
	CreateCGram();
	
	
	
	c=l;
	
	while(c--)
	{
			
        y[c]=0;
        x[c]=c;		
	lcd_gotoyx(y[c],x[c]);
	lcd_data(0x00);
	lcd_cmd(0x0C);//cursor off
	
	}
	
	nxt_y = y[l-1];
	nxt_x = x[l-1];
	
	ss_coords_out();
	
	UartSendByte(12);
	UartSendString("Snake is Ready;");
	        
        sei();
        
                

//MAIN LOOP
while(1){

        

        matrix();
        
        if ( kp>0 && r==0 ) {r=1; place_rnd(); }
        
        if((t==1) && (kp==2 || kp==8 || kp==4 || kp==6)){
       
        t=0; cnt=0; 
       
        lcd_gotoyx(y[last],x[last]);
        lcd_data(0x01);
        lcd_cmd(0x0C);
     
        next_pos(kp); 
                
        
        
        y[last]=nxt_y;
        x[last]=nxt_x;
            
             
        h=chck_hit();
        if (h==1) {lcd_clear(); lcd_gotoyx(1,4); lcd_string("Game Over!"); UartSendString("\n\rSnake is Dead."); while(1);}
        
        if(last<l-1) last++;
        else last=0;
                  
        nw=chck_new();
        if(nw==1) {nw=0; next_pos(kp); snake_add(); place_rnd();}
        
        lcd_gotoyx(nxt_y, nxt_x);
        lcd_data(0x00);
        lcd_cmd(0x0C);
          
        
                 
       ss_coords_out();
                 
        
        
        
        }//if
                       
                
        
               
}//while MAIN

}//main





  /////////////////////////////////////////
 //	FV. DEFFINITIONS		//
/////////////////////////////////////////


void portinic()
{
	DDRA=0xFF;
	DDRB=0xF0;
	DDRC=0xF8;
	DDRD=0xF0;
	DDRE=0xC0;
	DDRG=0x00;
}

//////////
void Timer2_init() {
        TIMSK|=(1<<TOIE2);
        TCCR2|=(1<<CS22);
}

void led_out(unsigned char led)
{
	PORTD=led;
	PORTB=(led<<4);
}

//////

unsigned char btn_in()
{
	return PING;
}

//////

void ss_out()
{
	unsigned char digit=0,j=0;
	
	
		while(digit<4)
		{
		PORTA=(0x80+(digit<<4)+ss[j]); //PORTA=(ENGbit+digitbitek+kiirnadóérték(0-9))
		digit++;
		j++;
		//if (digit==4){digit=0; j=0;}
		_delay_ms(1);
		}
	
	
}

///////



void _dly_7s (short int d)
{
	
	while(d--)
	ss_out();
		
}


///////


void ss_coords_out()
{
        ss[3] = nxt_y/10;
        ss[2] = nxt_y%10;
        ss[1] = nxt_x/10;
        ss[0] = nxt_x%10; 
        ss_out();

}

/////////


void matrix ()
{

        keyr=0x08;
        
        
	while(keyr!=0x80) {
		keyin=10;
		//led_out(rlse_cntr);	
		PORTC = keyr;
		
		_dly_7s(1);
		
		col = PINC;
		col &= 7;
		switch (col) {
			case 0x06: {
				switch (keyr) {
					case 0x08: { keyin=1; break;}
					case 0x10: { keyin=4; break;}
					case 0x20: { keyin=7; break;}
					case 0x40: { break;}
					} //sw keyr
				 break;} // case col
			case 0x05: {
				
				switch (keyr) {
					case 0x08: { keyin=2; break;}
					case 0x10: { keyin=5; break;}
					case 0x20: { keyin=8; break;}
					case 0x40: { keyin=0; break;}
					} //sw keyr
				 break;} // case col
			case 0x03: {
				
				switch (keyr) {
					case 0x08: { keyin=3; break;}
					case 0x10: { keyin=6; break;}
					case 0x20: { keyin=9; break;}
					case 0x40: {  break;}
					} //sw keyr
				 break;} // case col
		}//switch col

		keyr<<=1;
		
			
		
		if (keyin==last_value && rlse_cntr<5) {
			 rlse_cntr=0; continue;
			}

		if (keyin==10  && rlse_cntr<5) {
			 rlse_cntr++; continue;
			}
		
		if ((keyin!=10 && keyin==last_value && rlse_cntr>=5) || (keyin!=10 && keyin!=last_value)) {
			 rlse_cntr=0; 
			 last_value=keyin;
			 //UartSendByte(keyin+48);
			 kp=keyin;
			 continue;
			}

		
			
		
		
	}//while keyr
	
        if (keyr==0x80) keyr=0x08;

}



void x_inc() {

        if(nxt_x<15) nxt_x++;
        else nxt_x=0;

}

void x_dec()
{
        if(nxt_x>0) nxt_x--;
        else nxt_x=15;
}

void y_inc()
{
        if(nxt_y<3) nxt_y++;
        else nxt_y=0;
}


void y_dec()
{
        if(nxt_y>0) nxt_y--;
        else nxt_y=3;
}

next_pos(unsigned char k)
{
        switch (k) {
          case 2: { y_dec(); break; }
          case 8: { y_inc(); break; }
          case 4: { x_dec(); break; }
          case 6: { x_inc(); break; }
          }//sw
          
}


unsigned char chck_hit()
{
        unsigned char i=l;
        
        while (i--) {
          if ((nxt_y == y[i]) && (nxt_x == x[i]) && i!=last) return 1;
          else continue;
          }
        
        return 0;

}


unsigned char chck_new()
{
        if ((nxt_y == rnd_y) && (nxt_x == rnd_x)) return 1;       
        
        return 0;     
          
}



void place_rnd() 
{
        rnd_x=rnd_cnt%16; rnd_y=rnd_cnt%4;
        lcd_gotoyx(rnd_y, rnd_x);
        lcd_data(0x00);
}




void snake_add()
{
        unsigned char i=l;
        
        l++;
               
        while(i>last) {
          x[i] = x[i-1];
          y[i] = y[i-1];
          i--;
        
        
        }
        
        x[last] = nxt_x;
        y[last] = nxt_y;
        
        if(last<l-1) last++;
        else last=0;


}


//////////////

ISR(USART0_RX_vect)
{
        
        unsigned char ch=UDR0;
        led_out(ch);
        
	
}


ISR(TIMER2_OVF_vect)
{
	TCNT2=0;
	cnt++;	
	rnd_cnt++;

        if (cnt==SPEED) {
        
        t=1;
        cnt=0;

	}
	
}




