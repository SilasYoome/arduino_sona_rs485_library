#ifndef SONA_RS485_H_
#define SONA_RS485_H_

class sona_rs485{
    public:
        sona_rs485(int _uart_num,int _baud ,int _cs_pin,int address);
        void init();
        void send_command(int command);
        bool get_data(unsigned char* sona_data_buffer);
    private:
        int uart_num;
        int baud;
        int cs_pin;
        int command_data[5] = {0x55,0xAA,0x01,0x01,0x01};  //{head1(0x55),head2(0xAA),address,command,check}
        int sona_data[13];  //{head1,head2,address,command,D1H,D1L,D2H,D2L,D3H,D3L,D4H,D4L,check}
};
#endif