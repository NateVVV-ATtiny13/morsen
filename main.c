/*
* ATtiny13_Morse.c
*
* Created: 10.09.2014 12:15:58
*  Author: Nathanael
*/

//#include <string.h>
#include <avr/io.h>
#define F_CPU 1200000UL  // 1,2 MHz
#include <util/delay.h>
#define ledon    PORTB |= (1<<PB0);
#define ledoff    PORTB &= ~(1<<PB0);

const int dit = 100;           // 100ms
const int dah = 300;           // 300ms (=3 * dit)
const int pauseSymbols = 100;  // Pause zwischen zwei Symbolen (Strich, Punkt), 100ms (=dit)
const int pauseLetters = 300;  // Pause zwischen Buchstaben in einem Wort, 300ms (=3 * dit)
const int pauseWords = 700;    // Pause zwischen Wörtern, 700ms (=7 * dit)

void morsen(char Zeichen)
{
    uint8_t symb = 0;
    uint8_t symb_length = 0b11100000;

    // Die ersten 3 Bits von "symb" charakterisieren die gültige Anzahl von Symbolstellen (Anzahl dits und dahs)
    switch (Zeichen)
    {
        case 'A':
          // . _
          symb = 0b01000001;
          break;
        case 'B':
          // _ . . .
          symb = 0b10001000;
          break;
        case 'C':
          // _ . _ .
          symb = 0b10001010;
          break;
        case 'D':
          // _ . .
          symb = 0b01100100;
          break;
        case 'E':
          // .
          symb = 0b00100000;
          break;
        case 'F':
          // . . _ .
          symb = 0b10000010;
          break;
        case 'G':
          // _ _ .
          symb = 0b01100110;
          break;
        case 'H':
          // . . . .
          symb = 0b10000000;
          break;
        case 'I':
          // . .
          symb = 0b01000000;
          break;
        case 'J':
          // . _ _ _
          symb = 0b10000111;
          break;
        case 'K':
          // _ . _
          symb = 0b01100101;
          break;
        case 'L':
          // . _ . .
          symb = 0b10000100;
          break;
        case 'M':
          // _ _
          symb = 0b01000011;
          break;
        case 'N':
          // _ .
          symb = 0b01000010;
          break;
        case 'O':
          // _ _ _
          symb = 0b01100111;
          break;
        case 'P':
          // . _ _ .
          symb = 0b10000110;
          break;
        case 'Q':
          // _ _ . _
          symb = 0b10001101;
          break;
        case 'R':
          // . _ .
          symb = 0b01100010;
          break;
        case 'S':
          // . . .
          symb = 0b01100000;
          break;
        case 'T':
          // _
          symb = 0b00100001;
          break;
        case 'U':
          // . . _
          symb = 0b01100001;
          break;
        case 'V':
          // . . . _
          symb = 0b10000001;
          break;
        case 'W':
          // . _ _
          symb = 0b01100011;
          break;
        case 'X':
          // _ . . _
          symb = 0b10001001;
          break;
        case 'Y':
          // _ . _ _
          symb = 0b10001011;
          break;
        case 'Z':
          // _ _ . .
          symb = 0b10001100;
          break;
        default:
          symb = 0b00000000;
    }
    symb_length &= symb;               // Nur Symbolstellenanzahl bleibt stehen
    symb_length = symb_length >> 5;    // Symbolstellenanzahl nach rechts schieben
    symb_length--;
    ////////
    /*
     * E = . = 0b00100000 (symb_length & symb)
     * symb_length = 0b00100000 (>>5)
     * symb_length = 0b001  (--)
     * symb_length = 0b000
     * */
    //uint8_t symb_init = 0b00001111;
    //symb &= symb_init;
    ////////
    
    for (uint8_t i = 0; i <= symb_length; i++)
    {
        if (symb & (1<<(symb_length-i)))
        {
            ledon;    // lang, weil dah = 1
            _delay_ms(dah);
        }
        else
        {
            ledon;    // kurz
            _delay_ms(dit);
        }
        ledoff;
        _delay_ms(pauseSymbols);
    }
    _delay_ms(pauseLetters);
}

void get_sign(char Ausdruck[])
{
  // "Ausdruck" entspricht dem Satz o.ä., welcher gemorst werden soll
  uint64_t length = strlen(Ausdruck);
  for(uint16_t i = 0; i < length; i++)
  {
    if(Ausdruck[i] == 32)
    {
      // Leerzeichen
      _delay_ms(pauseWords);
    }
    else if(Ausdruck[i] >= 97 && Ausdruck[i] <= 122)
    {
      // kleiner Buchstabe, der in großen Buchstabe "umgewandelt" wird
      morsen(Ausdruck[i] - 32);
    }
    else
    {
      // normaler Großbuchstabe
      morsen(Ausdruck[i]);
    }
  }
  _delay_ms(pauseWords);
}

int main(void)
{
    DDRB = 1;     // PB0 ist Ausgang
    PORTB = 0;    // alle LEDs aus
    _delay_ms(pauseWords);
   while(1)
   {
        ////////////////
        //PORTB |= (1<<PB0);
        ////////////////
        //_delay_ms(200);
        //PORTB &= ~(1<<PB0);
        //_delay_ms(200);
        ////////////////
        
        //
        //get_sign("morse");
        //get_sign("MORSE");
        //get_sign("morse MORSE");
        //
        
        get_sign("Hallo du geiler Typ");
        get_sign("Wie geht es dir");
        
        get_sign("SOS");
        
        get_sign("Du bist ein Lappen");
        get_sign("blablabal");
        //get_sign("y");
        
        /*
        morsen('A');
        morsen('B');
        morsen('C');
        morsen('D');
        morsen('E');
        morsen('F');
        morsen('G');
        morsen('H');
        morsen('I');
        morsen('J');
        morsen('K');
        morsen('L');
        morsen('M');
        morsen('N');
        morsen('O');
        morsen('P');
        morsen('Q');
        morsen('R');
        morsen('S');
        morsen('T');
        morsen('U');
        morsen('V');
        morsen('W');
        morsen('X');
        morsen('Y');
        morsen('Z');

        _delay_ms(pauseWords);  //neues Wort
        */
   }
  return 0;
} 
