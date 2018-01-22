#define SET_BIT_HIGH(register_8, bit) (register_8 |= (1 << bit))
#define SET_BIT_LOW(register_8, bit) (register_8 &= ~(1 << bit))
