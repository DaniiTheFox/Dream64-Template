// ********************************
// *  TERMINAL EMULATOR FOR GAME  *
// ********************************
// ---------------------------------------------------------------
class LL_Termios {
    public:             // --------------------
        std::tm *now = NULL;   // TO AVOID NEW POINTERS TRASH
        LL_Termios();          // THIS IS THE TERMINAL SETUP START MODE
        void LL_Termios_Log(std::string _print); // PRINT A TERMINAL MESSAGE
        void LL_Termios_Exec(std::string _cmd_); // EXECUTE A COMMAND
        // ----------------------------------------------------------
};
// -----------------------------------------------------------------
LL_Termios::LL_Termios(){};
// -----------------------------------------------------------------
void LL_Termios::LL_Termios_Log(std::string _print){
    std::time_t t = std::time(0);   // get time now
    now = std::localtime(&t);
    std::cout<<"\033[1;31m{"<<now->tm_mday<<"-"<<now->tm_mon<<"-"<<(now->tm_year+1900)<<"} \033[1;33m<ねむりうた64>> \033[1;35m"<<_print<<std::endl;
}
// ------------------------------------------------------------------
LL_Termios *LL_Sterm = new LL_Termios();