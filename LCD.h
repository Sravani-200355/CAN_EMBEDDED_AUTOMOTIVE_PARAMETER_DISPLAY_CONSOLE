// Sends a command (like clear screen or move cursor) to the LCD
void Write_CMD_LCD(char);
// Sends a single data character to be displayed on the LCD screen
void Write_DAT_LCD(char);
// Low-level function to write a raw byte to the LCD hardware pins
void Write_LCD(char);
// Configures LCD pins and runs the startup sequence (bit mode, cursor off, etc.)
void LCD_Init(void);
// Accepts a string pointer to display a full word or sentence on the LCD
void Write_str_LCD(char *);
// Converts a signed integer to characters and displays it (-32768 to 32767)
void Write_int_LCD(signed int);//signed int(2 byte)-> -32768 to 32767
// Displays a float with a specific number of decimal places (defined by the char)
void Write_float_LCD(float f,char );
//void Write_Data_LCD(0);
//void Write_Data_LCD(1);
