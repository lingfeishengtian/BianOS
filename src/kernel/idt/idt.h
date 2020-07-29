struct idt_entry{
    unsigned short entry_address_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short entry_address_high;
} __attribute__ ((packed));

struct idt{
    unsigned short size;
    unsigned int address;
} __attribute__ ((packed));

void setup_idt();