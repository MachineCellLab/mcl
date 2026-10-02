#ifndef _mcl_terminal_
#define _mcl_terminal_

#include <unistd.h>
#include <stdint.h>
#include <stddef.h> 
#include <cstdio>
#include <string>

namespace mcl {
    class terminal {
        public:
            static const size_t MAX_INPUT_LINE = 4096;

            typedef struct _CursorPosition {
                uint16_t x;
                uint16_t y;
            } CursorPosition_t;

            typedef enum _AnsiColor : uint8_t {
                BLACK = 0,
                RED = 1,
                GREEN = 2,
                YELLOW = 3,
                BLUE = 4,
                MAGENTA = 5,
                CYAN = 6,
                WHITE = 7
            } AnsiColor_t;    

            typedef enum _AnsiStyle : uint8_t {
                RESET = 0,
                BOLD = 1,
                DIM = 2,

                UNDERLINE = 4,
                BLINK = 5,  

                REVERSED = 7,
                HIDDEN = 8,
                STRIKETHROUGH = 9
            } AnsiStyle_t;

            typedef enum _CtrlKey : char {
                KEY_NULL = 0,	    /* NULL */
                CTRL_A = 1,         /* Ctrl+a */
                CTRL_B = 2,         /* Ctrl+b */
                CTRL_C = 3,         /* Ctrl+c */
                CTRL_D = 4,         /* Ctrl+d */
                CTRL_E = 5,         /* Ctrl+e */
                CTRL_F = 6,         /* Ctrl+f */
                CTRL_G = 7,         /* Ctrl+g */
                CTRL_H = 8,         /* Ctrl+h */
                KEY_TAB = 9,        /* Tab */
                CTRL_K = 11,        /* Ctrl+k */
                CTRL_L = 12,        /* Ctrl+l */
                ENTER = 13,         /* Enter */ 
                CTRL_N = 14,        /* Ctrl+n */
                CTRL_O = 15,        /* Ctrl+o */
                CTRL_P = 16,        /* Ctrl+p */
                CTRL_Q = 17,        /* Ctrl+q */
                CTRL_R = 18,        /* Ctrl+r */
                CTRL_S = 19,        /* Ctrl+s */
                CTRL_T = 20,        /* Ctrl+t */
                CTRL_U = 21,        /* Ctrl+u */
                CTRL_V = 22,        /* Ctrl+v */
                CTRL_W = 23,        /* Ctrl+w */
                CTRL_X = 24,        /* Ctrl+x */
                CTRL_Y = 25,        /* Ctrl+y */
                CTRL_Z = 26,        /* Ctrl+z */
                ESC = 27,           /* Escape */
                BACKSPACE =  127    /* Backspace */
            } CtrlKey_t;

            terminal();

            virtual ~terminal();

            void clear(void);

            void home(void);

            void bell(void);

            // set the cursor position in the terminal

            void setCursorPosition(const uint16_t x, const uint16_t y);

            void setCursorPosition(const CursorPosition_t position);    


            // get the size of the terminal
            void getTerminalSize(uint16_t& rows, uint16_t& cols);

            // FIXME: unable to get getCursorPosition() to work 

            // DECSTBM scrolling region controls...
            void setScrollingRegion(const uint16_t top, const uint16_t bottom);

            void clearScrollingRegion(void);

            // manage the colors of the text in the terminal

            void setForegroundColor(const AnsiColor_t color);

            void setBackgroundColor(const AnsiColor_t color);

            // manage the style of the text in the terminal

            void setStyle(const AnsiStyle_t style);

            void resetStyle(void);

            // put stuff out to the terminal

            void put(const char c);

            void put(const char* str);

            void put(const std::string& str);

            // fancier prints

            void put(const AnsiColor_t fg, const AnsiColor_t bg, const std::string& str);

            void put(const AnsiColor_t fg, const AnsiColor_t bg, const AnsiStyle_t style, const std::string& str);     

            void put(const AnsiColor_t fg, const AnsiColor_t bg, const char c);

            void put(const AnsiColor_t fg, const AnsiColor_t bg, const AnsiStyle_t style, const char c); 

            // accept a line of user input
            void getLine(const std::string& prompt, std::string& line);

        protected:
            // input character buffer
            char inputBuffer[MAX_INPUT_LINE];

        private:
            // tbd
    }; // end class terminal
} // end namespace mcl

#endif

